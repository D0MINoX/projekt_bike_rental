#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include<vector>
class ClientMenuFrame:public wxPanel
{
public:
	ClientMenuFrame(wxWindow* parent, std::vector<std::vector<std::string>> dane);
private:
	void CreateControls(std::vector<std::vector<std::string>> dane);
	void BindEventHandlers();
	void AddReservation(wxCommandEvent& event);
	void DisplayData(std::vector<std::vector<std::string>> dane);
	void delReservations(wxCommandEvent& event);
	std::vector<std::vector<std::string>> GetGridVal();
	
	wxPanel* panel;
	
	wxStaticText* header;
	
	wxButton* addButton;
	wxButton* delButton;

	wxBoxSizer* buttonSizer;
	wxBoxSizer* headerSizer;
	wxBoxSizer* sizer;
	
	wxGrid* grid;
	
};

