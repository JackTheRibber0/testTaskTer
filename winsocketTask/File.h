#ifndef FILE_H
#define FILE_H


#include "common.h"

#include "Logger.h"

// костыль для разрешения создания нового сервера
static void clearFile()
{
	std::ofstream oStream;

	oStream.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);
	oStream.close();
}

// костыль для запрета создания второго сервера
static void fileWrite(const std::string message)
{
	std::ofstream oFile;

	oFile.open(FILE_NAME, std::ofstream::in);
	oFile << message;
	oFile.close();
}

// костыль для проверки на созданный сервер
static std::string fileRead()
{
	std::string line;
	std::ifstream iFile(FILE_NAME);

	if (iFile.is_open())
	{
		std::getline(iFile, line);
	}
	else
	{
		std::ofstream oFile{ FILE_NAME };
		oFile.close();
	}

	iFile.close();

	return line;
}

#endif