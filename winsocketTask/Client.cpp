#include "Client.h"

net::Client::Client(const char* ip, const uint16_t port)
{
	addressesSize = sizeof(addresses);
	addresses.sin_addr.s_addr = inet_addr(ip);
	addresses.sin_port = htons(port);
	addresses.sin_family = AF_INET;

	sConnection = socket(AF_INET, SOCK_STREAM, NULL);

}

/*
* connects client to server
* returns false if a client hasn't connect
* returns true if a client has successfuly connected
*/
bool net::Client::connectToServer() const
{
	int32_t connectionRespond = NULL;
	connectionRespond = connect(sConnection, (SOCKADDR*)&addresses, addressesSize);

	if (connectionRespond == SOCKET_ERROR) 
	{
		CONNECTION_FAILED(REPORT_CODES::CONNECTION_FAIL, "CLIENT: Failed to connect");
		WSACleanup;

		return false;
	}
	else 
	{
		CLIENT_CONNECTED(REPORT_CODES::SUCCESSFUL_CONNECTION, "CLIENT: Connected");
		return true;
	}
}

/* 
*  sends message from client to server(called within client's main function)
*  returns true if message was successfuly sent,
*  otherwise, returns SOCKET_ERROR(-1)
*/
int8_t net::Client::sendMessage(const std::string msg) const
{
	size_t msgSize = msg.size();

	int32_t sendRespond = NULL;
	sendRespond = send(sConnection, reinterpret_cast<char*>(&msgSize), sizeof(size_t), NULL);

	// sends message size to server
	if (sendRespond == SOCKET_ERROR)
	{
		SERVER_ERROR(REPORT_CODES::MISSING_SERVER, "CLIENT: Server is offline");
		WSACleanup();

		return SOCKET_ERROR;
	}

	// sends message text to server
	send(sConnection, msg.c_str(), static_cast<int32_t>(msgSize), NULL);

	return true;
}

void net::Client::stop()
{
	run = false;
}

// client's main function
void net::Client::main(const std::string msg)
{
	run = true;
	int32_t msgNo = 0;

	while (run == true)
	{
		std::string msgCopy = msg;
		msgCopy = msgCopy + std::to_string(msgNo);
		int8_t result = sendMessage(msgCopy);

		if (result == SOCKET_ERROR)
		{
			stop();
		}

		msgNo++;
		Sleep(2000);
	}
}