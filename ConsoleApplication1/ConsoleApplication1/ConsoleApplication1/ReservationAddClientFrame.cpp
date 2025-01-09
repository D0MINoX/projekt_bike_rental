#include "ReservationAddClientFrame.h"
#include "Reservations.h"
#include "ClientMenuFrame.h"
#include "ClientFrame.h"
#include "Client.h"
#include <fstream>
Client client;
ReservationAddClientFrame::ReservationAddClientFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
	new wxStaticText(this, wxID_ANY, wxT("Imiê"), wxPoint(20, 20));
	nameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(150, 20), wxSize(200, 25));
	new wxStaticText(this, wxID_ANY, wxT("Numer telefonu"), wxPoint(20, 60));
	phoneCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(150, 60), wxSize(200, 25));
	new wxStaticText(this, wxID_ANY, wxT("Data"), wxPoint(20, 100));
	dateCtrl = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(150, 100), wxSize(200, 25));
	new wxStaticText(this, wxID_ANY, wxT("Iloœæ rowerów enduro"), wxPoint(20, 140));
	enduroCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(150, 140), wxSize(200, 25)); 
	new wxStaticText(this, wxID_ANY, wxT("Iloœæ rowerów elektrycznych"), wxPoint(20, 180));
	electricCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(150, 180), wxSize(200, 25));
	new wxStaticText(this, wxID_ANY, wxT("Iloœæ rowerów gravel"), wxPoint(20, 220));
	gravelCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(150, 220), wxSize(200, 25)); 
	new wxStaticText(this, wxID_ANY, wxT("Iloœæ rowerów turystycznych"), wxPoint(20, 260));
	touringCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(150, 260), wxSize(200, 25));
	wxButton* submitButton = new wxButton(this, wxID_ANY, wxT("Zarezerwuj"), wxPoint(150, 300), wxSize(200, 30));
	Connect(submitButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ReservationAddClientFrame::OnSubmit));
} 
void ReservationAddClientFrame::OnSubmit(wxCommandEvent& event)
{
	wxString name = nameCtrl->GetValue();
	wxString phone = phoneCtrl->GetValue();
	wxDateTime date = dateCtrl->GetValue();
	int enduroBikes = enduroCtrl->GetValue();
	int electricBikes = electricCtrl->GetValue();
	int gravelBikes = gravelCtrl->GetValue();
	int touringBikes = touringCtrl->GetValue();
	wxString message;
	message.Printf("Rezerwacja dokonana!\nImiê: %s\nNumer telefonu: %s\nData: %s\nIloœæ rowerów enduro: %d\nIloœæ rowerów elektrycznych: %d\nIloœæ rowerów gravel: %d\nIloœæ rowerów turystycznych: %d", name, phone, date.FormatISODate(), enduroBikes, electricBikes, gravelBikes, touringBikes);
	Reservations res;
	res.SaveReservationToFile(name, phone, date, enduroBikes, electricBikes, gravelBikes, touringBikes);
	wxMessageBox(message, "Potwierdzenie", wxOK | wxICON_INFORMATION);

}


