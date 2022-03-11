/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#ifndef Project_h
#define Project_h

#include "Data.h"

class Project : public Data {
public:
	Data data;
	void GenerateProjectReport(string file_path, string keyword);
	vector<string>  GetInitialProgressPayments();
};

#endif // !Project_h
