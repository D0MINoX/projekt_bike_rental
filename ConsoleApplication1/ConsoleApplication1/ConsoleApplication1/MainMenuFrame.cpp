#include "MainMenuFrame.h"
#include "LogInFrame.h"
#include "ClientFrame.h"

MainMenuFrame::MainMenuFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    CreateControls();
    BindEventHandlers();
}

void MainMenuFrame::CreateControls() {
    workerButton = new wxButton(this, wxID_ANY, "Pracownik", wxPoint(50, 50), wxSize(200, 40));
    clientButton = new wxButton(this, wxID_ANY, "Klient", wxPoint(50, 100), wxSize(200, 40));
    
    buttonSizer = new wxBoxSizer(wxVERTICAL);
    buttonSizer->Add(workerButton, 0, wxALL, 5);
    buttonSizer->Add(clientButton, 0, wxALL, 5);

    name = new wxStaticText(this,wxID_ANY , "Wypo¿yczalnia");
    wxImage logoImage(wxT("resources/logo.png"), wxBITMAP_TYPE_PNG);
    wxBitmap logoBitmap(logoImage);
    logo = new wxStaticBitmap(this, wxID_ANY, logoBitmap);

    infoSizer = new wxBoxSizer(wxVERTICAL);
    infoSizer->Add(name, 0, wxALIGN_CENTER | wxALL, 5);
    infoSizer->Add(logo, 0, wxALIGN_CENTER | wxALL, 5);

    Sizer = new wxBoxSizer(wxHORIZONTAL);
    Sizer->Add(buttonSizer, 0, wxALIGN_LEFT | wxALL, 5);
    Sizer->Add(infoSizer, 0, wxALIGN_RIGHT | wxALL, 5);
    this->SetSizerAndFit(Sizer);
}

void MainMenuFrame::BindEventHandlers() {
    workerButton->Bind(wxEVT_BUTTON, &MainMenuFrame::OnClickWorker, this);
    clientButton->Bind(wxEVT_BUTTON, &MainMenuFrame::OnClickClient, this);
}

void MainMenuFrame::OnClickWorker(wxCommandEvent& evt) {
    this->Hide();

    LogInFrame* logInPanel = new LogInFrame(GetParent());
    logInPanel->SetSize(GetParent()->GetClientSize());
    logInPanel->Show();
}

void MainMenuFrame::OnClickClient(wxCommandEvent& evt) {
    this->Hide();

    ClientFrame* clientPanel = new ClientFrame(GetParent());
    clientPanel->SetSize(GetParent()->GetClientSize());
    clientPanel->Show();
}
