#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include<wx/wx.h>

using namespace std;

class Raporty
{
public:
	int b1 = 0, b2 = 0, b3 = 0, b4 = 0;
	void Generate(string date);
};

