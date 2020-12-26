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
	void HandleCLockEvent(bool& isClockActive);

};

