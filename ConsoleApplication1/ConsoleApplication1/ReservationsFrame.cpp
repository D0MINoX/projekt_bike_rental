#include "ReservationsFrame.h"
#include "Reservations.h"
#include "bikes.h"
#include "WorkerMenuFrame.h"


ReservationsFrame::ReservationsFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0,0), wxSize(800, 600)), timer(this, wxID_ANY), grid(nullptr)
{
	CreateControls();
	BindEventHandlers();
	timer.Start(10000);
	DisplayTime();
}

void ReservationsFrame::CreateControls()
{
	panel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(800, 300));

	wxArrayString choices;
	choices.Add("Szczawnica1");
	choices.Add("Sczawnica2");
	choices.Add("Kroscienko");
	place = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	place->SetSelection(1);

	name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 0));
	phone = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 0));
	date = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	dateTimeDisplay = new wxStaticText(panel, wxID_ANY, "", wxPoint(600, 25), wxSize(100,0));

	spacer = new wxStaticText(panel, wxID_ANY, "", wxPoint(600, 25), wxSize(100,0)); //jest tylko do zrobienia odstêpu bo inaczej nie wiem jak

	labelBike1 = new wxStaticText(panel, wxID_ANY, "rowery górskie", wxDefaultPosition);
	mountain_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	labelBike2 = new wxStaticText(panel, wxID_ANY, "rowery turystyczne", wxDefaultPosition);
	touring_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	labelBike3 = new wxStaticText(panel, wxID_ANY, "rowery gravel", wxDefaultPosition);
	gravel_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	labelBike4 = new wxStaticText(panel, wxID_ANY, "rowery enduro", wxDefaultPosition);
	enduro_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	
	search = new wxButton(panel, wxID_ANY,"szukaj", wxPoint(0, 50));
	add = new wxButton(panel, wxID_ANY, "dodaj", wxPoint(100, 50));
	remove = new wxButton(panel, wxID_ANY, "usuñ", wxPoint(200, 50));
	rent = new wxButton(panel, wxID_ANY, "wypo¿ycz");
	
	name->SetHint("name");
	phone->SetHint("phone");

	sizerForm = new wxBoxSizer(wxHORIZONTAL);
	sizerForm2 = new wxBoxSizer(wxHORIZONTAL);
	sizerButton = new wxBoxSizer(wxHORIZONTAL);
	sizer = new wxBoxSizer(wxVERTICAL);

	sizerForm->Add(name, 0, wxALL, 5);
	sizerForm->Add(phone, 0, wxALL, 5);
	sizerForm->Add(date, 0, wxALL, 5);
	sizerForm->Add(spacer, 1, wxEXPAND | wxALL, 5);
	sizerForm->Add(place, 0, wxALL, 5);
	sizerForm->Add(dateTimeDisplay, 0, wxALL, 5);

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
	sizerButton->Add(rent, 0, wxALL, 5);

	sizer->Add(sizerForm, 0, wxEXPAND | wxALL, 5);
	sizer->Add(sizerForm2, 0, wxEXPAND | wxALL, 5);
	sizer->Add(sizerButton, 0, wxALIGN_CENTER | wxALL, 5);

	back = new wxButton(panel, wxID_ANY, "wstecz", wxDefaultPosition);
	sizer->Add(back, wxALIGN_LEFT);

	wxString selectedDate = date->GetValue().Format("%d-%m-%Y");
	Available(selectedDate);
	panel->SetSizerAndFit(sizer);
}

void ReservationsFrame::BindEventHandlers()
{
	Bind(wxEVT_TIMER, &ReservationsFrame::OnTimer, this);
	search->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickSearch, this);
	add->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickAdd, this);
	remove->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickRemove, this);
	back->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickBack, this);
	date->Bind(wxEVT_DATE_CHANGED, &ReservationsFrame::OnChangeDate, this);
	rent->Bind(wxEVT_BUTTON, &ReservationsFrame::OnClickRent, this);
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
	wxString dateVal = date->GetValue().Format("%d-%m-%Y");
	int b1 = mountain_bikes->GetValue();
	int b2 = touring_bikes->GetValue();
	int b3 = gravel_bikes->GetValue();
	int b4 = enduro_bikes->GetValue();
	if (nameVal!="" and phoneVal!="" and (b1>0 or b2>0 or b3>0 or b4>0))
	{
		bikes bikes;
		vector<string>available = bikes.CheckBikes(dateVal.ToStdString());
		if (stoi(available[0]) >= b1 && stoi(available[1]) >= b2 && stoi(available[2]) >= b3 && stoi(available[3]) >= b4) {
			Reservations addRes;
			addRes.SaveReservationToFile(nameVal, phoneVal, dateVal, b1, b2, b3, b4);
			wxMessageBox("Dodano rezerwacje!", "info", wxOK | wxICON_INFORMATION);
			//bikes bikes;
			bikes.DelBikes(b1, b2, b3, b4, dateVal.ToStdString());
			Available(dateVal);
			Layout();
		}
		else
		{
			if (stoi(available[0]) < b1) wxMessageBox("przekroczono limit rowerów górskich maks." + available[0], "Potwierdzenie", wxOK | wxICON_INFORMATION);
			if (stoi(available[1]) < b2) wxMessageBox("przekroczono limit rowerów turystycznych maks." + available[1], "Potwierdzenie", wxOK | wxICON_INFORMATION);
			if (stoi(available[2]) < b4) wxMessageBox("przekroczono limit rowerów gravel maks." + available[2], "Potwierdzenie", wxOK | wxICON_INFORMATION);
			if (stoi(available[3]) < b3) wxMessageBox("przekroczono limit rowerów enduro maks." + available[3], "Potwierdzenie", wxOK | wxICON_INFORMATION);
		}
	}
}

void ReservationsFrame::OnClickSearch(wxCommandEvent& event)
{
	Reservations searchForRes;
	vector<vector<string>> res;

	wxString phoneVal = phone->GetValue();
	if (phoneVal == "*") {
		res = searchForRes.AllReservations();
		if (res.size() != 0) {
			DisplayRes(res);
		}
	}
	else
	{
		res = searchForRes.reservations_phone(phoneVal);
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
		sizer->Detach(grid);
		grid->Destroy();
		grid = nullptr;
		panel->Fit();
	}
	sizer->Detach(back);

	grid = new wxGrid(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	int rows = allRes.size();
	int cols = !allRes.empty() ? allRes[0].size() : 0;
	grid->CreateGrid(rows, cols+1);

	//grid->SetColLabelValue(0, "Select");
	for (int i = 0; i < rows; ++i) {
		grid->SetCellRenderer(i, 0, new wxGridCellBoolRenderer());
		grid->SetCellEditor(i, 0, new wxGridCellBoolEditor());
		grid->SetCellAlignment(i, 0, wxALIGN_CENTER, wxALIGN_CENTER);
	}

	vector<string> headers = {"Select", "Imiê i nazwisko", "Telefon", "Data", "mountain_bikes", "touring_bikes", "gravel_bikes", "enduro_bikes"};
	for (size_t i = 0; i < headers.size() && i < static_cast<size_t>(cols)+1; ++i) {
		grid->SetColLabelValue(i, headers[i]);
	}


	for (size_t i = 0; i < allRes.size(); ++i) {
		for (size_t j = 0; j < allRes[i].size(); ++j) {
			grid->SetCellValue(i, j + 1, allRes[i][j]);
			grid->SetReadOnly(i, j + 1, true);
		}
	}

	grid->AutoSizeColumns();
	grid->AutoSizeRows();
	grid->SetRowLabelSize(20);

	// Dodaj siatkê do uk³adu
	sizer->Add(grid, 1, wxEXPAND | wxALL, 10);

	sizer->Add(back, 0, wxALIGN_LEFT);

	panel->Fit();
	DisplayTime();
	Layout();
}

void ReservationsFrame::OnClickRemove(wxCommandEvent& event)
{
	if (grid == nullptr) {
		wxMessageBox("Nic nie wybrano", "Info", wxOK | wxICON_INFORMATION);
	}
	else
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
				reservations.DelRes(res,false);
			}
			wxString selectedDate = date->GetValue().Format("%d-%m-%Y");
			Available(selectedDate);
		}
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

void ReservationsFrame::OnClickRent(wxCommandEvent& evt)
{
	if (grid == nullptr) {
		wxMessageBox("Nic nie wybrano", "Info", wxOK | wxICON_INFORMATION);
	}
	else
	{
		auto checkedRows = GetGridVal();
		if (checkedRows.empty()) {
			wxMessageBox("Nic nie wybrano", "Info", wxOK | wxICON_INFORMATION);
		}
		else {
			Reservations reservations;
			wxString res;
			wxDateTime now = wxDateTime::Now();
			wxString time = now.Format("%d-%m-%Y %H:%M");
			wxString placeVal = place->GetString(place->GetSelection());
			for (const auto& row : checkedRows) {
				res = "";
				for (const auto& value : row) {
					res += value + " ";
				}
				reservations.RentRes(res,time,placeVal);
			}
			wxString selectedDate = date->GetValue().Format("%d-%m-%Y");
			Available(selectedDate);
		}
	}
}

void ReservationsFrame::Available(wxString& selectedDate)
{
	bikes bikes;
	vector<string> available = bikes.CheckBikes(selectedDate.ToStdString());
	string label1 = "mountain bike(" + available[0] + ")";
	string label2 = "touring bike(" + available[1] + ")";
	string label3 = "gravel bike(" + available[2] + ")";
	string label4 = "enduro bike(" + available[3] + ")";

	labelBike1->SetLabel(label1);
	labelBike2->SetLabel(label2);
	labelBike3->SetLabel(label3);
	labelBike4->SetLabel(label4);
}

void ReservationsFrame::OnClickBack(wxCommandEvent& evt)
{
	panel->Destroy();
	timer.Stop();

	panel = new WorkerMenuFrame(this);
	panel->SetSize(this->GetClientSize());
	Layout();
}

void ReservationsFrame::OnChangeDate(wxDateEvent& event)
{
	wxString selectedDate = event.GetDate().Format("%d-%m-%Y");
	Available(selectedDate);
}


