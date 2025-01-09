#pragma once
#include<wx/wx.h>
class ClientRegisterFrame : public wxPanel
{
public:
	ClientRegisterFrame(wxWindow* parent) ;
	
private:
	void Submit(wxCommandEvent& event);
	void CreateControls();
	void BindEventHandlers();
	void BackButton(wxCommandEvent& event);
	void BackButton();
	wxPanel* panel;
	wxTextCtrl* firstNameCtrl;
	wxTextCtrl* lastNameCtrl;
	wxTextCtrl* phoneCtrl;
	wxTextCtrl* passwordCtrl;
	wxButton* submitButton;
	wxButton* backButton;
	
	wxBoxSizer* sizer;
	wxFlexGridSizer* gridSizer;
};

