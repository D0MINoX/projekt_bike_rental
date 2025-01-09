#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Users
{
public:
	string name, surname, password;
	int id;
	bool isLogged=false;
	string virtual LogIn(const string& login, const string& password)=0;
};