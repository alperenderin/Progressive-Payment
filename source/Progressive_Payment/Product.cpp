/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#include "Product.h"

	void Product::ReportProductByKey(std::string file_path, std::string keyword)
	{
		fstream file;
		file.open(file_path, std::ios::in);

		int user_selection = 0;
		std::string row = "";
		vector<string> result;

		while (getline(file, row)) { 
			result = Data::StringFragmentation(row);

			for (int i = 0; i < result.size(); i++) {

				if (result.at(i) == keyword) {
					cout << "----------------------------------------------------------------" << endl;
					cout << "Urun Numarasi:" << result.at(0) << endl;
					cout << "Urun Adi:" << result.at(1) << endl;
					cout << "Urun Birimi:" << result.at(2) << endl;
					cout << "Urun Brim Fiyati:" << result.at(3) << endl;
					cout << "Urun Markasi:" << result.at(4) << endl;
					cout << "----------------------------------------------------------------" << endl;
					continue;
				}
			}
		}
		file.close();
	}
