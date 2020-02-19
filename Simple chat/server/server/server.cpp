#include "server.h"
#include <iostream>
#include <sstream>

Server::Server()
{
	std::cout << "Setting up" << std::endl;
	m_maxPlayerNumber = 10;
	m_currentID = 0;
	m_playerNumber = 0;

	m_ipAdress = m_ipAdress.getPublicAddress();
	m_isRunning = true;
	m_port = 45000;

	m_listener.setBlocking(false);
	m_listener.listen(m_port);
	m_selector.add(m_listener);

	userList.clear();

	std::cout << "Server is started. Waiting for clients" << std::endl;
	zegar.restart();
}

void Server::run()
{
	while (m_isRunning) // nieskonczona petla, poniewaz chcemy otrzymywac i wysylac pakiety caly czas
	{
		if (m_selector.wait())
		{
			if (m_selector.isReady(m_listener)) //Je¿eli server jest gotowy na nowe po³¹czenia
			{
				std::unique_ptr<sf::TcpSocket> tempSocket = std::make_unique<sf::TcpSocket>();

				if (m_listener.accept(*tempSocket) == sf::Socket::Done)
				{
					if (m_playerNumber < m_maxPlayerNumber) //Je¿eli server nie jest pe³ny
					{
						userList.emplace_back(User(&tempSocket, m_currentID));
						m_selector.add(*userList.back().getSocket());
						m_playerNumber++;

						sf::Packet outPacket;
						outPacket << PacketType::Connected;
						outPacket << m_currentID;

						if (userList.back().getSocket()->send(outPacket) != sf::Socket::Done) //Wyœlij id u¿ytkownika
							std::cout << "error sending player index" << std::endl;
						m_currentID++;
					}
					else //Je¿eli server jest pe³ny
					{
						sf::Packet outPacket;
						outPacket << PacketType::ServerFull;
						outPacket << 0;

						if (tempSocket->send(outPacket) != sf::Socket::Done)
							std::cout << "Error sending server is full message" << std::endl;

						std::cout << "User tried to connect but the server was full" << std::endl;
					}
				}
			}
			else
			{
				//Odbieraj dane
				for (unsigned int i = 0; i < userList.size(); i++)
				{
					if (m_selector.isReady(*userList[i].getSocket()))
					{
						sf::Packet received;
						if (userList[i].getSocket()->receive(received) == sf::Socket::Done)
						{
							userList[i].setTimeout(zegar.getElapsedTime());

							int num, id;
							received >> num;
							received >> id;

							if (num == PacketType::Disconnected) // u¿ytkownik siê roz³¹czy³. Wyœlij informacje innym u¿ytkownikom
							{

								sendPacket(received, i);

								for (auto& itr : userList)
								{
									if (itr.getId() == id)
									{
										std::cout << std::endl << "Client disconnected!" << std::endl;
										std::cout << "	ID: " << itr.getId() << " Name: " << itr.getName() << std::endl;
									}
								}
								m_playerNumber--;

								std::cout << "Number of users: " << m_playerNumber << std::endl;
								m_selector.remove(*userList[i].getSocket());
								userList.erase(userList.begin() + i);
								break;
							}

							else if (num == PacketType::MessageSent) //Ktoœ wys³a³ wiadomoœæ
							{
								sf::Packet wiadomosc;
								wiadomosc << num << id;
								char messageSent[100];
								received >> messageSent;
								wiadomosc << messageSent;
								sendPacket(wiadomosc, id);
								std::cout << "Sent: " << messageSent << std::endl;
							}
							else if (num == PacketType::SaveName) //Save player name
							{
								sf::Packet serverPacket, serverPacket2, serverPacket3;

								if (userList[i].getId() == id)
								{
									char nameHolder[100];
									received >> nameHolder;
									userList[i].setName(nameHolder);
									std::cout << std::endl << "Incomming connection from: " << userList[i].getSocket()->getRemoteAddress() << std::endl;
									std::cout << std::endl << "New client added." << std::endl;
									std::cout << "	ID: " << id << " Name: " << nameHolder << std::endl;
									std::cout << "Number of users: " << m_playerNumber << std::endl;
									serverPacket << 11 << id << "New client added";
									//serverPacket2 << 11 << id << "ID: " + to_string(id) + " Name: " + nameHolder;
									//serverPacket3 << 11 << id << "Number of players: " + to_string(m_playerNumber);
									sendPacket(serverPacket);
									//sendPacket(serverPacket2);
									//sendPacket(serverPacket3);
								}
							}
							else if (num == PacketType::SendClientList) //send client list with id and names  When player recive this it goes through the list and compares it with its list, if he finds a number that he doesn't have he creates a enemy with that id
							{
								sf::Packet namePacket;
								namePacket << PacketType::SendClientList;
								namePacket << 0;
								namePacket << m_playerNumber;

								for (unsigned int j = 0; j < userList.size(); ++j)
								{
									namePacket << userList[j].getId();
									namePacket << userList[j].getName().c_str();
								}

								sendPacket(namePacket);
							}
						}



						//If some player time-out-ed alert other players
						float tempTime = zegar.getElapsedTime().asSeconds() - userList[i].getTimeout().asSeconds();
						if (tempTime >= 5)
						{
							sf::Packet disconnectPacket;
							disconnectPacket << PacketType::Disconnected << userList[i].getId();

							sendPacket(disconnectPacket, i);

							std::cout << "Player: " << userList[i].getId() << " timeouted" << std::endl;

							m_selector.remove(*userList[i].getSocket());
							userList.erase(userList.begin() + i);
							m_playerNumber--;
							break;
						}
					} // end of player socket is ready
				}
			}
		}
	}
}

void Server::sendPacket(sf::Packet& packet, const int& skip)
{
	for (unsigned int i = 0; i < userList.size(); ++i)
	{
		if (skip == userList[i].getId())
			continue;
		if (userList[i].getSocket()->send(packet) != sf::Socket::Done)
		{
			std::cout << "Error sending packet in sendPacket func" << std::endl;
		}
	}
}

void Server::sendPacketSingle(sf::Packet& packet, const int& user)
{
	if (userList[user].getSocket()->send(packet) != sf::Socket::Done) {
		std::cout << "Error sending packet in sendPacket func" << std::endl;
	}
}

std::string Server::to_string(const int& liczba)
{
	std::stringstream ss;
	ss << liczba;
	return ss.str();
}
