#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/datetime.h>
#include <wx/timer.h>
#include <wx/grid.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

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

	void OnClickAdd(wxCommandEvent& event);
	void OnClickSearch(wxCommandEvent& event);

	void DisplayRentals(vector<vector<string>> allRentals);
	void OnGridCellClick(wxGridEvent& event);
	vector<string> GetSelectedRowValues();

	void OnClickPay(wxCommandEvent& event);

	void OnClickRaport(wxCommandEvent& event);

	void Available();

	void OnClickBack(wxCommandEvent& evt);

	wxPanel* panel;

	wxTimer timer;
	wxStaticText* dateTimeDisplay;

	wxTextCtrl* name;
	wxTextCtrl* phone;
	wxChoice* place;
	wxButton* raport;
	
	wxSpinCtrl* mountain_bikes;
	wxSpinCtrl* touring_bikes;
	wxSpinCtrl* gravel_bikes;
	wxSpinCtrl* enduro_bikes;
	wxStaticText* labelBike1;
	wxStaticText* labelBike2;
	wxStaticText* labelBike3;
	wxStaticText* labelBike4;

	wxButton* search;
	wxButton* add;
	wxButton* pay;

	wxButton* back;

	wxBoxSizer* mainSizer;
	wxBoxSizer* formSizer;
	wxBoxSizer* formSizer2;
	wxBoxSizer* buttonSizer;

	wxGrid* grid;
};

