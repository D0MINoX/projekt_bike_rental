#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include"Users.h"
class Workers:public Users
{

	string login;
	int placeId;
public:
	string LogIn(const string& login, const string& password) override;
};

