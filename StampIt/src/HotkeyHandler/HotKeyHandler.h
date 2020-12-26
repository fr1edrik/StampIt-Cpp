#pragma once
#include "wx/wx.h"
#include <ctime>

class HotkeyHandler
{
public:
	HotkeyHandler();
	~HotkeyHandler();

public:
	void StartUpdate();

private:
	void Update();
	void HandleClockEvent(bool& isClockActive, std::time_t& start, bool triggerStamp);
};

