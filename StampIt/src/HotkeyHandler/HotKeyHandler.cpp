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

//bool HotkeyHandler::RegisterNewHotKey(unsigned int key)
//{
//	if (RegisterHotKey(
//		NULL,
//		1,
//		MOD_ALT | MOD_NOREPEAT,
//		0x42
//	))
//	{
//		return true;
//	}
//
//	return false;
//}

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

void HotkeyHandler::HandleCLockEvent(bool& isClockActive,std::time_t start)
{
	std::time_t now = std::time(0);
	tm* localTime = localtime(&now);

	if (start == NULL) start = now;

	std::string dateStamp = Util::GetFormattedTimestamp(localTime, tfCLOCK | tfSECONDS);
	std::string yearStamp = Util::GetFormattedTimestamp(localTime, tfYEAR | tfMONTH | tfDAY);

	if (!isClockActive) {
		FileHandler::WriteFile(yearStamp.c_str(), dateStamp.c_str());
		isClockActive = true;
	}
	else
	{
		FileHandler::WriteFile(yearStamp.c_str(), dateStamp.c_str());
		start = NULL;
		delete localTime;
		isClockActive = false;
	}

	PlaySound(L"MouseClick", NULL, SND_SYNC);
}

const void HotkeyHandler::AddStamp(const std::time_t start)
{
	std::time_t now = std::time(0);
	difftime(start, mktime(localtime(&now)));
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
				HandleCLockEvent(isClockActive, start);
				break;

			case Constants::Buttons::TIMESTAMP_BTN:
				if (!isClockActive)break;

				AddStamp(start);
				break;

			default:
				break;
			}
		}
	}
}
