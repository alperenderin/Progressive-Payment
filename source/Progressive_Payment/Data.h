/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#ifndef Data_h
#define Data_h

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Data {
public:
	void AddRecord(string file_path, int number, string name_per_period, string company, string project_supervisor, string project_inspector);
	int FindRecordNumber(string file_path);
	vector<string> StringFragmentation(string row);
	void DeleteRecord(string file_path, string keyword);
	void SearchRecord(string file_path, string keyword);
	int NumberOfRecords(string file_path, string keyword);
};

#endif // !Data_h
