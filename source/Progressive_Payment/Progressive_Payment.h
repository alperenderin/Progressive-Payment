/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#include "Data.h"
#include "Product.h"

class Progressive_Payment : public Data
{
public:
	Product product_object;

	void DeleteProductInPP(string file_path, string project_info);
	void UpdateRecordInPP(string file_path, string project_number, string product_number, string current_amount, string current_price);
	void SearchProductFromPP(string file_path, string project_number);

	void ListProductsFromPP();

	void ReportProgressPayment(string project_number);

	void ReportPeriodicProgressPayment(string term);
	
};

