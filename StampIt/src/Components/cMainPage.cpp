#include "cMainPage.h"
#include <future>

wxBEGIN_EVENT_TABLE(cMainPage, wxFrame)
EVT_BUTTON(10001, OnApplyBtnClicked)
wxEND_EVENT_TABLE(cMainPage, wxFrame)

cMainPage::cMainPage() : wxFrame(nullptr, wxID_ANY, "Stamp It!", wxPoint(30, 30), wxSize(300, 350))
{
	hotkeyHandler_ = std::make_unique<HotkeyHandler>(HotkeyHandler());

	SetupUI();
}

cMainPage::~cMainPage()
{
	hotkeyHandler_.reset();
}
void cMainPage::OnApplyBtnClicked(wxCommandEvent& evt)
{
	if (hotkeyHandler_ == nullptr) {
		evt.Skip();
		return;
	};

	//if (hotkeyHandler->RegisterNewHotKey(VkKeyScanW('a'))) {
	//	wxMessageBox("Success");
	//}

	evt.Skip();
}

void cMainPage::SetupUI()
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxArrayString m_choice1Choices;
	m_choice1 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0);
	m_choice1->SetSelection(0);
	bSizer2->Add(m_choice1, 0, wxALL, 5);

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_textCtrl1, 0, wxALL, 5);

	m_button1 = new wxButton(this, 10001, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button1, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

}
