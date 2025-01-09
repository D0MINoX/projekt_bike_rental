#include "LogInFrame.h"
#include <wx/wx.h>
#include "Workers.h"
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
    header = new wxStaticText(panel, wxID_ANY, "Witaj w wypozyczalni!", wxDefaultPosition);
    labelLogin = new wxStaticText(panel, wxID_ANY, "Login:", wxDefaultPosition);
    login = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    labelPassword = new wxStaticText(panel, wxID_ANY, "Haslo:", wxDefaultPosition);
    password = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1), wxTE_PASSWORD);
    loginSubButton = new wxButton(panel, wxID_ANY, "Zaloguj", wxDefaultPosition, wxSize(100, 35));
    backButton = new wxButton(panel, wxID_ANY, "Wstecz", wxDefaultPosition, wxSize(100, 35));
    error = new wxStaticText(panel, wxID_ANY, "");

    wxFont fontHeader(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    header->SetFont(fontHeader);

    mainSizer = new wxBoxSizer(wxVERTICAL);
    formSizer = new wxBoxSizer(wxHORIZONTAL);
    formSizer2 = new wxBoxSizer(wxHORIZONTAL);

    formSizer->Add(labelLogin, 0, wxALL, 5);
    formSizer->Add(login, 0, wxALL, 5);
    formSizer2->Add(labelPassword, 0, wxALL, 5);
    formSizer2->Add(password, 0, wxALL, 5);

    mainSizer->Add(header, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    mainSizer->Add(error, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    mainSizer->Add(formSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    mainSizer->Add(formSizer2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    mainSizer->Add(loginSubButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_LEFT | wxALL, 5);


    panel->SetSizerAndFit(mainSizer);

    // Make the panel fill the frame
    this->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel, 1, wxEXPAND);

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

    Workers user;
    string logInStatus = user.LogIn(string(loginValue), string(passwordValue));

    if (user.isLogged == true) {
        HandleFrameSwap(); 
    }
    else {
        password->Clear();
        error->SetLabel(logInStatus);
        Layout();
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
    panel->Destroy();

    panel = new MainMenuFrame(this); 
    panel->SetSize(this->GetClientSize());  
    Layout();
}