#include "Raporty.h"
#include"Functions.h"


void Raporty::Generate(string date)
{
    ifstream returned("rentals-returned.txt");
    if (!returned.is_open()) {
        wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
        return;
    }
    ofstream raport("raporty/raport" + date + ".txt", ios::trunc);
    if (!returned.is_open()) {
        wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
        return;
    }

    int b1 = 0, b2 = 0, b3 = 0, b4 = 0;
    string line;
    while (getline(returned, line)) {
        
       
        vector<string> slliced = Functions::Slice(line);
        if (slliced[2] == wxDateTime::Now().Format("%d-%m-%Y").ToStdString()) {
            raport << line << "\n";
            b1 += stoi(slliced[4]);
            b2 += stoi(slliced[5]);
            b3 += stoi(slliced[6]);
            b4 += stoi(slliced[7]);
        }
      
    }
    if (b1 == 0 && b2 == 0 && b3 == 0 && b4 == 0) {
        remove(("raporty/raport" + date + ".txt").c_str());
        wxMessageBox(" Nieutworzono raportu", "Brak wypo¿yczeñ dzisiaj", wxOK | wxICON_INFORMATION);
    }
    else
    {
        raport << "górskie: " << b1
            << ", turystyczne: " << b2
            << ", gravel: " << b3
            << ", enduro: " << b4;
        wxMessageBox("Pomyœlnie utworzono raport", "Potwierdzenie", wxOK | wxICON_INFORMATION);
    }
}
