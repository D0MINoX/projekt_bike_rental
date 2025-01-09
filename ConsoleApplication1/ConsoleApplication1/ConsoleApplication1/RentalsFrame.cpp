#include "RentalsFrame.h"

RentalsFrame::RentalsFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600)), timer(this, wxID_ANY), grid(nullptr)
{
	CreateControls();
	BindEventHandlers();
	timer.Start(10000);
	DisplayTime();
}

void RentalsFrame::CreateControls()
{
	name = new wxTextCtrl(this, wxID_ANY, "", wxPoint(0, 0));
	phone = new wxTextCtrl(this, wxID_ANY, "", wxPoint(150, 0));
	dateTimeDisplay = new wxStaticText(this, wxID_ANY, "", wxPoint(600, 25), wxSize(100, 0));
	name->SetHint("name");
	phone->SetHint("phone");

	labelBike1 = new wxStaticText(this, wxID_ANY, "mountain bike", wxDefaultPosition);
	mountain_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	labelBike2 = new wxStaticText(this, wxID_ANY, "touring bike", wxDefaultPosition);
	touring_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	labelBike3 = new wxStaticText(this, wxID_ANY, "gravel bike", wxDefaultPosition);
	gravel_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);
	labelBike4 = new wxStaticText(this, wxID_ANY, "enduro bike", wxDefaultPosition);
	enduro_bikes = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition);

    search = new wxButton(this, wxID_ANY, "search");
    pay = new wxButton(this, wxID_ANY, "pay");

	mainSizer = new wxBoxSizer(wxVERTICAL);
	formSizer = new wxBoxSizer(wxHORIZONTAL);
	formSizer2 = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	formSizer->Add(name, 0, wxALL, 5);
	formSizer->Add(phone, 0, wxALL, 5);
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
    buttonSizer->Add(pay, 0, wxALL, 5);

	mainSizer->Add(formSizer, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(formSizer2, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

	this->SetSizerAndFit(mainSizer);
}

void RentalsFrame::BindEventHandlers()
{
	Bind(wxEVT_TIMER, &RentalsFrame::OnTimer, this);
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

void RentalsFrame::DisplayRentals(vector<std::vector<std::string>> allRentals)
{
    if (grid != nullptr) {
        grid->Destroy();
        grid = nullptr;
    }
    //mainsizer->Detach(back);
    //back->Destroy();

    grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    int rows = allRentals.size();
    int cols = !allRentals.empty() ? allRentals[0].size() + 1 : 1; // Add 1 for the radio button column
    grid->CreateGrid(rows, cols);

    // Set headers
    vector<string> headers = { "Select", "Imiê i nazwisko", "Telefon", "Data", "mountain_bikes", "touring_bikes", "gravel_bikes", "enduro_bikes" };
    for (size_t i = 0; i < headers.size() && i < static_cast<size_t>(cols); ++i) {
        grid->SetColLabelValue(i, headers[i]);
    }

    // Add radio button column
    for (int i = 0; i < rows; ++i) {
        grid->SetCellRenderer(i, 0, new wxGridCellBoolRenderer());
        grid->SetCellEditor(i, 0, new wxGridCellBoolEditor());
        grid->SetCellValue(i, 0, "0"); // Default unchecked
        grid->SetCellAlignment(i, 0, wxALIGN_CENTER, wxALIGN_CENTER);
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

    // Add grid to the layout
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 10);

    //back = new wxButton(this, wxID_ANY, "back", wxDefaultPosition);
    //mainsizer->Add(back, 0, wxALIGN_BOTTOM | wxALIGN_LEFT);

    // Bind event to handle row selection
    grid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &RentalsFrame::OnGridCellClick, this);

    this->Fit();
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
