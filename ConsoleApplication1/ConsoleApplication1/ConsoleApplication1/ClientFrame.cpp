#include <wx/wx.h>
#include "ClientFrame.h"
#include "Client.h"
#include "MainMenuFrame.h"
#include "ClientMenuFrame.h"
#include <string>


using namespace std;

ClientFrame::ClientFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    CreateControls();
    BindEventHandlers();
}
vector<std::string> ClientFrame::Slice5(const std::string& tekst) { //funkcja rodzielajaca string po spacji
    vector<std::string> wyniki;
    istringstream iss(tekst);
    std::string slowo;

    while (iss >> slowo) {
        wyniki.push_back(slowo);
    }

    return wyniki;
}
void ClientFrame::CreateControls()
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

void ClientFrame::BindEventHandlers()
{
    loginSubButton->Bind(wxEVT_BUTTON, &ClientFrame::OnButtonClick, this);
    this->Bind(wxEVT_CHAR_HOOK, &ClientFrame::OnEnterPress, this);
    backButton->Bind(wxEVT_BUTTON, &ClientFrame::OnClickBack, this);  // Dodane obs³ugiwanie przycisku Wstecz

}
std::vector<std::vector<std::string>> ClientFrame::reservations_phone(std::string phone) {	//metoda podaj¹ca rezerwacje dla danej daty
    fstream File;
    File.open("reservations.txt", ios::in);
    std::vector<std::vector<std::string>> dane;
    if (File.good() == true) {
       
        std::string line;

        int res_num = 0;
        while (getline(File, line)) {
           vector<std::string>sliced_string = Slice5(line);// wektro z podzielonymi danymi rezerwacji
           
           if (sliced_string[1] == phone) {
               dane.push_back(sliced_string);

            }
        }
        File.clear();
        File.seekg(0, ios::beg);
        if (!res_num)cout << endl << "Brak rezerwacji" << endl;


        File.close();
       
    }
    return dane;
}



void ClientFrame::HandleLogIn()
{
    wxString loginValue = login->GetValue();
    wxString passwordValue = password->GetValue();
    vector<vector<std::string>> dane;
    
   
    Client client;
  
    
    std::string logInStatus = client.LogIn(string(loginValue), string(passwordValue));
    if (client.isLogged == true) {
        std::string phone = client.phone;
        dane = reservations_phone(phone);
        // vector<wxArrayString>dane =reservations_phone();
        HandleFrameSwap(dane);  // Po zalogowaniu przechodzimy do ClientMenuFrame
    }
    else {
        password->Clear();
        error = new wxStaticText(panel, wxID_ANY, logInStatus, wxPoint(0, 90));  // Wyœwietlamy komunikat o b³êdzie
    }
}

void ClientFrame::OnButtonClick(wxCommandEvent& evt) {
    HandleLogIn();
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

void ClientFrame::HandleFrameSwap(std::vector<std::vector<std::string>> dane)
{
    panel->Destroy();  // Zniszczenie kontrolek okna logowania

    // Tworzymy nowe okno menu pracownika
    panel = new ClientMenuFrame(this, dane);  // Zak³adaj¹c, ¿e WorkerMenuFrame jest odpowiednio zaimplementowane
    panel->SetSize(this->GetClientSize());  // Dopasowanie rozmiarów do okna
    Layout();  // Odœwie¿enie uk³adu
}


void ClientFrame::OnClickBack(wxCommandEvent& evt)
{

}

