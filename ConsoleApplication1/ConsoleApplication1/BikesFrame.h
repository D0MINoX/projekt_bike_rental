#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/datetime.h>

using namespace std;

class BikesFrame : public wxPanel
{
public:
	BikesFrame(wxWindow* parent);
private:
	void CreateControls();
	void BindEventHandlers();
	void Available(wxString& selectedDate);
	void OnChangeDate(wxDateEvent& event);
	void OnClickBack(wxCommandEvent& evt);

	wxPanel* panel;
	wxDatePickerCtrl* date;
	wxStaticText* b1;
	wxStaticText* b2;
	wxStaticText* b3;
	wxStaticText* b4;
	wxButton* back;
	wxBoxSizer* sizer;
};

