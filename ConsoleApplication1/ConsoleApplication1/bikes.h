#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <wx/wx.h>
#include <sstream>

using namespace std;

class bikes
{
public:
	int mountain_bikes=50, touring_bikes=50, gravel_bikes=50, enduro_bikes=50;
	vector<string> CheckBikes(string date);
	void DelBikes(int b1, int b2, int b3, int b4, string date);
	void AddBikes(int b1, int b2, int b3, int b4, string date);
};
