#include "common.h"

#include "Logger.h"

#include "Client.h"
#include "Server.h"

#include "StringTools.h"

int main()
{
    WSAData data;
    WORD version = MAKEWORD(2, 1);

    int32_t wsaStartupRespond = NULL;
    wsaStartupRespond = WSAStartup(version, &data);

    if (wsaStartupRespond != NULL) {

        WSA_START_FAIL(REPORT_CODES::WSA_STARTUP_FAIL, "MAIN: " + WSAGetLastError());
    }

    std::string userInput;
    std::getline(std::cin, userInput);

    uint8_t decision = stringTools::GetMode(userInput);

    // server launch mode
    if (decision == 30)
    {
        net::Server* serverPointer = net::Server::getInstance("127.0.0.1", 450);

        if (serverPointer == nullptr)
        {
            FAILED_TO_GET_SERVER_INSTANCE(REPORT_CODES::GET_INSTANCE_FAIL, "MAIN: Failed to get server instance!");
            Sleep(4000);
            return -1;
        }

        serverPointer->main();
        clearFile();

        return 1;
    }

    // client launch mode
    else if (decision == 40)
    {
        auto client = net::Client("127.0.0.1", 450);

        if (!client.connectToServer())
        {
            Sleep(4000);

            return -1;
        }

        std::string tMsg = stringTools::GetMessageText(userInput);
        client.main(tMsg);

        return 1;
    }

    MODE_ERROR(REPORT_CODES::UNRECOGNIZABLE_MODE, "MAIN: Unrecognized mode input!");
    Sleep(4000);

    return -1;
}