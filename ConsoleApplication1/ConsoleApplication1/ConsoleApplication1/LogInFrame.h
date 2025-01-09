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
	wxStaticText* labelLogin;
	wxTextCtrl* login;
	wxStaticText* labelPassword;
	wxTextCtrl* password;
	wxButton* loginSubButton;
	wxStaticText* error;
	wxButton* backButton;
};
