#pragma once
#include "wx/wx.h"
#include <ctime>

class HotkeyHandler
{
public:
	HotkeyHandler();
	~HotkeyHandler();

public:
	//bool RegisterNewHotKey(unsigned int key);
	void StartUpdate();

private:
	void Update();
	void HandleClockEvent(bool& isClockActive, std::time_t& start, bool triggerStamp);
	//const void AddStamp(const std::time_t& start);
};

