#ifndef COMMONFILE_H
#define COMMONFILE_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")

#include <string>
#include <vector>
#include <iostream>

#include <future>
#include <mutex>

#include <winsock.h>
#include <WinSock2.h>
#include <fstream>

#include <memory>

#define SERVER 30;
#define CLIENT 40;
#define LOCAL_HOST "127.0.0.1";
#define PORT 450;

#define FILE_NAME "serverStatus.txt"

#endif