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
	int mountain_bikes, touring_bikes, gravel_bikes, enduro_bikes;
	vector<string> CheckBikes();
	void DelBikes(int b1, int b2, int b3, int b4);
	void AddBikes(int b1, int b2, int b3, int b4);
};

