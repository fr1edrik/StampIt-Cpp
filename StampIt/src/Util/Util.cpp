#include "Util.h"
#include <sstream>
#include <algorithm>

const std::string Util::GetFormattedTimestamp(const tm* localTime, short timeformat)
{
	std::stringstream strBuffer;
	bool isFirst = true;
	if (timeformat == 0) {
		timeformat = ~0;
	}

	auto handleFirst = [&isFirst, &strBuffer](const char character) mutable {
		if (!isFirst) strBuffer << character;
		if (isFirst) isFirst = false;
	};


	if ((timeformat & tfCLOCK) == tfCLOCK) {
		if (isFirst) isFirst = false;

		strBuffer << GetParsedTime(localTime->tm_hour) << ":" << GetParsedTime(localTime->tm_min);

		if ((timeformat & tfSECONDS) == tfSECONDS) {
			if (isFirst) isFirst = false;

			strBuffer << ":" <<GetParsedTime(localTime->tm_sec);
		}
	}



	if ((timeformat & tfDAY) == tfDAY)
	{
		handleFirst(' ');

		strBuffer << GetParsedTime(localTime->tm_mday);
	}

	if ((timeformat & tfMONTH) == tfMONTH)
	{
		handleFirst('-');
		auto month = std::clamp(localTime->tm_mon + 1, 1, 12);
		strBuffer << GetParsedTime(month);
	}

	if ((timeformat & tfYEAR) == tfYEAR)
	{
		handleFirst('-');

		strBuffer << localTime->tm_year + 1900;
	}

	return strBuffer.str();
}

const std::string Util::GetParsedTime(const int time)
{
	short upperBound = 9;
	std::stringstream strBuffer;

	if (time <= upperBound) {
		strBuffer << "0";
	}

	strBuffer << time;

	return strBuffer.str();
}


