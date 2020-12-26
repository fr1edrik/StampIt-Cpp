#include "cApp.h"
#include "Components/cMainPage.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	cMainPage* mainPage = new cMainPage();
	mainPage->Show();

	return true;
}
