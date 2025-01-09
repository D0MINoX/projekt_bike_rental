#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Users.h"

using namespace std;

class Client:public Users
{
public:
	string  phone;
	string LogIn(const string& phone, const string& password) override;
};

