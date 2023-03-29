#pragma once
#ifndef CLIENTFILE_H
#define CLIENTFILE_H

#include "common.h"

#include "Logger.h"

#include "StringTools.h"

namespace net 
{
	class Client
	{

	public:

		Client(const char* ip, const uint16_t port);

		// connects to server
		bool connectToServer() const;

		// stops client
		void stop();

		// client's main function
		void main(const std::string msg);

	protected:

		SOCKET sConnection;
		SOCKADDR_IN addresses;
		int32_t addressesSize;

		volatile bool run = false;

		// sends message to server (called withing Client's main function)
		int8_t sendMessage(const std::string msg) const;
	};
}

#endif