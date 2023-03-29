#ifndef SERVERFILE_H
#define SERVERFILE_H


#include "common.h"

#include "Logger.h"
#include "File.h"

// singletone server class
namespace net 
{
	class Server
	{

	public:

		Server(Server& other) = delete;
		void operator=(const Server& other) = delete;

		virtual ~Server();

		// returns the Server instance
		static Server* getInstance(const char* ip, const uint16_t port);

		// forces the server to receive messages from clients
		void receiveMessages(const size_t socketNo) const;

		// stops server
		void stop();

		// Server's main function
		void main();

	protected:

		static Server* instance;

		SOCKADDR_IN addresses;
		size_t addressesSize;

		// socket for listening
		SOCKET sSock;

		// latest conenction socket
		SOCKET sLatestConnection;

		// all connections
		std::vector<SOCKET> nConnections;

		// maximum count of active connections
		size_t maximumConnectionsCount = 50;

		volatile bool isReceiving = false;

	protected:

		Server(const char* address, const uint16_t port);

		// prints message from client
		void printMessage(const std::string msg) const;
	};
}

#endif