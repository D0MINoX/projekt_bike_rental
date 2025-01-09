#include "App.h"
#include "MainMenuFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* frame = new MainFrame("MENU");
	frame->SetClientSize(800, 600);
	frame->Show();

	return true;
}
