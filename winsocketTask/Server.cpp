#include "Server.h"

net::Server* net::Server::instance = nullptr;

// protected server constructor
net::Server::Server(const char* address, const uint16_t port)
{
	addresses.sin_addr.s_addr = inet_addr(address);
	addresses.sin_port = htons(port);
	addresses.sin_family = AF_INET;
	addressesSize = sizeof(addresses);

	sSock = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sSock, reinterpret_cast<SOCKADDR*>(&addresses), static_cast<int32_t>(addressesSize));
}

net::Server::~Server()
{
	clearFile();

	delete instance;
}

/*
* returns server instance
* in case if function hasn't created an instance, returns nullptr
*/
net::Server* net::Server::getInstance(const char* ip, const uint16_t port)
{
	std::string respond = fileRead();

	if (respond.empty())
	{
		if (net::Server::instance == nullptr)
		{
			instance = new Server(ip, port);
			// костыль
			fileWrite("Server instance was created");

			return instance;
		}
		return nullptr;
	}
	
	return nullptr;
}

// forces server to receive messages from client
void net::Server::receiveMessages(const size_t socketNo) const
{
	size_t msgSize = 0;

	while (isReceiving == true)
	{

		// receive string(msg) size from client
		recv(nConnections[socketNo], reinterpret_cast<char*>(&msgSize), sizeof(size_t), NULL);

		char* message = new char[static_cast<int32_t>(msgSize) + 1];
		message[msgSize] = '\0';

		// receive message from client
		recv(nConnections[socketNo], message, static_cast<int32_t>(msgSize), NULL);

		printMessage(message);

		delete[] message;
	}
}

// sets recConnections's "while" condition to "false"
void net::Server::stop()
{
	isReceiving = false;
}

// prints incomming from client message
void net::Server::printMessage(const std::string msg) const
{
	std::cout << msg << '\n';
}

// the main function of class
void net::Server::main()
{
	isReceiving = true;

	listen(sSock, SOMAXCONN);

	for (size_t socketNo = 0; socketNo < maximumConnectionsCount; socketNo++)
	{
		sLatestConnection = accept(sSock, reinterpret_cast<SOCKADDR*>(&addresses), reinterpret_cast<int*>(&addressesSize));

		if (sLatestConnection == NULL)
		{
			CONNECTION_FAILED(REPORT_CODES::CONNECTION_FAIL, "SERVER: Failed to connect!");
		}
		else
		{
			CLIENT_CONNECTED(REPORT_CODES::SUCCESSFUL_CONNECTION, "SERVER: Client has been connected");
		}

		nConnections.push_back(sLatestConnection);

		std::thread tReceiveMessages(std::bind(&Server::receiveMessages, this, socketNo));
		tReceiveMessages.detach();
	}
}