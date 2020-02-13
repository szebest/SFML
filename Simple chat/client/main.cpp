#include "user.h"
#include "network.h"
#include "otherUsers.h"
#include <iostream>

int main()
{
	User user;
	user.setName("szebest");
	std::vector<std::unique_ptr<OtherUsers>> otherUsers;
	sf::IpAddress ip = "localhost";
	unsigned short port = 45000;
	std::unique_ptr<Network> network;
	network = std::make_unique<Network>(ip, port);
	while (network->getConnected())
		network->receive(otherUsers, &user);
	return 0;
}