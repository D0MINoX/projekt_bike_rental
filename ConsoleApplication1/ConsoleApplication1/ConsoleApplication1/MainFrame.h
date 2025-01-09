#pragma once
#include <wx/wx.h>
#include "MainMenuFrame.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);  

private:
    void CreateControls();      
    MainMenuFrame* mainMenu;  
};
