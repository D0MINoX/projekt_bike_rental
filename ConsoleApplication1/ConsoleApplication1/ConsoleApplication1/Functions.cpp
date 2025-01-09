#include<vector>
#include<iostream>
#include "Functions.h"

vector<string> Functions::Slice(const string& tekst) //funkcja rodzielajaca string po spacji
{
	vector<string> wyniki;
	istringstream iss(tekst);
	string slowo;

	while (iss >> slowo) {
		wyniki.push_back(slowo);
	}

	return wyniki;
}

}
