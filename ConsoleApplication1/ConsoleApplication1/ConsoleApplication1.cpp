#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#ifdef _WIN32
#define SYSTEM system("chcp 1250 > null");

#elif _WIN64
#define SYSTEM system("chcp 1250 > null");

#endif

using namespace std;

vector<string> Slice(const string& tekst) { //funkcja rodzielajaca string po spacji
	vector<string> wyniki;
	istringstream iss(tekst);
	string slowo;

	while (iss >> slowo) {
		wyniki.push_back(slowo);
	}

	return wyniki;
}

class Reservations {
	string name, phone, date;
	int mountain_bikes = 0, touring_bikes = 0, gravel_bikes = 0, enduro_bikes = 0;

public:
	void reservations_date() {	//metoda podająca rezerwacje dla danej daty
		fstream File;
		File.open("reservations.txt", ios::in);
		if (File.good() == true) {
			string line, date_log;
			
				int res_num = 0;
				cout << "Podaj date: ";
				cin >> date_log;
				cout << "Imię\tNumer\t\tData\t\tgórskie\tturystyczne\tgravel\tenduro";
				while (getline(File, line)) {
					vector<string>sliced_string = Slice(line);// wektro z podzielonymi danymi rezerwacji
					if (sliced_string[2] == date_log) {
						res_num++;
						cout << endl;
						for (int i = 0; i <= 6; i++) {
							cout << sliced_string[i]<<"\t";
						}
						
					}
				}
				File.clear();
				File.seekg(0, ios::beg);
				if(!res_num)cout << "Brak rezerwacji" << endl;
				
			
			File.close();
		}
		else {
			cout << " Błąd połączenia z bazą";
		}
	}
	void reservations_phone() {	//metoda podająca rezerwacje dla danej daty
		fstream File;
		File.open("reservations.txt", ios::in);
		if (File.good() == true) {
			string line, phone_log;

			int res_num = 0;
			cout << "Podaj nr telefonu: ";
			cin >> phone_log;
			cout << "Imię\tNumer\t\tData\t\tgórskie\tturystyczne\tgravel\tenduro";
			while (getline(File, line)) {
				vector<string>sliced_string = Slice(line);// wektro z podzielonymi danymi rezerwacji
				if (sliced_string[1] == phone_log) {
					res_num++;
					cout << endl;
					for (int i = 0; i <= 6; i++) {
						cout << sliced_string[i] << "\t";
					}

				}
			}
			File.clear();
			File.seekg(0, ios::beg);
			if (!res_num)cout <<endl<< "Brak rezerwacji" << endl;


			File.close();
		}
		else {
			cout << " Błąd połączenia z bazą";
		}
	}
};

class User {
	string name, surname, login, password;
	int id, placeId;

public:
	int logIn() {
		fstream File;
		File.open("workers.txt", ios::in);
		if (File.good() == true) {
			string line, loginlog, passwd;
			while (true) {
				cout << "Podaj login: ";
				cin >> loginlog;
				cout << "podaj haslo: ";
				cin >> passwd;
				while (getline(File, line)) {
					vector<string>sliced_string = Slice(line);// wektro z podzielonymi danymi uzytkownika
					if (sliced_string[3] == loginlog && sliced_string[4] == passwd) {
						id = stoi(sliced_string[0]);
						name = sliced_string[1];
						surname = sliced_string[2];
						cout << "Witaj " << name << endl;
						File.close();
						return id;
					}
				}
				File.clear();
				File.seekg(0, ios::beg);
				cout << "Bledne dane logowania" << endl;
			}
		}
		else {
			cout << " Błąd połączenia z bazą";
		}

	}
};


int main()
{
	SYSTEM;
	Reservations reserv;
	reserv.reservations_phone();

}