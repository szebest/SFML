#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class Server
{
	public:

	Server();
	void run();

	private:

	void sendPacket(sf::Packet & packet, const int& skip = -1);
	std::string to_string(const int& liczba);

	sf::Clock zegar;

	bool m_isRunning;

	sf::IpAddress m_ipAdress;
	unsigned short m_port;

	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;

	int m_maxPlayerNumber;
	int m_currentID;
	int m_playerNumber;
};

#else
#endif