#pragma once
#include <wx/wx.h>
#include "MainMenuFrame.h"
#include <vector>
using namespace std;

class ClientFrame : public wxPanel
{
public:
	ClientFrame(wxWindow* parent);
	static std::vector<std::string> Slice5(const std::string& tekst);
private:
	void CreateControls();
	void BindEventHandlers();

	void HandleLogIn();

	void OnButtonClick(wxCommandEvent& evt);
	void OnClickSign(wxCommandEvent& evt);
	void OnEnterPress(wxKeyEvent& evt);
	void HandleFrameSwap(std::string phone);

	void OnClickBack(wxCommandEvent& evt);

	wxPanel* panel;
	wxStaticText* header;
	wxStaticText* error;
	wxStaticText* labelLogin;
	wxTextCtrl* login;
	wxStaticText* labelPassword;
	wxTextCtrl* password;
	wxButton* loginSubButton;
	wxButton* signinButton;
	wxButton* backButton;

	wxBoxSizer* mainSizer;
	wxBoxSizer* formSizer;
	wxBoxSizer* formSizer2;
};