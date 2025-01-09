#include "ReservationsFrame.h"
#include "Reservations.h"
#include "bikes.h"


ReservationsFrame::ReservationsFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize(800, 600)), timer(this, wxID_ANY), grid(nullptr)
{
	CreateControls();
	BindEventHandlers();
	timer.Start(10000);
	DisplayTime();
}

void ReservationsFrame::CreateControls()
{
	//panel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(800, 300));

	name = new wxTextCtrl(this, wxID_ANY, "", wxPoint(0, 0));
	phone = new wxTextCtrl(this, wxID_ANY, "", wxPoint(150, 0));
	date = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(300, 50));
	dateTimeDisplay = new wxStaticText(this, wxID_ANY, "", wxPoint(600, 25), wxSize(100,0));

	labelBike1 = new wxStaticText(this, wxID_ANY, "mountain bike", wxDefaultPosition);
	mountain_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	labelBike2 = new wxStaticText(this, wxID_ANY, "touring bike", wxDefaultPosition);
	touring_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	labelBike3 = new wxStaticText(this, wxID_ANY, "gravel bike", wxDefaultPosition);
	gravel_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	labelBike4 = new wxStaticText(this, wxID_ANY, "enduro bike", wxDefaultPosition);
	enduro_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	
	search = new wxButton(this, wxID_ANY, "search", wxPoint(0, 50));
	add = new wxButton(this, wxID_ANY, "ADD", wxPoint(100, 50));
	remove = new wxButton(this, wxID_ANY, "remove", wxPoint(200, 50));
	
	name->SetHint("name");
	phone->SetHint("phone");

	sizerForm = new wxBoxSizer(wxHORIZONTAL);
	sizerForm2 = new wxBoxSizer(wxHORIZONTAL);
	sizerButton = new wxBoxSizer(wxHORIZONTAL);
	sizer = new wxBoxSizer(wxVERTICAL);

	sizerForm->Add(name, 0, wxALL, 5);
	sizerForm->Add(phone, 0, wxALL, 5);
	sizerForm->Add(dateTimeDisplay, 1, wxEXPAND | wxALL, 5);
	sizerForm->Add(date, 0, wxALL, 5);

	sizerForm2->Add(labelBike1, 0, wxALL, 5);
	sizerForm2->Add(mountain_bikes, 0, wxALL, 5);
	sizerForm2->Add(labelBike2, 0, wxALL, 5);
	sizerForm2->Add(touring_bikes, 0, wxALL, 5);
	sizerForm2->Add(labelBike3, 0, wxALL, 5);
	sizerForm2->Add(gravel_bikes, 0, wxALL, 5);
	sizerForm2->Add(labelBike4, 0, wxALL, 5);
	sizerForm2->Add(enduro_bikes, 0, wxALL, 5);

	sizerButton->Add(search, 0, wxALL, 5);
	sizerButton->Add(add, 0, wxALL, 5);
	sizerButton->Add(remove, 0, wxALL, 5);

	sizer->Add(sizerForm, 0, wxEXPAND | wxALL, 5);
	sizer->Add(sizerForm2, 0, wxEXPAND | wxALL, 5);
	sizer->Add(sizerButton, 0, wxALIGN_CENTER | wxALL, 5);

	back = new wxButton(this, wxID_ANY, "back", wxDefaultPosition);
	sizer->Add(back, wxALIGN_LEFT);

	Available();
	this->SetSizerAndFit(sizer);
}

void ReservationsFrame::BindEventHandlers()
{
	Bind(wxEVT_TIMER, &ReservationsFrame::OnTimer, this);
	search->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickSearch, this);
	add->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickAdd, this);
	remove->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickRemove, this);
}

void ReservationsFrame::DisplayTime()
{
	wxDateTime now = wxDateTime::Now();
	wxString dateTimeStr = now.Format("%d-%m-%Y %H:%M");

	dateTimeDisplay->SetLabel(dateTimeStr);
}

void ReservationsFrame::OnTimer(wxTimerEvent& event)
{
	DisplayTime();
}

void ReservationsFrame::OnClickAdd(wxCommandEvent& event)
{
	wxString nameVal = name->GetValue();
	wxString phoneVal = phone->GetValue();
	wxDateTime dateVal = date->GetValue();
	int b1 = mountain_bikes->GetValue();
	int b2 = touring_bikes->GetValue();
	int b3 = gravel_bikes->GetValue();
	int b4 = enduro_bikes->GetValue();
	if (nameVal!="" and phoneVal!="" and (b1>0 or b2>0 or b3>0 or b4>0))
	{
		Reservations addRes;
		addRes.SaveReservationToFile(nameVal, phoneVal, dateVal, b1, b2, b3, b4);

		bikes bikes;
		bikes.DelBikes(b1, b2, b3, b4);
		Available();
		Layout();
	}
}

void ReservationsFrame::OnClickSearch(wxCommandEvent& event)
{
	Reservations searchForRes;

	wxString phoneVal = phone->GetValue();
	if (phoneVal == "*") {
		vector<vector<string>> res = searchForRes.AllReservations();
		if (res.size() != 0) {
			DisplayRes(res);
		}
	}
	else
	{
		vector<vector<string>> res = searchForRes.reservations_phone(phoneVal);
		if (res.size() != 0) {
			DisplayRes(res);
		}
		else
		{
			wxDateTime dateVal = date->GetValue();
			res = searchForRes.reservations_date(dateVal);
			if (res.size() != 0) {
				DisplayRes(res);
			}
			else
			{
				wxMessageBox("Nie znaleziono rezerwacji", "Info", wxOK | wxICON_INFORMATION);
			}
		}
	}
}

void ReservationsFrame::DisplayRes(vector<vector<string>> allRes)
{
	if (grid!=nullptr) {
		grid->Destroy();
		grid = nullptr;
	}
	sizer->Detach(back);

	grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	int rows = allRes.size();
	int cols = !allRes.empty() ? allRes[0].size() : 0;
	grid->CreateGrid(rows, cols+1);

	grid->SetColLabelValue(0, "Select");
	for (int i = 0; i < rows; ++i) {
		grid->SetCellRenderer(i, 0, new wxGridCellBoolRenderer());
		grid->SetCellEditor(i, 0, new wxGridCellBoolEditor());
	}

	vector<string> headers = { "Imiê i nazwisko", "Telefon", "Data", "mountain_bikes", "touring_bikes", "gravel_bikes", "enduro_bikes"};
	for (size_t i = 0; i < headers.size() && i < static_cast<size_t>(cols); ++i) {
		grid->SetColLabelValue(i +1, headers[i]);
	}


	for (size_t i = 0; i < allRes.size(); ++i) {
		for (size_t j = 0; j < allRes[i].size(); ++j) {
			grid->SetCellValue(i, j + 1, allRes[i][j]);
			grid->SetReadOnly(i, j + 1, true);
		}
	}

	grid->AutoSizeColumns();
	grid->AutoSizeRows();

	// Dodaj siatkê do uk³adu
	sizer->Add(grid, 1, wxEXPAND | wxALL, 10);

	sizer->Add(back,0, wxALIGN_LEFT);

	this->Fit();
	Layout();
}

void ReservationsFrame::OnClickRemove(wxCommandEvent& event)
{
	auto checkedRows = GetGridVal();

	if (checkedRows.empty()) {
		wxMessageBox("Nic nie wybrano", "Info", wxOK | wxICON_INFORMATION);
	}
	else {
		Reservations reservations;
		wxString res;
		for (const auto& row : checkedRows) {
			res = "";
			for (const auto& value : row) {
				res += value + " ";
			}
			reservations.DelRes(res);
		}
		Available();
	}
}

vector<vector<string>> ReservationsFrame::GetGridVal()
{
	vector<vector<string>> checkedRows;

	int rows = grid->GetNumberRows();
	int cols = grid->GetNumberCols();

	for (int i = 0; i < rows; ++i) {
		if (grid->GetCellValue(i, 0) == "1") { // Checkbox column
			vector<string> rowValues;
			for (int j = 1; j < cols; ++j) { // Skip the checkbox column
				rowValues.push_back(grid->GetCellValue(i, j).ToStdString());
			}
			checkedRows.push_back(rowValues);
		}
	}
	return checkedRows;
}

void ReservationsFrame::Available()
{
	bikes bikes;
	vector<string> available = bikes.CheckBikes();
	string label1 = "mountain bike(" + available[0] + ")";
	string label2 = "touring bike(" + available[1] + ")";
	string label3 = "gravel bike(" + available[2] + ")";
	string label4 = "enduro bike(" + available[3] + ")";

	labelBike1->SetLabel(label1);
	labelBike2->SetLabel(label2);
	labelBike3->SetLabel(label3);
	labelBike4->SetLabel(label4);
}


