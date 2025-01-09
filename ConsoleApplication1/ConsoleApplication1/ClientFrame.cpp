#include "ClientFrame.h"
#include "Client.h"
#include "MainMenuFrame.h"
#include "ClientMenuFrame.h"
#include <string>
#include"ClientRegisterFrame.h"

ClientFrame::ClientFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    CreateControls();
    BindEventHandlers();
}
void ClientFrame::CreateControls()
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
    header = new wxStaticText(panel, wxID_ANY, "Witaj w wypozyczalni!", wxDefaultPosition);
    labelLogin = new wxStaticText(panel, wxID_ANY, "Login:", wxDefaultPosition);
    login = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    labelPassword = new wxStaticText(panel, wxID_ANY, "Haslo:", wxDefaultPosition);
    password = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1), wxTE_PASSWORD);
    loginSubButton = new wxButton(panel, wxID_ANY, "Zaloguj", wxDefaultPosition, wxSize(100, 35));
    signinButton = new wxButton(panel, wxID_ANY, "Zarejestruj siê", wxPoint(390, 345), wxSize(100, 35));
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
    mainSizer->Add(signinButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_LEFT | wxALL, 5);


    panel->SetSizerAndFit(mainSizer);

    // Make the panel fill the frame
    this->SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(panel, 1, wxEXPAND);
}

void ClientFrame::BindEventHandlers()
{
    loginSubButton->Bind(wxEVT_BUTTON, &ClientFrame::OnButtonClick, this);
    panel->Bind(wxEVT_CHAR_HOOK, &ClientFrame::OnEnterPress, this);
    backButton->Bind(wxEVT_BUTTON, &ClientFrame::OnClickBack, this);  // Dodane obs³ugiwanie przycisku Wstecz
    signinButton->Bind(wxEVT_BUTTON, &ClientFrame::OnClickSign, this);  // Dodane obs³ugiwanie przycisku Wstecz

}



void ClientFrame::HandleLogIn()
{
    wxString loginValue = login->GetValue();
    wxString passwordValue = password->GetValue();
    
   
    Client client;
  
    
    string logInStatus = client.LogIn(string(loginValue), string(passwordValue));
    if (client.isLogged == true) {
        string phone = client.phone;
      
        HandleFrameSwap(phone);  // Po zalogowaniu przechodzimy do ClientMenuFrame
    }
    else {
        password->Clear();
        error = new wxStaticText(panel, wxID_ANY, logInStatus, wxPoint(0, 90));  // Wyœwietlamy komunikat o b³êdzie
    }
}
void ClientFrame::HandleFrameSwap(string phone)
{
    panel->Destroy();  // Zniszczenie kontrolek okna logowania

    // Tworzymy nowe okno menu pracownika
    panel = new ClientMenuFrame(this, phone);  // Zak³adaj¹c, ¿e WorkerMenuFrame jest odpowiednio zaimplementowane
    panel->SetSize(this->GetClientSize());  // Dopasowanie rozmiarów do okna
    Layout();  // Odœwie¿enie uk³adu
}


void ClientFrame::OnButtonClick(wxCommandEvent& evt) {
    HandleLogIn();
}

void ClientFrame::OnClickSign(wxCommandEvent& evt)
{
    panel->Destroy();  

    panel = new ClientRegisterFrame(this);  
    panel->SetSize(this->GetClientSize());  
    Layout();  
}

void ClientFrame::OnEnterPress(wxKeyEvent& evt)
{
    if (evt.GetKeyCode() == WXK_RETURN) {
        HandleLogIn();
    }
    else {
        evt.Skip();
    }
}



void ClientFrame::OnClickBack(wxCommandEvent& evt)
{
    if (panel) {
        panel->Destroy();
    }

    panel = new MainMenuFrame(this);
    panel->SetSize(this->GetClientSize());
    Layout();
}

