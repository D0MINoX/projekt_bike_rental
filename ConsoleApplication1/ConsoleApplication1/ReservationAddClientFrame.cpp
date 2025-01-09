#include "ReservationAddClientFrame.h"
#include "Reservations.h"
#include "ClientMenuFrame.h"
#include "ClientFrame.h"
#include "Client.h"
#include "bikes.h"
#include <fstream>

Client client;

ReservationAddClientFrame::ReservationAddClientFrame(wxWindow* parent,wxString phone1) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600))
{
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	main = new wxBoxSizer(wxHORIZONTAL);
	nameCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 25));
	dateCtrl = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize(200, 25));
	enduroCtrl = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 25));
	mountainCtrl = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 25));
	gravelCtrl = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 25));
	touringCtrl = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 25));
	submitButton = new wxButton(panel, wxID_ANY, wxT("Zarezerwuj"), wxDefaultPosition, wxSize(200, 30));
	backButton = new wxButton(panel, wxID_ANY, "Wstecz", wxDefaultPosition, wxSize(100, 35));
	
	form = new wxBoxSizer(wxVERTICAL);
	
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Imiê")), 0, wxALL, 5);
	form->Add(nameCtrl, 0, wxALL, 5);
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Numer telefonu:")), 0, wxALL, 5);
	form->Add(new wxStaticText(panel, wxID_ANY, phone1), 0, wxALL, 5);
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Data")), 0, wxALL, 5);
	form->Add(dateCtrl, 0, wxALL, 5);
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Iloœæ rowerów enduro")), 0, wxALL, 5);
	form->Add(enduroCtrl, 0, wxALL, 5); 
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Iloœæ rowerów elektrycznych")), 0, wxALL, 5);
	form->Add(mountainCtrl, 0, wxALL, 5);
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Iloœæ rowerów gravel")), 0, wxALL, 5);
	form->Add(gravelCtrl, 0, wxALL, 5);
	form->Add(new wxStaticText(panel, wxID_ANY, wxT("Iloœæ rowerów turystycznych")), 0, wxALL, 5);
	form->Add(touringCtrl, 0, wxALL, 5); form->Add(submitButton, 0, wxALL, 5);
	form->Add(backButton, 0, wxALL, 5);
	
	info = new wxBoxSizer(wxVERTICAL); 
	
	info->Add(new wxStaticText(panel, wxID_ANY, wxT("Rower górski: 40 z³")), 0, wxALL, 5);
	info->Add(new wxStaticText(panel, wxID_ANY, wxT("Rower enduro: 55 z³")), 0, wxALL, 5); 
	info->Add(new wxStaticText(panel, wxID_ANY, wxT("Rower gravel: 35 z³")), 0, wxALL, 5);
	info->Add(new wxStaticText(panel, wxID_ANY, wxT("Rower turystyczny: 30 z³")), 0, wxALL, 5);
	
	main->Add(form, 1, wxALL | wxEXPAND, 10);
	main->Add(info, 1, wxALL | wxEXPAND, 10);
	
	panel->SetSizerAndFit(main);
	phone = phone1;
	BindEventHandler();
} 

void ReservationAddClientFrame::BindEventHandler() {
	submitButton->Bind(wxEVT_BUTTON, &ReservationAddClientFrame::OnSubmit, this);
	backButton->Bind(wxEVT_BUTTON,&ReservationAddClientFrame::BackButton, this);
}
void ReservationAddClientFrame::OnSubmit(wxCommandEvent& event)
{

	bikes bikes;
	wxString name = nameCtrl->GetValue();
	wxString date = dateCtrl->GetValue().Format("%d-%m-%Y");
	int b4 = enduroCtrl->GetValue();
	int b1 = mountainCtrl->GetValue();
	int b3 = gravelCtrl->GetValue();
	int b2 = touringCtrl->GetValue();
	vector<string>available=bikes.CheckBikes(date.ToStdString());
	if (stoi(available[0]) >= b1 && stoi(available[1]) >= b2 && stoi(available[2]) >= b3 && stoi(available[3]) >= b4) {
		wxString message;
		int price = b4 * 55 + b1 * 40 + b2 * 30 + b3 * 35;
		message.Printf("Rezerwacja dokonana!\nImiê: %s\nNumer telefonu: %s\nData: %s\nIloœæ rowerów górskich: %d\nIloœæ rowerów turystycznych: %d\nIloœæ rowerów gravel: %d\nIloœæ rowerów enduro: %d\nKwota do zap³aty: %d ", name, phone, date, b1, b2, b3, b4,price);
		Reservations res;
		res.SaveReservationToFile(name, phone, date, b1, b2, b3, b4);
		wxMessageBox(message, "Potwierdzenie", wxOK | wxICON_INFORMATION);


		bikes.DelBikes(b1, b2, b3, b4, date.ToStdString());
		if (panel) {
			panel->Destroy();
		}

		panel = new ClientMenuFrame(this, phone);
		panel->SetSize(this->GetClientSize());
		Layout();
	}
	else {
		if (stoi(available[0]) < b1) wxMessageBox("przekroczono limit rowerów górskich maks." + available[0], "Potwierdzenie", wxOK | wxICON_INFORMATION);
		if (stoi(available[1]) < b2) wxMessageBox("przekroczono limit rowerów turystycznych maks." + available[1], "Potwierdzenie", wxOK | wxICON_INFORMATION);
		if (stoi(available[2]) < b3) wxMessageBox("przekroczono limit rowerów gravel maks." + available[2], "Potwierdzenie", wxOK | wxICON_INFORMATION);
		if (stoi(available[3]) < b4) wxMessageBox("przekroczono limit rowerów enduro maks." + available[3], "Potwierdzenie", wxOK | wxICON_INFORMATION);
	}

	
}

void ReservationAddClientFrame::BackButton(wxCommandEvent& event)
{
	if (panel) {
		panel->Destroy();
	}

	panel = new ClientMenuFrame(this, phone);
	panel->SetSize(this->GetClientSize());
	Layout();

}


