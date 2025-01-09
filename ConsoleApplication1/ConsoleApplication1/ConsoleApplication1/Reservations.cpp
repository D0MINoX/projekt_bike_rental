#include "Reservations.h"
#include "bikes.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

vector<string> Slice2(const string& tekst) { //funkcja rodzielajaca string po spacji
	vector<string> wyniki;
	istringstream iss(tekst);
	string slowo;

	while (iss >> slowo) {
		wyniki.push_back(slowo);
	}

	return wyniki;
}

vector<vector<string>> Reservations::AllReservations()
{
	fstream File;
	File.open("reservations.txt", ios::in);
	if (File.good() == true) {
		string line;
		vector<vector<string>> allRes;
		while (getline(File, line)) {
			vector<string>sliced_string = Slice2(line);// wektro z podzielonymi danymi rezerwacji
				allRes.push_back(sliced_string);
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();

		return allRes;
	}
	else {
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

vector<vector<string>> Reservations::reservations_date(const wxDateTime& date_log)
{
	fstream File;
	File.open("reservations.txt", ios::in);
	if (File.good() == true) {
		string line, res;
		vector<vector<string>> allRes;
		while (getline(File, line)) {
			vector<string>sliced_string = Slice2(line);// wektro z podzielonymi danymi rezerwacji
			if (sliced_string[2] == date_log.FormatISODate().ToStdString()) {
				allRes.push_back(sliced_string);
			}
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();

		return allRes;
	}
	else {
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

vector<vector<string>> Reservations::reservations_phone(const wxString& phone_log)
{
	fstream File;
	File.open("reservations.txt", ios::in);
	if (File.good() == true) {
		vector<vector<string>> allRes;
		string line;
		while (getline(File, line)) {
			vector<string>sliced_string = Slice2(line);// wektro z podzielonymi danymi rezerwacji
			if (sliced_string[1] == phone_log) {
				allRes.push_back(sliced_string);
			}
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();
		
		return allRes;
	}
	else {
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

void Reservations::SaveReservationToFile(const wxString& name, const wxString& phone, const wxDateTime& date, int mountain, int touring, int gravel, int enduro)
{
	ofstream file("reservations.txt", ios::app);
	if (file.is_open())
	{
		file << name.ToStdString() << " "
			<< phone.ToStdString() << " "
			<< date.FormatISODate().ToStdString() << " "
			<< mountain << " "
			<< touring << " "
			<< gravel << " "
			<< enduro << " "
			<< endl;
		file.close();
		wxMessageBox("Dodano rezerwacje!", "info", wxOK | wxICON_INFORMATION);
	}
	else {
		wxMessageBox("B³¹d zapisu do pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
}

void Reservations::DelRes(const wxString& res)
{
	ifstream inputFile("reservations.txt");
	if (!inputFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		return;
	}

	ofstream tempFile("reservations.tmp");
	if (!tempFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		inputFile.close();
		return;
	}

	string line;
	bool del = false;
	while (getline(inputFile, line)) {
		if (line!=res) {
			tempFile << line << "\n";
		}
		else
		{
			del = true;
			vector<string>sliced_string = Slice2(res.ToStdString());
			bikes addbikes;
			addbikes.AddBikes(stoi(sliced_string[3]), stoi(sliced_string[4]), stoi(sliced_string[5]), stoi(sliced_string[6]));
			wxMessageBox(sliced_string[3], "B³¹d", wxOK | wxICON_ERROR);
		}
	}

	inputFile.close();
	tempFile.close();

	if (remove("reservations.txt") != 0) {
		wxMessageBox("Nie mo¿na usun¹æ pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	else if (rename("reservations.tmp", "reservations.txt") != 0) {
		wxMessageBox("Nie mo¿na zmieniæ nazwy pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	else if (del)
	{
		wxMessageBox("Usuniêto rezewacje: "+res, "Info", wxOK | wxICON_INFORMATION);
	}
}