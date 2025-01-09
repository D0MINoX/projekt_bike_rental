#include "WorkerMenuFrame.h"
#include "ReservationsFrame.h"
#include "RentalsFrame.h"
#include "BikesFrame.h"
#include "LogInFrame.h"

WorkerMenuFrame::WorkerMenuFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(800, 600))
{
	CreateControls();
	BindEventHandlers();
}

void WorkerMenuFrame::CreateControls()
{
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	bikes = new wxButton(panel, wxID_ANY, "rowery", wxDefaultPosition);
	rentals = new wxButton(panel, wxID_ANY, "wypo¿yczenia", wxDefaultPosition);
	reservations = new wxButton(panel, wxID_ANY, "rezerwacje", wxDefaultPosition);
	back = new wxButton(panel, wxID_ANY, "wyloguj", wxDefaultPosition);
	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(bikes, 0, wxALL, 15);
	sizer->Add(rentals, 0, wxALL, 15);
	sizer->Add(reservations, 0, wxALL, 15);
	sizer->Add(back, 0, wxALL, 15);
	
	panel->SetSizerAndFit(sizer);
}

void WorkerMenuFrame::BindEventHandlers()
{
	reservations->Bind(wxEVT_BUTTON, &WorkerMenuFrame::OnClickRes, this);
	rentals->Bind(wxEVT_BUTTON, &WorkerMenuFrame::OnClickRent, this);
	bikes->Bind(wxEVT_BUTTON, &WorkerMenuFrame::OnClickBikes, this);
	back->Bind(wxEVT_BUTTON, &WorkerMenuFrame::OnClickBack, this);
}

void WorkerMenuFrame::OnClickRes(wxCommandEvent& evt)
{
	panel->Destroy();
	panel = new ReservationsFrame(this);

	Layout();
}

void WorkerMenuFrame::OnClickRent(wxCommandEvent& evt)
{
	panel->Destroy();
	panel = new RentalsFrame(this);

	Layout();
}

void WorkerMenuFrame::OnClickBikes(wxCommandEvent& evt)
{
	panel->Destroy();
	panel = new BikesFrame(this);

	Layout();
}

void WorkerMenuFrame::OnClickBack(wxCommandEvent& evt)
{
	panel->Destroy();

	panel = new LogInFrame(this);
	panel->SetSize(this->GetClientSize());
	Layout();
}

