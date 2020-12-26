#pragma once
#include <string>

class FileHandler
{
public:
	static void WriteFile(const char* relativeFilePath, const char* content);
};

