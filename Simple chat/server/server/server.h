#ifndef SERVER_H
#define SERVER_H

#include "user.h"
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>

class Server
{
	public:

	Server();
	void run();

	private:

	void sendPacket(sf::Packet & packet, const int& skip = -1);
	void sendPacketSingle(sf::Packet & packet, const int& user);
	std::string to_string(const int& liczba);

	sf::Clock zegar;

	bool m_isRunning;

	sf::IpAddress m_ipAdress;
	unsigned short m_port;

	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;

	std::vector<User> userList;

	int m_maxPlayerNumber;
	int m_currentID;
	int m_playerNumber;
};

enum PacketType
{
	Connected,
	Disconnected,
	ServerFull,
	MessageSent,
	SaveName,
	SendClientList,
};

#else
#endif