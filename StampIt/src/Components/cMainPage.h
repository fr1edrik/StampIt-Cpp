#pragma once
#include "wx/wx.h"
#include "../HotkeyHandler/HotKeyHandler.h"

class cMainPage : public wxFrame
{
public:
	cMainPage();
	~cMainPage();

protected:
	wxChoice* m_choice1;
	wxTextCtrl* m_textCtrl1;
	wxButton* m_button1;

public:
	void OnApplyBtnClicked(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
	
private:
	std::unique_ptr<HotkeyHandler> hotkeyHandler_ = nullptr;
	void SetupUI();
};

