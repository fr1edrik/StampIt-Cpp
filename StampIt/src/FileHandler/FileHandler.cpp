#include "FileHandler.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <algorithm>

#include <wx/wx.h>

const static std::string basePath = std::string(getenv("USERPROFILE")) + "\\Desktop\\";

void FileHandler::WriteFile(const char* relativeFilePath = "", const char* content = "", const bool timeEnded = false)
{
	if (strlen(content) == 0) return;

	const char* endl = timeEnded ? "\n" : " - ";

	auto pathWQualifier = std::string(relativeFilePath) + ".txt";

	std::replace(pathWQualifier.begin(), pathWQualifier.end(), ':', '_');

	auto fullPath = basePath + pathWQualifier;

	std::ofstream file;

	try
	{
		file.open(fullPath, std::ios::app);
		file << content << endl;
		file.close();
	}
	catch (const std::exception& e)
	{
		wxMessageBox(e.what());
		file.close();
	}
}
