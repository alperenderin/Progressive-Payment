/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#include "Data.h"


void Data::AddRecord(string file_path, int number, string name_per_period, string company, string project_supervisor, string project_inspector) {

	fstream writeToFile; 
	writeToFile.open(file_path.c_str(), ios::app);	
	writeToFile << to_string(number) << "|" << name_per_period << "|" << company << "|" << project_supervisor << "|" << project_inspector << "\n";	
	writeToFile.close();
}

int Data::FindRecordNumber(string file_path) {
	fstream file;
	file.open(file_path.c_str(), ios::in);

	int index = 0;
	string str;

	if (file.is_open()) {	

		while (getline(file, str))	
			index++;
	}
	file.close();
	return index;	
}

vector<string> Data::StringFragmentation(string row)
{
	vector<string> result;	
	stringstream stream(row);

	while (stream.good()) {
		string substr;
		getline(stream, substr, '|');	
		result.push_back(substr);	
	}

	return result;
}

void Data::DeleteRecord(string file_path, string keyWord) {

	fstream readToFile;
	fstream writeToFile;
	readToFile.open(file_path, ios::in);	
	writeToFile.open("../Data/temp.txt", ios::app);

	int user_selection = 0;
	int skip = false;
	string row = "";
	vector<string> result;

	while (getline(readToFile, row)) {
		result = StringFragmentation(row);

		for (int i = 0; i < result.size(); i++) { 

			if (result.at(i) == keyWord) {

				for (int i = 0; i < result.size(); i++)	
					cout << result.at(i) << " ";

				cout << "\nYukarýdaki Kayýt Bulundu, Gerçekten Silmek Ýstiyor Musunuz? (1-Evet, 0-Hayýr):";
				cin >> user_selection;

				while (user_selection != 1 && user_selection != 0) {	
					cout << "Yanlýs secim yaptiniz, Gerçekten Silmek Ýstiyor Musunuz? (1-Evet, 0-Hayýr):";
					cin >> user_selection;
				}

				if (user_selection == 0) {
					writeToFile << result.at(0) << "|" << result.at(1) << "|" << result.at(2) << "|" << result.at(3) << "|" << result.at(4) << "\n"; 
					skip = true;
					continue;	
				}
				else {
					cout << "Kayýt Silindi" << endl;
					skip = true;
					continue;
				}
			}
		}
		if (!skip == true) 
			writeToFile << result.at(0) << "|" << result.at(1) << "|" << result.at(2) << "|" << result.at(3) << "|" << result.at(4) << "\n"; 
		skip = false;
	}
	readToFile.close();
	writeToFile.close();

	remove(file_path.c_str());	
	rename("../Data/temp.txt", file_path.c_str());
}


void Data::SearchRecord(string file_path, string keyword) {
	fstream file;
	file.open(file_path, ios::in); 

	int user_selection = 0;
	string row = "";
	vector<string> result;

	while (getline(file, row)) { 
		result = StringFragmentation(row); 

		for (int i = 0; i < result.size(); i++) { 

			if (result.at(i) == keyword) {

				for (int i = 0; i < result.size(); i++)
					cout << result.at(i) << " ";
				cout << "\n";
				continue;
			}
		}

	}
	file.close();
}

int Data::NumberOfRecords(string file_path, string keyword) { 
	fstream file;
	file.open(file_path, ios::in);

	int user_selection = 0;
	string row = "";
	vector<string> result;

	int index = 0;

	while (getline(file, row)) { 
		result = StringFragmentation(row);

		for (int i = 0; i < result.size(); i++) {

			if (result.at(i) == keyword) {
				index++;
				continue;
			}
		}

	}
	file.close();
	return index;
}