#include "network.h"
#include "user.h"
#include "otherUsers.h"
#include <iostream>
#include <SFML/Network.hpp>

Network::Network(sf::IpAddress& ip, unsigned short& port) : m_connected(false)
{
	connected = false;
	if (connection.connect(ip, port, sf::seconds(2)) != sf::Socket::Done) {
		std::cout << "Error connecting to server" << std::endl;
		connected = false;
	}
	else {
		connection.setBlocking(false);
		std::cout << "Connected" << std::endl;
		connected = true;
	}
}

void Network::disconnect(User* p) //Rozlacz gracza z serwerem
{
	sf::Packet temp;
	temp << PacketType::Disconnected;
	temp << p->getID();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending disconnect command to server" << std::endl;
	}
	else
	{
		std::cout << "Disconnected" << std::endl;
	}
}

void Network::sendMessage(User* p, std::string& text)
{
	sf::Packet temp;
	temp << 5;
	temp << p->getID();
	temp << text;

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending text message to server" << std::endl;
	}
}


void Network::sendMyName(User* p)
{
	sf::Packet temp;
	temp << PacketType::SendName;
	temp << p->getID();
	temp << "kappa";

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending my name" << std::endl;
	}

}

void Network::getPlayerList(User* p)
{
	sf::Packet temp;
	temp << 7;
	temp << p->getID();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending getPlayerList to server" << std::endl;
	}
}

bool Network::getConnected() {
	return this->connected;
}

void Network::receive(std::vector<std::unique_ptr<OtherUsers>>& otherUsers, User* p)
{
	sf::Packet receivePacket;
	int type, id;
	if (connection.receive(receivePacket) == sf::Socket::Done)
	{
		receivePacket >> type;
		receivePacket >> id;

		if (type == 0) //polaczono sie z serwerem, otrzymanie swojego ID
		{
			if (p->getID() == -1)
			{
				p->setID(id);
				std::cout << "I connected to server, my ID: " << p->getID() << std::endl;
				this->sendMyName(p);
				sf::sleep(sf::milliseconds(50));
				this->getPlayerList(p);
			}
			m_connected = true;
		}
		else if (type == 1) //rozlaczono
		{
			for (unsigned int i = 0; i < otherUsers.size(); i++)
			{
				if (otherUsers[i]->getID() == id)
				{
					m_textMessage = "Player " + otherUsers[i]->getName() + " disconnected.";
					std::cout << "Enemy: " << otherUsers[i]->getID() << " deleted " << std::endl;
					otherUsers.erase(otherUsers.begin() + i);
				}
			}
		}
		else if (type == 2)
		{
			std::cout << "Server is full" << std::endl;
		}
		else if (type == 5) //otrzymano nowa wiadomosc
		{
			std::string receivedMessage;
			receivePacket >> receivedMessage;

			if (!receivedMessage.empty())
			{
				std::string senderName;
				for (unsigned int k = 0; k < otherUsers.size(); k++)
				{
					if (otherUsers[k]->getID() == id)
						senderName = otherUsers[k]->getName();
				}
				if (id == p->getID())
					senderName = p->getName();
				std::string testMessage(receivedMessage);
				std::string newString = testMessage.substr(0, testMessage.length() - 1);
				m_textMessage = senderName + ":" + newString;
			}


		}

		else if (type == 7) //Utworz nowych uzytkownikow
		{
			int playerNumber;
			std::vector<std::string> playersName;
			std::vector<int> playersId;

			receivePacket >> playerNumber;
			std::cout << "Num of players on server: " << playerNumber << std::endl;

			for (int i = 0; i < playerNumber; ++i)
			{
				std::string tempName;
				int tempId;
				receivePacket >> tempId;
				receivePacket >> tempName;
				playersName.push_back(tempName);
				playersId.push_back(tempId);

			}


			for (unsigned int i = 0; i < playersId.size(); ++i) //loop through id-s we got
			{
				bool haveThatUser = false;
				for (unsigned int v = 0; v < otherUsers.size(); v++) //check if we already have enemy with that id
				{
					if (otherUsers[v]->getID() == playersId[i])
					{
						haveThatUser = true;
					}

				}
				if (playersId[i] != p->getID() && !haveThatUser) //if it is not our id and if we dont have that enemy, create a new enemy with that id
				{
					otherUsers.push_back(std::make_unique<OtherUsers>(playersId[i], playersName[i]));
					m_textMessage = "New player connected: " + playersName[i];
					std::cout << "Created a new enemy with id: " << playersId[i] << std::endl;

				}
			}

			playersName.clear();
			playersId.clear();
		}

	}
}
