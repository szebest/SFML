#include "user.h"

User::User(std::unique_ptr<sf::TcpSocket>* socket, int id)
{
	m_name = "Default Name";
	m_id = id;
	m_socket = std::move(*socket);
	m_timeout = sf::seconds(0);
}

void User::setName(const std::string name)
{
	m_name = name;
}

std::string User::getName()
{
	return m_name;
}

int User::getId()
{
	return m_id;
}

sf::TcpSocket* User::getSocket()
{
	return m_socket.get();
}

void User::setTimeout(sf::Time time)
{
	m_timeout = time;
}

sf::Time User::getTimeout()
{
	return m_timeout;
}

