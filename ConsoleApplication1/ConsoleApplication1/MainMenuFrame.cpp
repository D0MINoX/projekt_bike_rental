#include "MainMenuFrame.h"
#include "LogInFrame.h"
#include "ClientFrame.h"

MainMenuFrame::MainMenuFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    CreateControls();
    BindEventHandlers();
}
//konfigurowanie GUI
void MainMenuFrame::CreateControls() {
    workerButton = new wxButton(this, wxID_ANY, "Pracownik", wxPoint(50, 50), wxSize(200, 40));
    clientButton = new wxButton(this, wxID_ANY, "Klient", wxPoint(50, 100), wxSize(200, 40));
   
    wxPNGHandler* handler = new wxPNGHandler;
    wxImage::AddHandler(handler);
    wxImage logoImage("logo.png", wxBITMAP_TYPE_PNG);
    logoImage.Rescale(250, 250);
    wxStaticBitmap* image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(logoImage), wxDefaultPosition, wxSize(250, 250));
    buttonSizer = new wxBoxSizer(wxVERTICAL);
    buttonSizer->Add(workerButton, 0, wxALL, 5);
    buttonSizer->Add(clientButton, 0, wxALL, 5);
   
    wxFont titleFont = wxFont(24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    name = new wxStaticText(this, wxID_ANY, "Wypo¿yczalnia");
    name->SetFont(titleFont);

    wxString openingHours = "Poniedzia³ek - Czwartek: 10:00 - 20:00\n" "Pi¹tek: 10:00 - 22:00\n" "Sobota - Niedziela: 8:00 - 22:00";
    openingHoursText = new wxStaticText(this, wxID_ANY, openingHours);
    infoSizer = new wxBoxSizer(wxVERTICAL);
    infoSizer = new wxBoxSizer(wxVERTICAL); 
    infoSizer->Add(image, 0, wxALIGN_CENTER | wxALL, 5);
    infoSizer->Add(name, 0, wxALIGN_CENTER | wxALL, 5);
    infoSizer->Add(openingHoursText, 0, wxALIGN_CENTER | wxALL, 5);

    Sizer = new wxBoxSizer(wxHORIZONTAL);
    Sizer->Add(buttonSizer, 0, wxALIGN_LEFT | wxALL, 5);
    Sizer->Add(infoSizer, 1, wxALIGN_CENTER | wxALL, 5); 

    this->SetSizerAndFit(Sizer);
}
// Powi¹zanie obs³ugi zdarzeñ z odpowiednimi kontrolkami
void MainMenuFrame::BindEventHandlers() {
    workerButton->Bind(wxEVT_BUTTON, &MainMenuFrame::OnClickWorker, this);
    clientButton->Bind(wxEVT_BUTTON, &MainMenuFrame::OnClickClient, this);
}
// Obs³uguje klikniêcie przycisku Pracownik
void MainMenuFrame::OnClickWorker(wxCommandEvent& evt) {
    this->Hide();

    LogInFrame* logInPanel = new LogInFrame(GetParent());
    logInPanel->SetSize(GetParent()->GetClientSize());
    logInPanel->Show();
}
// Obs³uguje klikniêcie przycisku Klient
void MainMenuFrame::OnClickClient(wxCommandEvent& evt) {
    this->Hide();

    ClientFrame* clientPanel = new ClientFrame(GetParent());
    clientPanel->SetSize(GetParent()->GetClientSize());
    clientPanel->Show();
}
