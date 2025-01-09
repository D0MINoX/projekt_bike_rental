#include "ClientMenuFrame.h"
#include<fstream>
#include <string>
#include"ReservationAddClientFrame.h"
#include <vector>
#include<wx/grid.h>
#include "Reservations.h"

ClientMenuFrame::ClientMenuFrame(wxWindow* parent, std::vector<std::vector<std::string>> dane) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600)), grid(nullptr)
{
    CreateControls(dane);
    BindEventHandlers();
    DisplayData(dane);
}

// Tworzy elementy interfejsu u¿ytkownika
void ClientMenuFrame::CreateControls(std::vector<std::vector<std::string>> dane)
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

    header = new wxStaticText(panel, wxID_ANY, "Panel U¿ytkownika", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont headerFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    header->SetFont(headerFont);

    addButton = new wxButton(panel, wxID_ANY, wxT("Utwórz rezerwacjê"), wxDefaultPosition);
    delButton = new wxButton(panel, wxID_ANY, "Usuñ rezerwacjê", wxDefaultPosition);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addButton, 0, wxALL, 5);
    buttonSizer->Add(delButton, 0, wxALL, 5);

    headerSizer = new wxBoxSizer(wxVERTICAL);
    headerSizer->Add(header, 0, wxALIGN_CENTER | wxALL, 10);
    headerSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(headerSizer, 0, wxEXPAND | wxALL, 5);

    panel->SetSizerAndFit(sizer);
}

// Przypisuje zdarzenia do przycisków
void ClientMenuFrame::BindEventHandlers()
{
    addButton->Bind(wxEVT_BUTTON, &ClientMenuFrame::AddReservation, this);
    delButton->Bind(wxEVT_BUTTON, &ClientMenuFrame::delReservations, this);
}

// Obs³uguje logikê dodawania rezerwacji
void ClientMenuFrame::AddReservation(wxCommandEvent& event)
{
    if (panel) {
        panel->Destroy();
    }

    panel = new ReservationAddClientFrame(this);
    panel->SetSize(this->GetClientSize());
    Layout();
}

// Wyœwietla dane w tabeli
void ClientMenuFrame::DisplayData(std::vector<std::vector<std::string>> dane) {
    if (grid != nullptr) {
        grid->Destroy();
        grid = nullptr;
    }

    grid = new wxGrid(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    int rows = dane.size();
    int cols = !dane.empty() ? dane[0].size() : 0;

    grid->CreateGrid(rows, cols + 1);
    grid->SetColLabelValue(0, "Select");

    for (int i = 0; i < rows; ++i)
    {
        grid->SetCellRenderer(i, 0, new wxGridCellBoolRenderer());
        grid->SetCellEditor(i, 0, new wxGridCellBoolEditor());
    }

    std::vector<std::string> headers = { "Imiê i nazwisko", "Telefon", "Data", "rowery górskie", "rowery turystyczne", "rowery gravel", "rowery enduro" };
    for (size_t i = 0; i < headers.size() && i < static_cast<size_t>(cols); ++i) {
        grid->SetColLabelValue(i + 1, headers[i]);
    }

    for (size_t i = 0; i < dane.size(); ++i) {
        for (size_t j = 0; j < dane[i].size(); ++j) {
            grid->SetCellValue(i, j + 1, dane[i][j]);
            grid->SetReadOnly(i, j + 1, true);
        }
    }

    grid->AutoSizeColumns();
    grid->AutoSizeRows();

    sizer->Add(grid, 1, wxEXPAND | wxALL, 10);
    panel->SetSizerAndFit(sizer);
    Layout();
}

// Pobiera zaznaczone wartoœci z tabeli
std::vector<std::vector<std::string>> ClientMenuFrame::GetGridVal()
{
    std::vector<std::vector<std::string>> checkedRows;

    int rows = grid->GetNumberRows();
    int cols = grid->GetNumberCols();

    for (int i = 0; i < rows; ++i) {
        if (grid->GetCellValue(i, 0) == "1") {
            std::vector<std::string> rowValues;
            for (int j = 1; j < cols; ++j) {
                rowValues.push_back(grid->GetCellValue(i, j).ToStdString());
            }
            checkedRows.push_back(rowValues);
        }
    }
    return checkedRows;
}

// Usuwa zaznaczone rezerwacje
void ClientMenuFrame::delReservations(wxCommandEvent& event)
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
    }
}
