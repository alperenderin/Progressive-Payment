/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#ifndef Product_h
#define Product_h

#include "Data.h"

class Product : public Data {
public:
	void ReportProductByKey(std::string file_path, std::string keyword);
};

#endif // !Product_h
