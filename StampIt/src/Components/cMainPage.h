#pragma once
#include "wx/wx.h"
#include "../HotkeyHandler/HotKeyHandler.h"

class cMainPage : public wxFrame
{
public:
	cMainPage();
	~cMainPage();

protected:
	wxButton* m_button3;
	wxChoice* m_choice2;
	wxButton* m_button1;

public:
	void OnSaveBtnClicked(wxCommandEvent& evt);
	void OnHotkeyBtnClicked(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
	
private:
	std::unique_ptr<HotkeyHandler> HotkeyHandler_ = nullptr;
	void SetupUI();
};

