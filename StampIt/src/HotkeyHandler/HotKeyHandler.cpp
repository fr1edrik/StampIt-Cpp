#include "HotKeyHandler.h"
#include <Windows.h>
#include <future>
#include "../FileHandler/FileHandler.h"
#include <sstream>
#include <chrono>
#include "../Util/Util.h"

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
		3,
		MOD_ALT | MOD_NOREPEAT,
		VkKeyScanA('a')
	);

	RegisterHotKey(
		NULL,
		3,
		MOD_ALT | MOD_NOREPEAT,
		VkKeyScanA('b')
	);

	Update();
}

void HotkeyHandler::HandleCLockEvent(bool& isClockActive)
{
	std::time_t now = std::time(0);
	tm* localTime = localtime(&now);

	std::string dateStamp = Util::GetFormattedTimestamp(localTime, tfCLOCK | tfSECONDS);
	std::string yearStamp = Util::GetFormattedTimestamp(localTime, tfYEAR | tfMONTH | tfDAY);

	if (!isClockActive) {
		FileHandler::WriteFile(yearStamp.c_str(), dateStamp.c_str(), false);
		isClockActive = true;
	}
	else
	{
		FileHandler::WriteFile(yearStamp.c_str(), dateStamp.c_str(), true);
		isClockActive = false;
	}

	PlaySound(L"MouseClick", NULL, SND_SYNC);
}

void HotkeyHandler::Update()
{
	bool isClockActive = false;
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY) {
			HandleCLockEvent(isClockActive);
		}
	}
}
