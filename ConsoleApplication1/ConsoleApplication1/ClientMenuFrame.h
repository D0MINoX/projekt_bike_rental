#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include<vector>
class ClientMenuFrame:public wxPanel
{
public:
	ClientMenuFrame(wxWindow* parent, std::string phone);
private:
	void CreateControls();
	void BindEventHandlers();
	void AddReservation(wxCommandEvent& event);
	void BackButton(wxCommandEvent& event);
	std::vector<std::vector<std::string>> reservations_phone(std::string phone);
	void DisplayData(std::vector<std::vector<std::string>> dane);
	void delReservations(wxCommandEvent& event);
	std::vector<std::vector<std::string>> GetGridVal();
	
	wxPanel* panel;
	
	wxStaticText* header;
	
	wxButton* addButton;
	wxButton* delButton;
	wxButton* backButton;

	wxBoxSizer* buttonSizer;
	wxBoxSizer* headerSizer;
	wxBoxSizer* sizer;
	
	wxGrid* grid;
	
};

