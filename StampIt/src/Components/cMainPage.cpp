#include "cMainPage.h"
#include <future>

wxBEGIN_EVENT_TABLE(cMainPage, wxFrame)
EVT_BUTTON(10001, OnSaveBtnClicked)
EVT_BUTTON(10002, OnHotkeyBtnClicked)
wxEND_EVENT_TABLE(cMainPage, wxFrame)

cMainPage::cMainPage() : wxFrame(nullptr, wxID_ANY, "Stamp It!", wxPoint(30, 30), wxSize(300, 350))
{
	HotkeyHandler_ = std::make_unique<HotkeyHandler>(HotkeyHandler());

	SetupUI();
}

cMainPage::~cMainPage()
{
	HotkeyHandler_.reset();
}

void cMainPage::OnSaveBtnClicked(wxCommandEvent& evt)
{
	//if (hotkeyHandler_ == nullptr) {
	//	evt.Skip();
	//	return;
	//};

	//if (hotkeyHandler->RegisterNewHotKey(VkKeyScanW('a'))) {
	//	wxMessageBox("Success");
	//}

	evt.Skip();
}

void cMainPage::OnHotkeyBtnClicked(wxCommandEvent& evt)
{
	auto hotkeyDialog = new wxFrame(
		this,
		wxID_ANY,
		"Choose Button",
		this->GetPosition()
	);

	auto bSizer = new wxBoxSizer(wxVERTICAL);
	hotkeyDialog->SetSizer(bSizer);
	bSizer->Add(new wxStaticText(hotkeyDialog, wxID_ANY, "Choose Button"));

	hotkeyDialog->Show();

	auto waitForKey = [hotkeyDialog]() {
		MSG msg = { 0 };
		BOOL bRet;
		HACCEL haccel = { 0 };

		while ((bRet = GetMessage(&msg, hotkeyDialog->GetHWND(), 0, 0)) != 0) {

			if (bRet == -1) {

			}
			else
			{
				if (TranslateAccelerator(hotkeyDialog->GetHWND(), haccel, &msg))
				{
					wxMessageBox("Hallo welt");
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			//std::string s = std::to_string(msg.wParam);

			//switch (msg.Param)
			//{
			//case 

			//default:
			//	break;
			//}
		}
	};

	//std::async(std::launch::async, waitForKey);

	std::packaged_task<void()> task([this, &waitForKey] {waitForKey(); });
	auto thread = std::thread(std::move(task));
	thread.detach();

	evt.Skip();
}

void cMainPage::SetupUI()
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_button3 = new wxButton(this, 10002, wxT("B"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button3, 0, wxALL, 5);

	wxString m_choice2Choices[] = { wxT("Alt"), wxT("Ctrl"), wxT("Shift") };
	int m_choice2NChoices = sizeof(m_choice2Choices) / sizeof(wxString);
	m_choice2 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2NChoices, m_choice2Choices, 0);
	m_choice2->SetSelection(0);
	bSizer2->Add(m_choice2, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	m_button1 = new wxButton(this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_button1, 0, wxALL, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);
}
