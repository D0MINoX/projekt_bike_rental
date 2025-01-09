#pragma once
#include <wx/wx.h>
#include "WorkerMenuFrame.h"
#include <wx/datectrl.h>
#include <wx/spinctrl.h>
class ReservationAddClientFrame:public wxPanel
{
public:
	ReservationAddClientFrame(wxWindow* parent);
private: 
	void OnSubmit(wxCommandEvent& event);
	

	wxPanel* panel;
	wxTextCtrl* nameCtrl;
	wxTextCtrl* phoneCtrl;
	wxDatePickerCtrl* dateCtrl;
	wxSpinCtrl* enduroCtrl;
	wxSpinCtrl* electricCtrl;
	wxSpinCtrl* gravelCtrl;
	wxSpinCtrl* touringCtrl;
};

