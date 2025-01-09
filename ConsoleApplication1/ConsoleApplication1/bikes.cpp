#include "bikes.h"
#include"Functions.h"
vector<string> bikes::CheckBikes(string date)
{
	fstream File;
	File.open("bikes.txt", ios::in);
	if (File.is_open() == true) {
		string line;
		while (getline(File, line)) {
			vector<string>sliced_string = Functions::Slice(line);
			if (sliced_string[4]==date)
			{
				File.close();
				return sliced_string;
			}
		}
		File.close();
		vector<string> a = {"50", "50", "50", "50"};
		return a;
	}
	else {
		wxMessageBox("B³¹d pliku 3", "B³¹d", wxOK | wxICON_ERROR);
		//return error;
	}
}

void bikes::DelBikes(int b1, int b2, int b3, int b4, string date)
{
	ifstream inputFile("bikes.txt");
	if (!inputFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		return;
	}

	ofstream tempFile("bikes.tmp");
	if (!tempFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		inputFile.close();
		return;
	}

	int bike1=50, bike2=50, bike3=50, bike4=50;
	string line;
	bool found = false;

	while (getline(inputFile, line)) {
		vector<string>sliced_string = Functions::Slice(line);
		if (sliced_string[4] != date) {
			tempFile << line << "\n";
		}
		else
		{
			bike1 = stoi(sliced_string[0]) - b1;
			bike2 = stoi(sliced_string[1]) - b2;
			bike3 = stoi(sliced_string[2]) - b3;
			bike4 = stoi(sliced_string[3]) - b4;
			tempFile << bike1 << " " << bike2 << " " << bike3 << " " << bike4 << " " << date << "\n";
			found = true;
		}
	}
	if (!found) {
		bike1 -= b1;
		bike2 -= b2;
		bike3 -= b3;
		bike4 -= b4;
		tempFile << bike1 << " " << bike2 << " " << bike3 << " " << bike4 << " " << date << "\n";
	}

	inputFile.close();
	tempFile.close();

	if (remove("bikes.txt") != 0) {
		wxMessageBox("Nie mo¿na usun¹æ pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	if (rename("bikes.tmp", "bikes.txt") != 0) {
		wxMessageBox("Nie mo¿na zmieniæ nazwy pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
}

void bikes::AddBikes(int b1, int b2, int b3, int b4, string date)
{
	ifstream inputFile("bikes.txt");
	if (!inputFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		return;
	}

	ofstream tempFile("bikes.tmp");
	if (!tempFile.is_open()) {
		wxMessageBox("B³¹d pliku!", "B³¹d", wxOK | wxICON_ERROR);
		inputFile.close();
		return;
	}

	int bike1 = 0, bike2 = 0, bike3 = 0, bike4 = 0;
	string line;
	bool found = false;

	while (getline(inputFile, line)) {
		vector<string>sliced_string = Functions::Slice(line);
		if (sliced_string[4] != date) {
			tempFile << line << "\n";
		}
		else
		{
			bike1 = stoi(sliced_string[0]) + b1;
			bike2 = stoi(sliced_string[1]) + b2;
			bike3 = stoi(sliced_string[2]) + b3;
			bike4 = stoi(sliced_string[3]) + b4;
			tempFile << bike1 << " " << bike2 << " " << bike3 << " " << bike4 << " " << date << "\n";
			found = true;
		}
	}
	if (!found) {
		bike1 += b1;
		bike2 += b2;
		bike3 += b3;
		bike4 += b4;
		tempFile << bike1 << " " << bike2 << " " << bike3 << " " << bike4 << " " << date << "\n";
	}

	inputFile.close();
	tempFile.close();

	if (remove("bikes.txt") != 0) {
		wxMessageBox("Nie mo¿na usun¹æ pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
	if (rename("bikes.tmp", "bikes.txt") != 0) {
		wxMessageBox("Nie mo¿na zmieniæ nazwy pliku!", "B³¹d", wxOK | wxICON_ERROR);
	}
}

