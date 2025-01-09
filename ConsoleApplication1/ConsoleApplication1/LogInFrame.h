#pragma once
#include <wx/wx.h>
#include "WorkerMenuFrame.h"

class LogInFrame : public wxPanel
{
public:
	LogInFrame(wxWindow* parent	);
private:
	void CreateControls();
	void BindEventHandlers();

	void HandleLogIn();

	void OnButtonClick(wxCommandEvent& evt);
	void OnEnterPress(wxKeyEvent& evt);
	void HandleFrameSwap();

	void OnClickBack(wxCommandEvent& evt);


	wxPanel* panel;
	wxStaticText* header;
	wxStaticText* error;
	wxStaticText* labelLogin;
	wxTextCtrl* login;
	wxStaticText* labelPassword;
	wxTextCtrl* password;
	wxButton* loginSubButton;
	wxButton* backButton;

	wxBoxSizer* mainSizer;
	wxBoxSizer* formSizer;
	wxBoxSizer* formSizer2;
};
