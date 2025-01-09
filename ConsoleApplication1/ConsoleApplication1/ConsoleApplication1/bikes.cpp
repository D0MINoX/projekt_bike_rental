#include "bikes.h"

vector<string> Slice4(const string& tekst) { //funkcja rodzielajaca string po spacji
	vector<string> wyniki;
	istringstream iss(tekst);
	string slowo;

	while (iss >> slowo) {
		wyniki.push_back(slowo);
	}

	return wyniki;
}

vector<string> bikes::CheckBikes()
{
	fstream File;
	File.open("bikes.txt", ios::in);
	if (File.is_open() == true) {
		string line;
		getline(File, line);
		vector<string>sliced_string = Slice4(line);
		File.close();
		return sliced_string;
	}
	else {
		wxMessageBox("B³¹d pliku 3", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
    return vector<string>();
}

void bikes::DelBikes(int b1, int b2, int b3, int b4)
{
	int bike1=0, bike2=0, bike3=0, bike4=0;
	ifstream FileIn;
	FileIn.open("bikes.txt", ios::in);
	if (FileIn.is_open() == true) {
		string line;
		getline(FileIn, line);
		vector<string>sliced_string = Slice4(line);
		bike1 = stoi(sliced_string[0]) - b1;
		bike2 = stoi(sliced_string[1]) - b2;
		bike3 = stoi(sliced_string[2]) - b3;
		bike4 = stoi(sliced_string[3]) - b4;
		FileIn.close();
		remove("bikes.txt");
	}
	else {
		wxMessageBox("B³¹d pliku 1", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}

	ofstream FileOut("bikes.txt");
	if (FileOut.is_open() == true) {
		if (bike1 > 0 or bike2 > 0 or bike3 > 0 or bike4 > 0) {
			FileOut << bike1 << " " << bike2 << " " << bike3 << " " << bike4;
			FileOut.close();
		}
	}
	else {
		wxMessageBox("B³¹d pliku 2", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

void bikes::AddBikes(int b1, int b2, int b3, int b4)
{
	int bike1 = 0, bike2 = 0, bike3 = 0, bike4 = 0;
	ifstream FileIn;
	FileIn.open("bikes.txt", ios::in);
	if (FileIn.is_open() == true) {
		string line;
		getline(FileIn, line);
		vector<string>sliced_string = Slice4(line);
		bike1 = stoi(sliced_string[0]) + b1;
		bike2 = stoi(sliced_string[1]) + b2;
		bike3 = stoi(sliced_string[2]) + b3;
		bike4 = stoi(sliced_string[3]) + b4;
		FileIn.close();
		remove("bikes.txt");
		wxMessageBox(to_string(bike1), "B³¹d", wxOK | wxICON_ERROR);
	}
	else {
		wxMessageBox("B³¹d pliku 1", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}

	ofstream FileOut("bikes.txt");
	if (FileOut.is_open() == true) {
		//if (bike1 > 0 or bike2 > 0 or bike3 > 0 or bike4 > 0) {
			FileOut << bike1 << " " << bike2 << " " << bike3 << " " << bike4;
			FileOut.close();
		//}
	}
	else {
		wxMessageBox("B³¹d pliku 2", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

