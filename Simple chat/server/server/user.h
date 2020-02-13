#ifndef USER_H
#define USER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>
#include <string>

class User
{
	public:

	User(std::unique_ptr<sf::TcpSocket>* socket, int id);

	void setName(const std::string name);
	std::string getName();

	int getId();

	sf::TcpSocket* getSocket();

	void setTimeout(sf::Time time);
	sf::Time getTimeout();

	private:

	std::string m_name;
	int m_id;
	std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
	sf::Time m_timeout;
};

#else
#endif