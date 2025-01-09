#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/datetime.h>
#include <wx/timer.h>
#include <wx/grid.h>

using namespace std;

class RentalsFrame :public wxPanel
{
public:
	RentalsFrame(wxWindow* parent);
private:
	void CreateControls();
	void BindEventHandlers();

	void DisplayTime();
	void OnTimer(wxTimerEvent& event);

	void DisplayRentals(vector<std::vector<std::string>> allRentals);
	void OnGridCellClick(wxGridEvent& event);
	vector<string> GetSelectedRowValues();

	wxTimer timer;
	wxStaticText* dateTimeDisplay;

	wxTextCtrl* name;
	wxTextCtrl* phone;
	
	wxSpinCtrl* mountain_bikes;
	wxSpinCtrl* touring_bikes;
	wxSpinCtrl* gravel_bikes;
	wxSpinCtrl* enduro_bikes;
	wxStaticText* labelBike1;
	wxStaticText* labelBike2;
	wxStaticText* labelBike3;
	wxStaticText* labelBike4;

	wxButton* search;
	wxButton* pay;

	wxBoxSizer* mainSizer;
	wxBoxSizer* formSizer;
	wxBoxSizer* formSizer2;
	wxBoxSizer* buttonSizer;

	wxGrid* grid;
};

