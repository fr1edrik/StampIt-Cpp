#include "HotKeyHandler.h"
#include <Windows.h>
#include <future>
#include "../FileHandler/FileHandler.h"
#include <sstream>
#include <chrono>
#include "../Util/Util.h"
#include "../Util/Constants.h"

HotkeyHandler::HotkeyHandler()
{

	std::packaged_task<void()> task([&] {StartUpdate(); });
	auto thread = std::thread(std::move(task));
	thread.detach();
}

HotkeyHandler::~HotkeyHandler()
{
	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL, 2);
}

void HotkeyHandler::StartUpdate()
{
	RegisterHotKey(
		NULL,
		Constants::TOGGLE_START_BTN,
		MOD_ALT | MOD_NOREPEAT,
		VkKeyScanA('a')
	);

	RegisterHotKey(
		NULL,
		Constants::TIMESTAMP_BTN,
		MOD_ALT | MOD_NOREPEAT,
		VkKeyScanA('b')
	);

	Update();
}

void HotkeyHandler::HandleClockEvent(bool& isClockActive, std::time_t& start, bool triggerStamp)
{
	std::time_t now = std::time(0);
	tm* localTime = localtime(&now);

	if (start == NULL) start = now;

	std::string dateStamp = Util::GetFormattedTimestamp(localTime, tfCLOCK | tfSECONDS);
	std::string yearStamp = Util::GetFormattedTimestamp(localTime, tfYEAR | tfMONTH | tfDAY);

	if (isClockActive && triggerStamp) {
		auto AddStamp = [&start](const std::string filePath) {
			std::time_t now = std::time(0);
			time_t diffInSeconds = static_cast<time_t>(difftime(mktime(localtime(&now)), start));
			tm* localTime = gmtime(&diffInSeconds);

			std::stringstream strBuffer;

			constexpr auto Format = &Util::GetParsedTime;
			constexpr auto indendToken = "     ";
			strBuffer << indendToken << Format(localTime->tm_hour) << ":" << Format(localTime->tm_min) << ":" << Format(localTime->tm_sec);

			FileHandler::WriteFile(filePath.c_str(), strBuffer.str().c_str());
		};

		AddStamp(yearStamp);

		return;
	}

	if (!isClockActive) {
		FileHandler::WriteFile(yearStamp.c_str(), (dateStamp+">").c_str());
		isClockActive = true;
	}
	else
	{
		FileHandler::WriteFile(yearStamp.c_str(), ("<"+dateStamp).c_str());
		start = NULL;
		delete localTime;
		isClockActive = false;
	}

	PlaySound(L"MouseClick", NULL, SND_SYNC);
}

void HotkeyHandler::Update()
{
	bool isClockActive = false;
	std::time_t start = NULL;

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY) {

			switch (msg.wParam)
			{
			case Constants::Buttons::TOGGLE_START_BTN:
				HandleClockEvent(isClockActive, start, false);
				break;

			case Constants::Buttons::TIMESTAMP_BTN:
				if (!isClockActive)break;
				HandleClockEvent(isClockActive, start, true);
				break;

			default:
				break;
			}
		}
	}
}
