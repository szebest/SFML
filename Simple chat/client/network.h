#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <SFML/Network.hpp>
#include "otherUsers.h"
#include "user.h"

class Network
{
public:
	Network(sf::IpAddress& ip, unsigned short& port);
	void disconnect(User* p);

	void receive(std::vector<std::unique_ptr<OtherUsers>>& otherUsers, User* p);
	void sendMessage(User* p, std::string& text);
	void sendMyName(User* p);
	void getPlayerList(User* p);
	bool getConnected();

	std::string getMessage() { return m_textMessage; }

private:
	sf::TcpSocket connection;
	bool m_connected;

	std::string m_textMessage;
	int packetCounter = 0;
	sf::Clock packetClock;
	bool connected;
};

enum PacketType
{
	Connected,
	Disconnected,
	ServerFull,
	MessageSent,
	SendName,
	GetClientList,
};

#else
#endif