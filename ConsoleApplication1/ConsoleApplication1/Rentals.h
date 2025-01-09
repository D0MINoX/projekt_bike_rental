#pragma once
#include <string>
#include <vector>
#include <wx/wx.h>
#include <sstream>
#include <fstream>

using namespace std;

class Rentals
{
public:
	string name, phone, date, time;
	int mountain_bikes = 0, touring_bikes = 0, gravel_bikes = 0, enduro_bikes = 0;
	vector<vector<string>> AllRentals();
	vector<vector<string>> RentalsPhone(const wxString& phone_log);
	void SaveRentalsToFile(const wxString& name, const wxString& phone, const wxString& date, const wxString& time, int mountain, int touring, int gravel, int enduro, const wxString& place);
	void DelRentals(const wxString& rental);
};

