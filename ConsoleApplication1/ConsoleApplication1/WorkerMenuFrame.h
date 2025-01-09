#pragma once
#include <wx/wx.h>

class WorkerMenuFrame : public wxPanel
{
public:
	WorkerMenuFrame(wxWindow* parent);
private:
	void CreateControls();
	void BindEventHandlers();

	void OnClickRes(wxCommandEvent& evt);
	void OnClickRent(wxCommandEvent& evt);
	void OnClickBikes(wxCommandEvent& evt);
	void OnClickBack(wxCommandEvent& evt);


	wxPanel* panel;
	wxButton* bikes;
	wxButton* rentals;
	wxButton* reservations;
	wxButton* back;

	wxBoxSizer* sizer;
};

