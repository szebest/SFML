#include "server.h"
#include <iostream>

Server::Server()
{
	std::cout << "Setting up" << std::endl;
	m_maxPlayerNumber = 10;
	m_currentID = 0;
	m_playerNumber = 0;

	m_ipAdress = "localhost";
	m_isRunning = true;
	m_port = 45000;

	m_listener.setBlocking(false);
	m_listener.listen(m_port);
	m_selector.add(m_listener);

	std::cout << "Server is started. Waiting for clients" << std::endl;
	zegar.restart();
}

void Server::run()
{
	while (true) // nieskonczona petla, poniewaz chcemy otrzymywac i wysylac pakiety caly czas
	{

	}
}
