#include "StringTools.h"

std::string stringTools::GetMessageText(const std::string& msg)
{
	size_t first = msg.find_first_of('(');
	size_t last = msg.find_last_of(')');
	std::string substr = msg.substr(first + 1, last - first - 1);

	return substr;
}

uint8_t stringTools::GetMode(const std::string& msg)
{
	size_t first = msg.find_first_of('<');
	size_t last = msg.find_last_of('>');

	std::string substr = msg.substr(first + 1, last - first - 1);

	if (substr._Equal("client") || substr._Equal("Client"))
		return CLIENT; // return 40

	if (substr._Equal("server") || substr._Equal("Server"))
		return SERVER; // return 30

	// case "wrong mode"
	return REPORT_CODES::UNRECOGNIZABLE_MODE;
}