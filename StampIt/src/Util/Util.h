#pragma once
#include <string>
#include <ctime>
#include <algorithm>

#define tfCLOCK		0b00000001
#define tfSECONDS	0b00000010
#define tfDAY		0b00000100
#define tfMONTH		0b00001000
#define tfYEAR		0b00010000

class Util
{
public:
	const static std::string GetFormattedTimestamp(const tm* localTime, short timeformat);
	const static std::string GetParsedTime(const int time);
private:
	Util();
	~Util();
};

