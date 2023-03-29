#ifndef STRINGTOOLSFILE_H
#define STRINGTOOLSFILE_H


#include "common.h"

#include "Logger.h"

namespace stringTools
{
	// returns message for server withing () symbols
	std::string GetMessageText(const std::string& msg);

	/*
	*   returns launch mode based on information within <> symbols
	*   returns CLIENT(40) in case of "client" or "Client" input
	*   return SERVER(30) in case of "server" or "Server" input
	*   otherwise, returns UNRECOGNIZABLE_MODE(0)
	*/
	uint8_t GetMode(const std::string& msg);
}

#endif