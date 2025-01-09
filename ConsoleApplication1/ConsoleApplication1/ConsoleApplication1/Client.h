#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Client
{
public:
	string name, surname, phone, password;
	int id;
	bool isLogged = false;
	string LogIn(const string& phone, const string& password);
};

