#include "Client.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

vector<string> Slice3(const string& tekst) { //funkcja rodzielajaca string po spacji
	vector<string> wyniki;
	istringstream iss(tekst);
	string slowo;

	while (iss >> slowo) {
		wyniki.push_back(slowo);
	}

	return wyniki;
}

string Client::LogIn(const string& phone, const string& password)
{
	fstream File;
	File.open("clients.txt", ios::in);
	if (File.good() == true) {
		string line;
		while (getline(File, line)) {
			vector<string>sliced_string = Slice3(line);// wektro z podzielonymi danymi uzytkownika
			if (sliced_string[3] == phone && sliced_string[4] == password) {
				id = stoi(sliced_string[0]);
				name = sliced_string[1];
				surname = sliced_string[2];
				this->phone = sliced_string[3];
				File.close();
				isLogged = true;
				return to_string(id) + " " + name + " " + surname;
			}
		}
		File.clear();
		File.seekg(0, ios::beg);
		return "B��dne dane logowania";
	}
	else
	{
		return "B��d po��czenia z baz�";
	}
}