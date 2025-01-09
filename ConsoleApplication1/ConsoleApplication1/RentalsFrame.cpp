#include "RentalsFrame.h"
#include "Rentals.h"
#include "bikes.h"
#include "WorkerMenuFrame.h"
#include "Raporty.h"

RentalsFrame::RentalsFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600)), timer(this, wxID_ANY), grid(nullptr)
{
	CreateControls();
	BindEventHandlers();
	timer.Start(10000);
	DisplayTime();
}

void RentalsFrame::CreateControls()
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

    wxArrayString choices;
    choices.Add("Szczawnica1");
    choices.Add("Sczawnica2");
    choices.Add("Kroscienko");
    place = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
    place->SetSelection(1);

	name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(0, 0));
	phone = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 0));
    raport = new wxButton(panel, wxID_ANY, "Generuj raport");
	dateTimeDisplay = new wxStaticText(panel, wxID_ANY, "", wxPoint(600, 25), wxSize(100, 0));
	name->SetHint("name");
	phone->SetHint("phone");

	labelBike1 = new wxStaticText(panel, wxID_ANY, "rowery górskie", wxDefaultPosition);
	mountain_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	labelBike2 = new wxStaticText(panel, wxID_ANY, "rowery turystyczne", wxDefaultPosition);
	touring_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	labelBike3 = new wxStaticText(panel, wxID_ANY, "rowery gravel", wxDefaultPosition);
	gravel_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);
	labelBike4 = new wxStaticText(panel, wxID_ANY, "rowery enduro", wxDefaultPosition);
	enduro_bikes = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition);

    search = new wxButton(panel, wxID_ANY, "szukaj");
    add = new wxButton(panel, wxID_ANY, "dodaj");
    pay = new wxButton(panel, wxID_ANY, "zap³aæ");

    back = new wxButton(panel, wxID_ANY, "wstecz", wxDefaultPosition);

	mainSizer = new wxBoxSizer(wxVERTICAL);
	formSizer = new wxBoxSizer(wxHORIZONTAL);
	formSizer2 = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	formSizer->Add(name, 0, wxALL, 5);
	formSizer->Add(phone, 0, wxALL, 5);
	formSizer->Add(place, 0, wxALL, 5);
	formSizer->Add(raport, 0, wxALL, 5);
	formSizer->Add(dateTimeDisplay, 0, wxALL, 5);

	formSizer2->Add(labelBike1, 0, wxALL, 5);
	formSizer2->Add(mountain_bikes, 0, wxALL, 5);
	formSizer2->Add(labelBike2, 0, wxALL, 5);
	formSizer2->Add(touring_bikes, 0, wxALL, 5);
	formSizer2->Add(labelBike3, 0, wxALL, 5);
	formSizer2->Add(gravel_bikes, 0, wxALL, 5);
	formSizer2->Add(labelBike4, 0, wxALL, 5);
	formSizer2->Add(enduro_bikes, 0, wxALL, 5);

    buttonSizer->Add(search, 0, wxALL, 5);
    buttonSizer->Add(add, 0, wxALL, 5);
    buttonSizer->Add(pay, 0, wxALL, 5);

	mainSizer->Add(formSizer, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(formSizer2, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer->Add(back, 0, wxALIGN_LEFT | wxALL, 5);

    Available();

	panel->SetSizerAndFit(mainSizer);
}

void RentalsFrame::BindEventHandlers()
{
	Bind(wxEVT_TIMER, &RentalsFrame::OnTimer, this);
    search->Bind(wxEVT_BUTTON, &RentalsFrame::OnClickSearch, this);
    add->Bind(wxEVT_BUTTON, &RentalsFrame::OnClickAdd, this);
    back->Bind(wxEVT_BUTTON, &RentalsFrame::OnClickBack, this);
    pay->Bind(wxEVT_BUTTON, &RentalsFrame::OnClickPay, this);
    raport->Bind(wxEVT_BUTTON, &RentalsFrame::OnClickRaport, this);
}

void RentalsFrame::DisplayTime()
{
	wxDateTime now = wxDateTime::Now();
	wxString dateTimeStr = now.Format("%d-%m-%Y %H:%M");

	dateTimeDisplay->SetLabel(dateTimeStr);
}

void RentalsFrame::OnTimer(wxTimerEvent& event)
{
	DisplayTime();
}

void RentalsFrame::OnClickAdd(wxCommandEvent& event)
{
    wxString nameVal = name->GetValue();
    wxString phoneVal = phone->GetValue();
    wxString placeVal = place->GetString(place->GetSelection());

    wxDateTime now = wxDateTime::Now();
    wxString dateStr = now.Format("%d-%m-%Y");
    wxString timeStr = now.Format("%H:%M");

    int b1 = mountain_bikes->GetValue();
    int b2 = touring_bikes->GetValue();
    int b3 = gravel_bikes->GetValue();
    int b4 = enduro_bikes->GetValue();
    if (nameVal != "" and phoneVal != "" and (b1 > 0 or b2 > 0 or b3 > 0 or b4 > 0))
    {
        bikes bikes;
        vector<string>available = bikes.CheckBikes(dateStr.ToStdString());
        if (stoi(available[0]) >= b1 && stoi(available[1]) >= b2 && stoi(available[2]) >= b3 && stoi(available[3]) >= b4) {
            Rentals addRental;
            addRental.SaveRentalsToFile(nameVal, phoneVal, dateStr, timeStr, b1, b2, b3, b4, placeVal);

            //bikes bikes;
            bikes.DelBikes(b1, b2, b3, b4, dateStr.ToStdString());
            Available();
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

void RentalsFrame::OnClickSearch(wxCommandEvent& event)
{
    Rentals searchForRental;

    wxString phoneVal = phone->GetValue();
    if (phoneVal == "*") {
        vector<vector<string>> rental = searchForRental.AllRentals();
        if (rental.size() != 0) {
            DisplayRentals(rental);
        }
    }
    else
    {
        vector<vector<string>> rental = searchForRental.RentalsPhone(phoneVal);
        if (rental.size() != 0) {
            DisplayRentals(rental);
        }
        else
        {
            wxMessageBox("Nie znaleziono wypo¿yczenia", "Info", wxOK | wxICON_INFORMATION);
        }
    }
}

void RentalsFrame::DisplayRentals(vector<vector<string>> allRentals)
{
    if (grid != nullptr) {
        mainSizer->Detach(grid);
        grid->Destroy();
        grid = nullptr;
        panel->Fit();
    }
    mainSizer->Detach(back);
    //back->Destroy();

    grid = new wxGrid(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    int rows = allRentals.size();
    int cols = !allRentals.empty() ? allRentals[0].size() + 1 : 1; // Add 1 for the radio button column
    grid->CreateGrid(rows, cols);

    // Add radio button column
    for (int i = 0; i < rows; ++i) {
        grid->SetCellRenderer(i, 0, new wxGridCellBoolRenderer());
        grid->SetCellEditor(i, 0, new wxGridCellBoolEditor());
        //grid->SetCellValue(i, 0, "0"); // Default unchecked
        grid->SetCellAlignment(i, 0, wxALIGN_CENTER, wxALIGN_CENTER);
    }

    // Set headers
    vector<string> headers = {"Select", "Imiê", "Telefon", "Data", "Godzina", "mountain_bikes", "touring_bikes", "gravel_bikes", "enduro_bikes", "Miejsce"};
    for (size_t i = 0; i < headers.size() && i < static_cast<size_t>(cols); ++i) {
        grid->SetColLabelValue(i, headers[i]);
    }

    // Fill other columns with data
    for (size_t i = 0; i < allRentals.size(); ++i) {
        for (size_t j = 0; j < allRentals[i].size(); ++j) {
            grid->SetCellValue(i, j + 1, allRentals[i][j]); // Offset by 1 for the radio column
            grid->SetReadOnly(i, j + 1, true);
        }
    }

    grid->AutoSizeColumns();
    grid->AutoSizeRows();
    grid->SetRowLabelSize(20);
    // Add grid to the layout
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);

    mainSizer->Add(back, 0, wxALIGN_LEFT | wxALL, 5);

    // Bind event to handle row selection
    grid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &RentalsFrame::OnGridCellClick, this);

    DisplayTime();
    Available();

    panel->Fit();
    Layout();
}

void RentalsFrame::OnGridCellClick(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

    if (col == 0) { // Radio button column
        // Set the clicked row's radio button to checked
        for (int i = 0; i < grid->GetNumberRows(); ++i) {
            grid->SetCellValue(i, 0, (i == row ? "1" : "0"));
        }
        grid->ForceRefresh(); // Redraw the grid
    }
    event.Skip();
}

vector<string> RentalsFrame::GetSelectedRowValues()
{
    for (int i = 0; i < grid->GetNumberRows(); ++i) {
        if (grid->GetCellValue(i, 0) == "1") { // Check if radio button is selected
            vector<string> rowValues;
            for (int j = 1; j < grid->GetNumberCols(); ++j) { // Skip the radio button column
                rowValues.push_back(grid->GetCellValue(i, j).ToStdString());
            }
            return rowValues;
        }
    }
    return {}; // Return empty vector if no row is selected
}

void RentalsFrame::OnClickPay(wxCommandEvent& event)
{
    if (grid == nullptr) {
        wxMessageBox("Nic nie wybrano", "Info", wxOK | wxICON_INFORMATION);
    }
    else
    {
        vector<string> checkedRows = GetSelectedRowValues();
        if (checkedRows.empty()) {
            wxMessageBox("Nic nie wybrano", "Info", wxOK | wxICON_INFORMATION);
        }
        else {
            Rentals rentals;
            wxString rental;
            rental = "";
            for (int i = 0; i < checkedRows.size(); i++) {
                rental += checkedRows[i] + " ";
                rentals.DelRentals(rental);
            }
            Available();
        }
    }
}

void RentalsFrame::OnClickRaport(wxCommandEvent& event)
{
    wxDateTime now = wxDateTime::Now();
    string dateTimeStr = now.Format("%d-%m-%Y;%H-%M").ToStdString();
    Raporty raporty;
    raporty.Generate(dateTimeStr);
}

void RentalsFrame::Available()
{
    string dateStr = wxDateTime::Now().Format("%d-%m-%Y").ToStdString();

    bikes bikes;
    vector<string> available = bikes.CheckBikes(dateStr);
    string label1 = "mountain bike(" + available[0] + ")";
    string label2 = "touring bike(" + available[1] + ")";
    string label3 = "gravel bike(" + available[2] + ")";
    string label4 = "enduro bike(" + available[3] + ")";

    labelBike1->SetLabel(label1);
    labelBike2->SetLabel(label2);
    labelBike3->SetLabel(label3);
    labelBike4->SetLabel(label4);
}

void RentalsFrame::OnClickBack(wxCommandEvent& evt)
{
    panel->Destroy();
    timer.Stop();

    panel = new WorkerMenuFrame(this);
    panel->SetSize(this->GetClientSize());
    Layout();
}