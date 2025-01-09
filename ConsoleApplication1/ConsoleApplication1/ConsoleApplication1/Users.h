#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Users
{
public:
	string name, surname, login, password;
	int id, placeId;
	bool isLogged=false;
	string LogIn(const string& login, const string& password);
};