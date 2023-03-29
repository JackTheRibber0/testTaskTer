#ifndef LOGGERFILE_H
#define LOGGERFILE_H


#include "common.h"

const enum REPORT_CODES
{
	UNRECOGNIZABLE_MODE,
	INVALID_CLIENT,
	WSA_STARTUP_FAIL,
	MISSING_SERVER,
	CONNECTION_FAIL,
	SUCCESSFUL_CONNECTION,
	MSG_IS_SENT,
	MSG_WASNT_SEND,
	FILE_OPEN_FAIL,
	CLIENT_DISCONNECTION,
	GET_INSTANCE_FAIL
};

void output(const REPORT_CODES code, const std::string message);

// REPORT_CODES::code and str::string message
#define WSA_START_FAIL(code, msg) output(code, msg)

// REPORT_CODES::code and std::string message
#define MODE_ERROR(code, msg) output(code, msg)

// REPORT_CODES::code and std::string message
#define CONNECTION_FAILED(code, msg) output(code, msg)

// REPORT_CODES::code and std::string message
#define SERVER_ERROR(code, msg) output(code, msg)

// REPORT_CODES::code and std::string message
#define CLIENT_DISCONNECTED(code, msg) output(code, msg)

// REPORT_CODES::code and str::string message
#define CLIENT_CONNECTED(code, msg) output(code, msg)

// REPORT_CODES::code and str::string message
#define MESSAGE_SENT(code, msg) output(code, msg)

// REPORT_CODES::code and str::string message
#define FILE_WASNT_OPENED(code, msg) output(code, msg)

// REPORT_CODES::code and str::string message
#define FAILED_TO_GET_SERVER_INSTANCE(code, msg) output(code, msg)

#endif