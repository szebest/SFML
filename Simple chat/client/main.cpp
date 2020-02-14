#include "user.h"
#include "network.h"
#include "otherUsers.h"
#include <iostream>
#include <SFML/System/Thread.hpp>

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

		sf::sleep(sf::milliseconds(100)); //Zeby server nie zostal przeciazony niepotrzebnymi requestami dalejmy opoznienie na ten watek
	}
}

void init()
{
	std::cout << "Set your name: ";
	std::string name;
	std::cin >> name;
	user.setName(name);
}

int main()
{
	//Przygotowujemy watek ktory bedzie odbieral pakiety
	sf::Thread watek(&receivedThread);

	init();

	//Inicjalizujemy polaczenie
	sf::IpAddress ip = "localhost";
	unsigned short port = 45000;
	network = std::make_unique<Network>(ip, port);

	watek.launch();

	std::string message = "";
	//Glowna petla ktora pobiera i wysyla wiadomosci
	while (network->getConnected())
	{
		std::cin >> message;
		network->sendMessage(&user, message);
	}
	return 0;
}