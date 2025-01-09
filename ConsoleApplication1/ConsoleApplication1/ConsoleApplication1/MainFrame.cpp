#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    CreateControls();  
}

void MainFrame::CreateControls() {

    mainMenu = new MainMenuFrame(this);
    mainMenu->SetSize(this->GetClientSize());  
    mainMenu->Show(true); 
}
