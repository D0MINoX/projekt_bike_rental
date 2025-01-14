#include "BikesFrame.h"
#include "bikes.h"
#include "WorkerMenuFrame.h"

BikesFrame::BikesFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600))
{
	CreateControls();
	BindEventHandlers();
}
//wyœwietlenie GUI
void BikesFrame::CreateControls()
{
	panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 300));
	b1 = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 0));
	b2 = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 0));
	b3 = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 0));
	b4 = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 0));
	date = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	back = new wxButton(panel, wxID_ANY, "wstecz", wxDefaultPosition);
	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(date, 0, wxEXPAND | wxALL, 15);
	sizer->Add(b1, 0, wxEXPAND | wxALL, 15);
	sizer->Add(b2, 0, wxEXPAND | wxALL, 15);
	sizer->Add(b3, 0, wxEXPAND | wxALL, 15);
	sizer->Add(b4, 0, wxEXPAND | wxALL, 15);
	sizer->Add(back, 0, wxEXPAND | wxALL, 15);
	//???????????!
	panel->SetSizerAndFit(sizer);
	wxString selectedDate = date->GetValue().Format("%d-%m-%Y");
	Available(selectedDate);
	Layout();
}
//dodanie elementów alcji
void BikesFrame::BindEventHandlers()
{
	date->Bind(wxEVT_DATE_CHANGED, &BikesFrame::OnChangeDate, this);
	back->Bind(wxEVT_BUTTON, &BikesFrame::OnClickBack, this);
}
//wyœwietlanie dostêpnych rowerów
void BikesFrame::Available(wxString& selectedDate)
{
	bikes bikes;
	vector<string> available = bikes.CheckBikes(selectedDate.ToStdString());
	string label1 = "rowery górskie: " + available[0];
	string label2 = "rowery turystyczne: " + available[1];
	string label3 = "rowery gravel: " + available[2];
	string label4 = "rowery enduro: " + available[3];

	b1->SetLabel(label1);
	b2->SetLabel(label2);
	b3->SetLabel(label3);
	b4->SetLabel(label4);

	//wxMessageBox(label1, "Potwierdzenie", wxOK | wxICON_INFORMATION);
	panel->Fit();
	Layout();
}

void BikesFrame::OnChangeDate(wxDateEvent& event)
{
	wxString selectedDate = event.GetDate().Format("%d-%m-%Y");
	Available(selectedDate);
}

void BikesFrame::OnClickBack(wxCommandEvent& evt)
{
	panel->Destroy();

	panel = new WorkerMenuFrame(this);
	panel->SetSize(this->GetClientSize());
	Layout();
}
