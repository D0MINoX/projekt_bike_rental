#pragma once
#include <wx/wx.h>
#include "WorkerMenuFrame.h"
#include <wx/datectrl.h>
#include <wx/spinctrl.h>
class ReservationAddClientFrame:public wxPanel
{
public:
	ReservationAddClientFrame(wxWindow* parent,wxString phone);
private: 
	void BindEventHandler();
	void OnSubmit(wxCommandEvent& event);
	void BackButton(wxCommandEvent& event);
	
	wxButton* submitButton;
	wxButton* backButton;
	wxPanel* panel;
	wxTextCtrl* nameCtrl;
	wxTextCtrl* phoneCtrl;
	wxDatePickerCtrl* dateCtrl;
	wxSpinCtrl* enduroCtrl;
	wxSpinCtrl* mountainCtrl;
	wxSpinCtrl* gravelCtrl;
	wxSpinCtrl* touringCtrl;
	wxBoxSizer* info;
	wxBoxSizer* form;
	wxBoxSizer* main;
	std::string phone;
};

