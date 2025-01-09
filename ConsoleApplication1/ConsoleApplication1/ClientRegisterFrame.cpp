#include "ClientRegisterFrame.h"
#include <fstream>
#include"MainMenuFrame.h"

ClientRegisterFrame::ClientRegisterFrame(wxWindow* parent): wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600))
{
	CreateControls();
	BindEventHandlers();
	
}
void ClientRegisterFrame::CreateControls() {
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

	
	sizer = new wxBoxSizer(wxVERTICAL);

	
	gridSizer = new wxFlexGridSizer(2, 5, 10); 
	gridSizer->AddGrowableCol(1, 1); 

	// Dodawanie etykiet i pól tekstowych do siatki
	gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Imiê"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	firstNameCtrl = new wxTextCtrl(panel, wxID_ANY);
	gridSizer->Add(firstNameCtrl, 1, wxEXPAND | wxALL, 5);

	gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Nazwisko"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	lastNameCtrl = new wxTextCtrl(panel, wxID_ANY);
	gridSizer->Add(lastNameCtrl, 1, wxEXPAND | wxALL, 5);

	gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Numer telefonu"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	phoneCtrl = new wxTextCtrl(panel, wxID_ANY);
	gridSizer->Add(phoneCtrl, 1, wxEXPAND | wxALL, 5);

	gridSizer->Add(new wxStaticText(panel, wxID_ANY, "Has³o"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	passwordCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	gridSizer->Add(passwordCtrl, 1, wxEXPAND | wxALL, 5);

	// Dodawanie siatki do g³ównego sizeru
	sizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 10);

	// Dodawanie przycisków pod siatk¹
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	submitButton = new wxButton(panel, wxID_ANY, "Zarejestruj");
	backButton = new wxButton(panel, wxID_ANY, "Wstecz");

	buttonSizer->Add(submitButton, 0, wxALL, 5);
	buttonSizer->Add(backButton, 0, wxALL, 5);

	sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

	panel->SetSizerAndFit(sizer);
}
void ClientRegisterFrame::BindEventHandlers()
{
	submitButton->Bind(wxEVT_BUTTON, &ClientRegisterFrame::Submit, this);
	backButton->Bind(wxEVT_BUTTON, &ClientRegisterFrame::BackButton, this);
}
void ClientRegisterFrame::BackButton(wxCommandEvent& event)
{
	if (panel) {
		panel->Destroy();
	}

	panel = new MainMenuFrame(this);
	panel->SetSize(this->GetClientSize());
	Layout();
}
void ClientRegisterFrame::BackButton()
{

	if (panel) {
		panel->Destroy();
	}

	panel = new MainMenuFrame(this);
	panel->SetSize(this->GetClientSize());
	Layout();
}
void ClientRegisterFrame::Submit(wxCommandEvent& event)
{
	std::fstream inputFile("clients.txt"); 
	int lineCount = 1;
	if (inputFile.is_open()) {
		std::string line;


		while (std::getline(inputFile, line)) {
			lineCount++;
		}

		inputFile.close();
	}
	wxString firstName = firstNameCtrl->GetValue();
	wxString lastName = lastNameCtrl->GetValue();
	wxString phone = phoneCtrl->GetValue();
	wxString password = passwordCtrl->GetValue();
	std::ofstream file("clients.txt", std::ios::app);
	if (file.is_open())
		{
			file << lineCount <<" "
				<< firstName.ToStdString() << " "
				<< lastName.ToStdString() << " "
				<< phone.ToStdString() << " "
				<< password.ToStdString() << " " << std::endl;
			file.close();
			wxString message; message.Printf("Rejestracja dokonana!\nImiê: %s\nNazwisko: %s\nNumer telefonu: %s\nHas³o: %s", firstName, lastName, phone, password);
			wxMessageBox(message, "Potwierdzenie", wxOK | wxICON_INFORMATION);
			BackButton();
		}
	else {
			wxMessageBox("B³¹d rejestracji!", "B³¹d", wxOK | wxICON_ERROR);
		}
		
	
}
