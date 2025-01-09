#pragma once
#include <wx/wx.h>
#include<string>
#include<vector>
class Functions :public wxApp {
public:
	vector<string> Slice(const string& tekst);
};