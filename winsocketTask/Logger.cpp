#include "Logger.h"

// outputs logged event flag to console
void output(const REPORT_CODES code, const std::string message)
{
	std::vector<std::string> codes
	{ 
		"UNRECOGNIZABLE_MODE",
	    "INVALID_CLIENT",
	    "WSA_STARTUP_FAIL",
	    "MISSING_SERVER",
	    "CONNECTION_FAIL",
	    "SUCCESSFUL_CONNECTION",
	    "MESSAGE_IS_SENT",
		"MESSAGE_WASNT_SEND",
		"FILE_OPEN_FAIL",
		"CLIENT_DISCONNECTED",
		"GET_INSTANCE_FAIL"
	};

	std::cout << codes[code] << ": " << message << '\n';
}