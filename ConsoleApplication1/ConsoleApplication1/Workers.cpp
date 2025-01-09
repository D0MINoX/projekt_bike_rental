#include "Workers.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Functions.h"


string Workers::LogIn(const string& login, const string& password)
{
	fstream File;
	File.open("workers.txt", ios::in);
	if (File.good() == true) {
		string line;
		while (getline(File, line)) {
			vector<string>sliced_string = Functions::Slice(line);// wektro z podzielonymi danymi uzytkownika
			if (sliced_string[3] == login && sliced_string[4] == password) {
				id = stoi(sliced_string[0]);
				name = sliced_string[1];
				surname = sliced_string[2];
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