#include "WorkerMenuFrame.h"
#include "ReservationsFrame.h"
#include "RentalsFrame.h"

WorkerMenuFrame::WorkerMenuFrame(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(800, 600))
{
	CreateControls();
	BindEventHandlers();
}

void WorkerMenuFrame::CreateControls()
{
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
	bikes = new wxButton(panel, wxID_ANY, "bikes", wxPoint(0, 0));
	rentals = new wxButton(panel, wxID_ANY, "rentals", wxPoint(0, 30));
	reservations = new wxButton(panel, wxID_ANY, "reservations", wxPoint(0, 60));
}

void WorkerMenuFrame::BindEventHandlers()
{
	reservations->Bind(wxEVT_BUTTON, &WorkerMenuFrame::OnClickRes, this);
	rentals->Bind(wxEVT_BUTTON, &WorkerMenuFrame::OnClickRent, this);
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
