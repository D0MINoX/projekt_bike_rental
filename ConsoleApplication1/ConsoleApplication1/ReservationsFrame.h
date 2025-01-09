#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/datetime.h>
#include <wx/timer.h>
#include <wx/grid.h>
#include <vector>
#include <string>
#include <wx/datectrl.h>
#include <wx/dateevt.h>

using namespace std;

class ReservationsFrame : public wxPanel
{
public:
	ReservationsFrame(wxWindow* parent);
private:
	void CreateControls();
	void BindEventHandlers();

	void DisplayTime();
	void OnTimer(wxTimerEvent& event);

	void OnClickAdd(wxCommandEvent& event);
	void OnClickSearch(wxCommandEvent& event);

	void DisplayRes(vector<vector<string>> allRes);

	void OnClickRemove(wxCommandEvent& event);
	vector<vector<string>> GetGridVal();

	void OnClickRent(wxCommandEvent& evt);

	void Available(wxString& selectedDate);

	void OnClickBack(wxCommandEvent& evt);

	void OnChangeDate(wxDateEvent& event);
	
	wxTimer timer;
	wxStaticText* dateTimeDisplay;

	wxPanel* panel;
	wxTextCtrl* name;
	wxTextCtrl* phone;
	wxSpinCtrl* mountain_bikes;
	wxSpinCtrl* touring_bikes;
	wxSpinCtrl* gravel_bikes;
	wxSpinCtrl* enduro_bikes;
	wxDatePickerCtrl* date;
	wxButton* search;
	wxButton* add;
	wxButton* remove;
	wxButton* rent;

	wxChoice* place;

	wxStaticText* labelBike1;
	wxStaticText* labelBike2;
	wxStaticText* labelBike3;
	wxStaticText* labelBike4;

	wxStaticText* spacer;
	
	wxBoxSizer* sizerForm;
	wxBoxSizer* sizerForm2;
	wxBoxSizer* sizerButton;
	wxBoxSizer* sizer;
	wxGrid* grid;

	wxButton* back;
};

