#include "LogInFrame.h"
#include <wx/wx.h>
#include "Users.h"
#include "MainMenuFrame.h"



using namespace std;

LogInFrame::LogInFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    CreateControls();
    BindEventHandlers();
}

void LogInFrame::CreateControls()
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
    labelLogin = new wxStaticText(panel, wxID_ANY, "Login:", wxPoint(300, 250));
    login = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(340, 245), wxSize(200, -1));
    labelPassword = new wxStaticText(panel, wxID_ANY, "Haslo:", wxPoint(300, 280));
    password = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(340, 275), wxSize(200, -1), wxTE_PASSWORD);
    loginSubButton = new wxButton(panel, wxID_ANY, "Zaloguj", wxPoint(390, 305), wxSize(100, 35));
    backButton = new wxButton(panel, wxID_ANY, "Wstecz", wxPoint(1, 564), wxSize(100, 35));

    wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Witaj w wypozyczalni!", wxPoint(300, 10));
    wxFont fontHeader(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    staticText->SetFont(fontHeader);
}

void LogInFrame::BindEventHandlers()
{
    loginSubButton->Bind(wxEVT_BUTTON, &LogInFrame::OnButtonClick, this);
    panel->Bind(wxEVT_CHAR_HOOK, &LogInFrame::OnEnterPress, this);
    backButton->Bind(wxEVT_BUTTON, &LogInFrame::OnClickBack, this);
    
}



void LogInFrame::HandleLogIn()
{
    wxString loginValue = login->GetValue();
    wxString passwordValue = password->GetValue();

    Users user;
    string logInStatus = user.LogIn(string(loginValue), string(passwordValue));

    if (user.isLogged == true) {
        HandleFrameSwap(); 
    }
    else {
        password->Clear();
        error = new wxStaticText(panel, wxID_ANY, logInStatus, wxPoint(0, 90)); 
    }
}

void LogInFrame::OnButtonClick(wxCommandEvent& evt) {
    HandleLogIn();
}

void LogInFrame::OnEnterPress(wxKeyEvent& evt)
{
    if (evt.GetKeyCode() == WXK_RETURN) {
        HandleLogIn();
    }
    else {
        evt.Skip();
    }
}

void LogInFrame::HandleFrameSwap()
{
    panel->Destroy();  

    panel = new WorkerMenuFrame(this);  
    panel->SetSize(this->GetClientSize()); 
    Layout();  
}


void LogInFrame::OnClickBack(wxCommandEvent& evt)
{
    panel->Hide();

    panel = new MainMenuFrame(this); 
    panel->SetSize(this->GetClientSize());  
    Layout();

}

