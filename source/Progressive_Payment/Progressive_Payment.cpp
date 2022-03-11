/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#include "Progressive_Payment.h"

void Progressive_Payment::DeleteProductInPP(string file_path, string project_info) {
	fstream file;
	fstream file_temp;
	file.open(file_path, ios::in); 
	file_temp.open("../Data/temp.txt", ios::app);

	
	string row = "";
	vector<string> result;
	int user_selection = 0;

	while (getline(file, row))
	{
		result = Data::StringFragmentation(row); 
		if (result.at(0) == project_info) { 
			
			cout << "\nProje No:" << result.at(0) << "\nHakedis Donemi:" << result.at(1) << "\nUrun Numarasi:" << result.at(2) <<
				"\nUrun Adeti:" << result.at(3) << "\nUrun Fiyati:" << result.at(4) << endl;
			cout << "\Proje numarasýný girdiðini elemanlardan birisi yukarýdadýr, urun, urun adedi, urun fiyatý bilgilerini gercekten silmek istiyor musunuz? (1-Evet, 0-Hayýr)";
			cin >> user_selection;

			while (user_selection != 1 && user_selection != 0) {	
				cout << "Yanlýs secim yaptiniz, Gerçekten Silmek Ýstiyor Musunuz? (1-Evet, 0-Hayýr:)";
				cin >> user_selection;
			}

			if (user_selection == 1)
				file_temp << result.at(0) << "|" << result.at(1) << "\n";
			else 
				file_temp << result.at(0) << "|" << result.at(1) << "|" << result.at(2) << "|" << result.at(3) << "|" << result.at(4) << "\n";
		}
		else 
			file_temp << result.at(0) << "|" << result.at(1) << "|" << result.at(2) << "|" << result.at(3) << "|" << result.at(4) << "\n";
	}

	file.close();
	file_temp.close();

	remove(file_path.c_str());
	rename("../Data/temp.txt", file_path.c_str());
}

void Progressive_Payment::UpdateRecordInPP(string file_path, string project_number, string product_number, string current_amount, string current_price) {
	fstream file;
	fstream file_temp;
	file.open(file_path, ios::in); 
	file_temp.open("../Data/temp.txt", ios::app);

	string row = "";
	vector<string> result;
	int user_selection = 0;

	while (getline(file, row))
	{
		result = Data::StringFragmentation(row); 

		if (result.at(0) == project_number) { 
			
			cout << "\nProje No:" << result.at(0) << "\nHakedis Donemi:" << result.at(1) << "\nUrun Numarasi:" << result.at(2) <<
				"\nUrun Adeti:" << result.at(3) << "\nUrun Fiyati:" << result.at(4) << endl;
			cout << "\Bigisini girdiðiniz verilerden birisi yukarýdadýr, onu güncellemek istiyor musunuz?(1-Evet, 0-Hayýr)";
			cin >> user_selection;

			while (user_selection != 1 && user_selection != 0) {	
				cout << "Yanlýs secim yaptiniz, Gerçekten Güncellemek Ýstiyor Musunuz? (1-Evet, 0-Hayýr):";
				cin >> user_selection;
			}

			if (user_selection == 1)
				file_temp << result.at(0) << "|" << result.at(1) << "|" << product_number << "|" << current_amount << "|" << current_price << "\n";
			else
				file_temp << result.at(0) << "|" << result.at(1) << "|" << result.at(2) << "|" << result.at(3) << "|" << result.at(4) << "\n"; 
		}
		else 
			file_temp << result.at(0) << "|" << result.at(1) << "|" << result.at(2) << "|" << result.at(3) << "|" << result.at(4) << "\n";
	}

	file.close();
	file_temp.close();

	remove(file_path.c_str());
	rename("../Data/temp.txt", file_path.c_str());
}

void Progressive_Payment::SearchProductFromPP(string file_path, string project_number) {

	fstream file;
	fstream file_product;

	file.open(file_path, ios::in);
	file_product.open("../Data/Urunler.txt", ios::in);

	string row;
	string temp_product_number;
	vector<string> result;

	while (getline(file, row)) {	
		result = StringFragmentation(row); 

		if (result.at(0) == project_number) {	
			temp_product_number = result.at(2);

			product_object.Product::ReportProductByKey("../Data/Urunler.txt", temp_product_number);
		}
	}
	file.close();
	file_product.close();
}

void Progressive_Payment::ListProductsFromPP() {
	fstream file;
	file.open("../Data/Hakedis.txt", ios::in);

	vector<string> result;
	string str;
	string product_number[100];
	int index = 0;
	bool same = false;

	while (getline(file, str)) {
		result = StringFragmentation(str);  

		for (int i = 0; i < index; i++) {	
			if (product_number[i] == result.at(2))	
				same = true;
		}
		if (same == false)	
			product_number[index] = result.at(2);

		same = false;
		index++;
	}
	file.close();

	
	fstream file_product;
	file_product.open("../Data/Urunler.txt", std::ios::in);

	std::string row = "";

	while (getline(file_product, row)) {
		result = Data::StringFragmentation(row);

		for (int i = 0; i < index; i++) { 

			if (result.at(0) == product_number[i]) { 
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
	file_product.close();
}

void Progressive_Payment::ReportProgressPayment(string project_number) {

	fstream file;
	fstream file_product;
	file.open("../Data/Hakedis.txt", ios::in);
	file_product.open("../Data/Urunler.txt", ios::in);

	string row, row_product;
	int price, index = 0, total_price = 0;
	vector<string> result, resultUrun;

	while (getline(file, row)) {	
		result = StringFragmentation(row);	

		if (project_number == result.at(0)) {	

			price = stoi(result.at(3));	
			price *= stoi(result.at(4));

			file_product.clear();
			file_product.seekg(0, std::ios::beg);

			while (getline(file_product, row_product)) {
				resultUrun = StringFragmentation(row_product);

				if (result.at(2) == resultUrun.at(0))	
				{
					cout << "-----------------------------------" << endl;
					cout << "Hakediþ Projesi:" << result.at(0) << endl;
					cout << "Hakkediþ Donemi:" << result.at(1) << endl;
					cout << "Kullanilan Urun Numarasi:" << result.at(2) << endl;
					cout << "Urun Tutari:" << price << endl;
					cout << "-----------------------------------" << endl;
				}
			}
			total_price += price;
		}
	}
	cout << "Projenin Toplam Maliyeti:" << total_price << endl << endl;
	file.close();
	file_product.close();
}

void Progressive_Payment::ReportPeriodicProgressPayment(string term) {

	fstream file;
	file.open("../Data/Hakedis.txt", ios::in);

	string row;
	int  index = 0;
	vector<string> result;

	while (getline(file, row)) {	
		result = StringFragmentation(row);	

		if (term == result.at(1)) {	

			cout << "-----------------------------------" << endl;
			cout << "Hakediþ Projesi:" << result.at(0) << endl;
			cout << "Hakkediþ Donemi:" << result.at(1) << endl;
			cout << "Kullanilan Urun Numarasi:" << result.at(2) << endl;
			cout << "Urun Adedi:" << result.at(3) << endl;
			cout << "Urun Tutari:" << result.at(4) << endl;
			cout << "-----------------------------------" << endl << endl;

		}
	}
	file.close();
}
