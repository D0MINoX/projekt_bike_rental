#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <wx/wx.h>

using namespace std;

class Reservations
{
public:
	string name, phone, date;
	int mountain_bikes = 0, touring_bikes = 0, gravel_bikes = 0, enduro_bikes = 0;
	vector<vector<string>> AllReservations();
	vector<vector<string>> reservations_date(const wxDateTime& date_log);
	vector<vector<string>> reservations_phone(const wxString& phone_log);
	void SaveReservationToFile(const wxString& name, const wxString& phone, const wxString& date, int mountain, int touring, int gravel, int enduro);
	void DelRes(const wxString& res, bool isRent);
	void RentRes(const wxString& res, const wxString& time, const wxString& place);
};