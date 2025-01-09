#pragma once
#include <wx/wx.h>
#include "MainMenuFrame.h"
#include <vector>

class ClientFrame : public wxPanel
{
public:
	ClientFrame(wxWindow* parent);
	static std::vector<std::vector<std::string>> reservations_phone(std::string phone);
	
private:
	void CreateControls();
	void BindEventHandlers();
	
	void HandleLogIn();
	static std::vector<std::string> Slice5(const std::string& tekst);
	void OnButtonClick(wxCommandEvent& evt);
	void OnEnterPress(wxKeyEvent& evt);
	void HandleFrameSwap(std::vector<std::vector<std::string>> dane);

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