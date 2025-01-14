#include "Reservations.h"
#include "bikes.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include"Functions.h"

//obs³uga wyszukania wszystkich rezerwacji
vector<vector<string>> Reservations::AllReservations()
{
	fstream File;
	File.open("reservations.txt", ios::in);
	if (File.good() == true) { //sprawdzenie po³¹czenia z plikiem
		string line;
		vector<vector<string>> allRes;
		while (getline(File, line)) {
			vector<string>sliced_string =Functions::Slice(line);// wektro z podzielonymi danymi rezerwacji
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

//obs³uga wyszukania po dacie
vector<vector<string>> Reservations::reservations_date(const wxDateTime& date_log)
{
	fstream File;
	File.open("reservations.txt", ios::in);
	if (File.good() == true) { //sprawdzenie po³¹czenia z plikiem
		string line, res;
		vector<vector<string>> allRes;
		while (getline(File, line)) {
			vector<string>sliced_string = Functions::Slice(line);// wektro z podzielonymi danymi rezerwacji
			if (sliced_string[2] == date_log.FormatISODate().ToStdString()) {//sprawdzenie czy data siê zgadza
				allRes.push_back(sliced_string);
			}
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();

		return allRes;
	}
	else 
	{
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

//obs³uga wyszukania po numerze telefonu
vector<vector<string>> Reservations::reservations_phone(const wxString& phone_log)
{
	fstream File;
	File.open("reservations.txt", ios::in);
	if (File.good() == true) { //sprawdznie po³¹czenia z plikiem
		vector<vector<string>> allRes;
		string line;
		while (getline(File, line)) {
			vector<string>sliced_string = Functions::Slice(line);// wektro z podzielonymi danymi rezerwacji
			if (sliced_string[1] == phone_log) { //sprawdzenie czy numer telefonu siê zgadza
				allRes.push_back(sliced_string);
			}
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();
		
		return allRes;
	}
	else
	{
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

//obs³uga dodawania rezerwacji
void Reservations::SaveReservationToFile(const wxString& name, const wxString& phone, const wxString& date, int mountain, int touring, int gravel, int enduro)
{
	ofstream file("reservations.txt", ios::app);
	if (file.is_open()) { //sprawdzenie po³¹czenia z plikiem
		file << name.ToStdString() << " "
			<< phone.ToStdString() << " "
			<< date.ToStdString() << " "
			<< mountain << " "
			<< touring << " "
			<< gravel << " "
			<< enduro << " "
			<< endl;
		file.close();
	}
	else 
	{
		wxMessageBox("B³¹d zapisu do pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
}

//obs³uga usuniêcia rezerwacji
void Reservations::DelRes(const wxString& res,bool isRent)
{
	//sprawdzenie po³¹czenia z plikami
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
		if (line!=res) { //sprawdzenie czy rezerwacja jest inna i przepisanie jej do tymczasowego pliku
			tempFile << line << "\n";
		}
		else
		{
			del = true;
			if (!isRent) { //sprawdza czy jest to usuwanie rezerwacj czy tak¿e jej wypo¿yczenie
				vector<string>sliced_string = Functions::Slice(res.ToStdString());
				bikes addbikes;
				//zmiana iloœci dostêpnych rowerów przy usuwaniu rezerwacji
				addbikes.AddBikes(stoi(sliced_string[3]), stoi(sliced_string[4]), stoi(sliced_string[5]), stoi(sliced_string[6]), sliced_string[2]);
			}
		}
	}

	inputFile.close();
	tempFile.close();

	//sprawdzenie czy wszystkie operacje na plikach siê wykonuj¹
	if (remove("reservations.txt") != 0) {
		wxMessageBox("Nie mo¿na usun¹æ pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	else if (rename("reservations.tmp", "reservations.txt") != 0) {
		wxMessageBox("Nie mo¿na zmieniæ nazwy pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	else if (del && !isRent)
	{
		wxMessageBox("Usuniêto rezewacje: "+res, "Info", wxOK | wxICON_INFORMATION);
	}
	else if (del && isRent)
	{
		wxMessageBox("Wypo¿yczono rezewacje: "+res, "Info", wxOK | wxICON_INFORMATION);
	}
}

//obsuga wypo¿yczenia rezerwacji
void Reservations::RentRes(const wxString& res, const wxString& time, const wxString& place)
{
	ifstream resFile("reservations.txt");
	if (!resFile.is_open()) { //sprwadzenie po³¹czenia z plikiem
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		return;
	}
	bool a = true;
	string line;
	while (getline(resFile, line)&&a) {
		if (line == res) { //sprwadzenie czy rezerwacja istnieje
			vector<string>sliced_string = Functions::Slice(res.ToStdString());

			ofstream reservations("rentals.txt");
			if (!reservations.is_open()) {
				wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
				resFile.close();
				return;
			}

			reservations << sliced_string[0] << " "
				<< sliced_string[1] << " "
				<< time.ToStdString() << " "
				<< sliced_string[3] << " "
				<< sliced_string[4] << " "
				<< sliced_string[5] << " "
				<< sliced_string[6] << " "
				<< place.ToStdString() << " "
				<< endl;

			reservations.close();
			resFile.close();

			DelRes(res, true);
			a = false;
		}
	}
}