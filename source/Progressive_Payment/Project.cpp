/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#include "Project.h"

void Project::GenerateProjectReport(string file_path, string keyword)
{
	fstream file;
	file.open(file_path, std::ios::in);

	int user_selection = 0;
	string row = "";
	vector<string> result;

	while (getline(file, row)) { 

		result = StringFragmentation(row);

		if (result.at(0) == keyword) {
			cout << "----------------------------------------------------------------" << endl;
			cout << "Projenin Numarasi:" << result.at(0) << endl;
			cout << "Projenin Adi:" << result.at(1) << endl;
			cout << "Projeyi Yuruten Firma:" << result.at(2) << endl;
			cout << "Projenin Sorumlusu:" << result.at(3) << endl;
			cout << "Projenin Kontroloru:" << result.at(4) << endl;
			cout << "----------------------------------------------------------------" << endl;
			break;
		}

	}
	file.close();
}

vector<string>  Project::GetInitialProgressPayments() {
	
	fstream readToFile;
	readToFile.open("../Data/Hakedis.txt", std::ios::in); 

	string row = "";
	vector<string> result;

	vector<string> progressive_payments;
	int index = 0;
	
	while (getline(readToFile, row)) {
		result = data.Data::StringFragmentation(row);

		progressive_payments.push_back(result.at(0));
	}

	readToFile.close();
	return progressive_payments;	
}