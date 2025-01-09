#pragma once
#include <wx/wx.h>

class MainMenuFrame : public wxPanel {
public:
    MainMenuFrame(wxWindow* parent); 
    void CreateControls();          
    void BindEventHandlers();         

private:

    wxButton* workerButton;
    wxButton* clientButton;

    wxStaticText* name;
    wxStaticText* openingHoursText;
    wxStaticBitmap* logo;

    wxBoxSizer* buttonSizer;
    wxBoxSizer* infoSizer;
    wxBoxSizer* Sizer;

    void OnClickWorker(wxCommandEvent& evt);
    void OnClickClient(wxCommandEvent& evt);  
};
