#include "user.h"
#include "network.h"
#include "otherUsers.h"
#include <iostream>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>

std::vector<std::unique_ptr<OtherUsers>> otherUsers;
std::unique_ptr<Network> network;
User user;

void receivedThread()
{
	while (network->getConnected())
	{
		network->receive(otherUsers, &user);

		if (network->getReceivedMessage())
		{
			network->setReceivedMessage(false);
			std::cout << network->getMessage() << std::endl;
		}

		sf::sleep(sf::milliseconds(50));
	}
}

int main()
{
	sf::Thread watek(&receivedThread);
	std::cout << "Set your name: ";
	std::string name;
	std::cin >> name;
	user.setName(name);
	sf::IpAddress ip = "localhost";
	unsigned short port = 45000;
	network = std::make_unique<Network>(ip, port);
	std::string message = "";
	watek.launch();
	while (network->getConnected())
	{
		std::cin >> message;
		network->sendMessage(&user, message);
	}
	return 0;
}