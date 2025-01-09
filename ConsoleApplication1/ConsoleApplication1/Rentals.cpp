#include "Rentals.h"
#include "bikes.h"
#include "Functions.h"

vector<vector<string>> Rentals::AllRentals()
{
	fstream File;
	File.open("rentals.txt", ios::in);
	if (File.good() == true) {
		string line;
		vector<vector<string>> allRentals;
		while (getline(File, line)) {
			vector<string>sliced_string = Functions::Slice(line);// wektro z podzielonymi danymi rezerwacji
			allRentals.push_back(sliced_string);
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();

		return allRentals;
	}
	else {
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

vector<vector<string>> Rentals::RentalsPhone(const wxString& phone_log)
{
	fstream File;
	File.open("rentals.txt", ios::in);
	if (File.good() == true) {
		vector<vector<string>> allRentals;
		string line;
		while (getline(File, line)) {
			vector<string>sliced_string = Functions::Slice(line);// wektro z podzielonymi danymi rezerwacji
			if (sliced_string[1] == phone_log) {
				allRentals.push_back(sliced_string);
			}
		}
		File.clear();
		File.seekg(0, ios::beg);
		File.close();

		return allRentals;
	}
	else {
		wxMessageBox("B³¹d pliku", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

void Rentals::SaveRentalsToFile(const wxString& name, const wxString& phone, const wxString& date, const wxString& time, int mountain, int touring, int gravel, int enduro, const wxString& place)
{
	ofstream file("rentals.txt", ios::app);
	if (file.is_open())
	{
		file << name.ToStdString() << " "
			<< phone.ToStdString() << " "
			<< date.ToStdString() << " "
			<< time.ToStdString() << " "
			<< mountain << " "
			<< touring << " "
			<< gravel << " "
			<< enduro << " "
			<< place << " "
			<< endl;
		file.close();
		wxMessageBox("Dodano wypo¿yczenie!", "info", wxOK | wxICON_INFORMATION);
	}
	else {
		wxMessageBox("B³¹d zapisu do pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
}

void Rentals::DelRentals(const wxString& rental)
{
	ifstream inputFile("rentals.txt");
	if (!inputFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		return;
	}

	ofstream tempFile("rentals.tmp");
	if (!tempFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		inputFile.close();
		return;
	}

	string line;
	bool del = false;
	while (getline(inputFile, line)) {
		if (line != rental) {
			tempFile << line << "\n";
		}
		else
		{
			ofstream returned("rentals-returned.txt", ios::app);
			if (!returned.is_open()) {
				wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
				return;
			}
			returned << line << "\n";

			del = true;
			vector<string>sliced_string = Functions::Slice(rental.ToStdString());
			bikes addbikes;
			addbikes.AddBikes(stoi(sliced_string[4]), stoi(sliced_string[5]), stoi(sliced_string[6]), stoi(sliced_string[7]), sliced_string[2]);
		}
	}

	inputFile.close();
	tempFile.close();

	if (remove("rentals.txt") != 0) {
		wxMessageBox("Nie mo¿na usun¹æ pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	else if (rename("rentals.tmp", "rentals.txt") != 0) {
		wxMessageBox("Nie mo¿na zmieniæ nazwy pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	else if (del)
	{
		wxMessageBox("Usuniêto wypo¿yczenie: " + rental, "Info", wxOK | wxICON_INFORMATION);
	}
}
