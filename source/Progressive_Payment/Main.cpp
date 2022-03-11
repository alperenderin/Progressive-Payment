/**
 * File Name: Main.cpp
 * Author	: Alperen Derin
 * Created  : 11.07.2019
 **/

#include "Product.h"
#include "Project.h"
#include "Progressive_Payment.h"
#include "stdlib.h"

static int project_number = 0;
static int product_number = 0;

string name_per_period = "";
string company = "";
string project_supervisor = "";
string project_inspector = "";

int project_number_pp;
int user_selection = 0;
bool first_project_file_control = false;
bool first_product_file_control = false;

void GetProjectData(); 
void GetProductData();
void GetProgressPaymentData();
void AssignRecordNumbers(Data);

Project project;	
Product product;
Progressive_Payment progress_payment;

vector<string> progress_payments;

using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");

	AssignRecordNumbers(project);
	progress_payments = project.GetInitialProgressPayments();

	do {
		cout << "Goruntulemek Istediginiz Kategoriyi Seciniz" << endl;
		cout << "1-Proje Islemleri" << endl;
		cout << "2-Urun Islemleri" << endl;
		cout << "3-Hakedis Islemleri" << endl;
		cout << "0-Sistemden Cik" << endl;
		cin >> user_selection;
		system("CLS");

		switch (user_selection) {

			case 1:
				system("CLS");
				cout << "Proje Ile Ilgili Hangi Islemi Yapmak Istersiniz?" << endl;
				cout << "1-Proje Ekleme" << endl;
				cout << "2-Proje Silme" << endl;
				cout << "3-Proje Arama" << endl;
				cout << "4-Proje Raporlama" << endl;
				cin >> user_selection;

				if (user_selection == 1) {
					GetProjectData();			
					project_number++;			
					project.Data::AddRecord("../Data/Projeler.txt", project_number, name_per_period, company, project_supervisor, project_inspector);	
					cout << "Kayit Basari Ýle Eklendi" << endl;
				}
				if (user_selection == 2) {
					string projectNo;
					cout << "Silmek istediðiniz proje numarasini giriniz:";
					cin.ignore(10, '\n');
					getline(cin, projectNo);

					int index = 0;
					bool delete_confirmation = true;
					
					do {						
						if (progress_payments.at(index++) == projectNo)	
							delete_confirmation = false;
					} while (progress_payments.size() != index);

					if (delete_confirmation != false)
						project.Data::DeleteRecord("../Data/Projeler.txt", projectNo);
					else
						cout << "Girdiginiz Projeye Hakedis Verilgidinden Silme Isleminiz Gerceklestirilemiyor" << endl << endl;
				}
				if (user_selection == 3) {
					string keyword;
					cout << "Aramak istediginiz kayit icerisinde gecen bir anahtar kelime giriniz:";
					cin.ignore(10, '\n');
					getline(cin, keyword);
					project.Data::SearchRecord("../Data/Projeler.txt", keyword);
				}
				if (user_selection == 4) {
					string keyword;
					cout << "Raporlamak istediginiz proje numarasini giriniz" << endl;
					cin.ignore(10, '\n');
					getline(cin, keyword);
					project.GenerateProjectReport("../Data/Projeler.txt", keyword);
				}
				break;
				
			case 2:
				system("CLS");
				cout << "Urunler Ile Ilgili Hangi Islemi Yapmak Istersiniz?" << endl;
				cout << "1-Urun Ekleme" << endl;
				cout << "2-Urun Silme" << endl;
				cout << "3-Urun Arama" << endl;
				cout << "4-Urun Raporlama" << endl;
				cin >> user_selection;

				if (user_selection == 1) {
					GetProductData();
					product_number++;
					product.Data::AddRecord("../Data/Urunler.txt", product_number-1, name_per_period, company, project_supervisor, project_inspector);
					cout << "Kayit Basari Ile Eklendi" << endl;
				}
				if (user_selection == 2) {
					string keyWord;
					cout << "Silmek istediðiniz kayýt içerisinde geçen bir anahtar kelime giriniz:";
					cin.ignore(10, '\n');
					getline(cin, keyWord);
					product.Data::DeleteRecord("../Data/Urunler.txt", keyWord);
				}
				if (user_selection == 3) {
					string keyword;
					cout << "Aramak istediginiz kayit icerisinde gecen bir anahtar kelime giriniz:";
					cin.ignore(10, '\n');
					getline(cin, keyword);
					product.Data::SearchRecord("../Data/Urunler.txt", keyword);
				}
				if (user_selection == 4) {
					string keyword;
					cout << "Raporlamak istediginiz urun ile ilgili bilgileri giriniz" << endl;
					cin.ignore(10, '\n');
					getline(cin, keyword);
					product.ReportProductByKey("../Data/Urunler.txt", keyword);
				}
				break;

			case 3:
				system("CLS");
				cout << "Hakedis Ile Ilgili Hangi Islemi Yapmak Istersiniz?" << endl;
				cout << "1-Hakedis Ekleme" << endl;
				cout << "2-Urun Silme" << endl;
				cout << "3-Urun Listeleme" << endl;
				cout << "4-Urun Guncelleme" << endl;
				cout << "5-Urun Arama" << endl;
				cout << "6-Hakedis Raporlama" << endl;
				cout << "7-Kayitli Projeleri Hakedislerini Raporlama" << endl;
				cin >> user_selection;

				if (user_selection == 1) {
					GetProgressPaymentData(); 
					progress_payment.Data::AddRecord("../Data/Hakedis.txt", project_number_pp, name_per_period, company, project_supervisor, project_inspector);
					cout << "Kayit Basari Ile Eklendi" << endl;
				}
				if (user_selection == 2) {
					string project_num;
					cout << "Silmek istediðiniz urunun numarasýný giriniz:";
					cin.ignore(10, '\n');
					getline(cin, project_num);
					progress_payment.DeleteProductInPP("../Data/Hakedis.txt", project_num);
				}
				if (user_selection == 3) {
					progress_payment.ListProductsFromPP();
				}
				if (user_selection == 4) {
					cin.ignore(10, '\n');
					string project_num, current_product_number, current_product_amount, current_product_price;
					cout << "Hangi projenin hakediþ almýþ urununu degistirmek istersiniz:";
					getline(cin, project_num);
					cout << "Yeni ürünün ürün numarasýný giriniz:";
					getline(cin, current_product_number);
					cout << "Yeni ürünün miktarýný giriniz:";
					getline(cin, current_product_amount);
					cout << "Yeni ürünün fiyatini giriniz:";
					getline(cin, current_product_price);

					if (product.NumberOfRecords("../Data/Urunler.txt", current_product_number) != 0)
						progress_payment.UpdateRecordInPP("../Data/Hakedis.txt", project_num, current_product_number, current_product_amount, current_product_price);
					else
						cout << "Deðiþtirmek istediðiniz hakedis, veri tabanýnda yok!" << endl;
				}
				if (user_selection == 5) {
					string progress_payment_number;
					cin.ignore(10, '\n');

					cout << "Hakediþ almýþ projede kullanýlan urunleri görmek için proje numarasini giriniz";
					getline(cin, progress_payment_number);

					if (progress_payment.NumberOfRecords("../Data/Hakedis.txt", progress_payment_number) == 0)
						cout << "Hakedis alan bu þekilde bir proje yok, lütfen tekrar giriniz";
					else
						progress_payment.SearchProductFromPP("../Data/Hakedis.txt", progress_payment_number);
				}
				if (user_selection == 6) {
					string project_number;
					cout << "Hangi proje için hakedilmiþ ürünleri raporlamak istersiniz, proje numarasini giriniz";
					cin >> project_number;
					progress_payment.ReportProgressPayment(project_number);
				}
				if (user_selection == 7) {
					string term;
					cout << "Hangi donem için tüm projelerin hakedislerini gormek istiyorsunuz?";
					cin >> term;
					progress_payment.ReportPeriodicProgressPayment(term);
				}
				break;

			default:
				system("CLS");
				cout << "Lutfen geçerli bir numara giriniz" << endl;
				break;
	}

	} while (user_selection != 0);

	system("Pause");
}

	void GetProjectData() {
		name_per_period = ""; company = ""; project_supervisor = ""; project_inspector = "";
		bool loop;

		do {
			loop = false;

			cin.ignore(10, '\n');
			cout << "Proje ismini giriniz:"; getline(cin, name_per_period);
			cout << "Yurutucu firmayi giriniz:"; getline(cin, company);
			cout << "Proje sorumlusunu giriniz:"; getline(cin, project_supervisor);
			cout << "Proje kontrolorunu giriniz:"; getline(cin, project_inspector);

			if (name_per_period == "" || company == "" || project_supervisor == "" || project_inspector == "") {
				cout << "Lutfen verileri eksiksiz giriniz" << endl;
				loop = true;
			}
		} while (loop);
		system("CLS");
	}

	void GetProductData() {
		name_per_period = ""; company = ""; project_supervisor = ""; project_inspector = "";
		bool loop = false;
		do {
			loop = false;
			cin.ignore(10, '\n');
			cout << "Urun ismini giriniz:"; getline(cin, name_per_period);
			cout << "Urunun birimini giriniz:"; getline(cin, company);
			cout << "Urunun birim fiyatýný giriniz:"; getline(cin, project_supervisor);
			cout << "Urunun markasini giriniz:"; getline(cin, project_inspector);

			if (name_per_period == "" || company == "" || project_supervisor == "" || project_inspector == "") {
				cout << "Lutfen verileri eksiksiz giriniz" << endl;
				loop = true;
			}
		} while (loop);
		system("CLS");
	}

	void GetProgressPaymentData() {
		project_number_pp = 0; name_per_period = ""; company = ""; project_supervisor = ""; project_inspector = "";
		bool loop = false;
		bool statement = true;
		do {
			loop = false;

			cin.ignore(10, '\n');
			do {
				cout << "Proje Numarasini giriniz:"; cin >> project_number_pp;
				if (statement = (project.NumberOfRecords("../Data/Projeler.txt", to_string(project_number_pp)) == 0))
					cout << "Girdiðiniz projeye numarasýnda bir proje bulunamadi.\nLutfen gecerli bir proje no giriniz." << endl;
			} while (statement);
		
			progress_payments.push_back(to_string(project_number_pp));
			statement = true;

			cin.ignore(10, '\n');
			do {
				cout << "Hakedis donemini giriniz:"; getline(cin, name_per_period);
				if (statement = (name_per_period != to_string(1) && name_per_period != to_string(2) && name_per_period != to_string(3) && name_per_period != to_string(4)))
					cout << "Hakedis donemi 1, 2, 3 veya 4 olarak girilebilir." << endl;
			} while (statement);

			statement = true;

			do {
				cout << "Urunun numarasini giriniz:"; getline(cin, company);
				if (statement = (product.NumberOfRecords("../Data/Urunler.txt", company) == 0))
					cout << "Girdiginiz numaraya gore bir urun bulunamadi, \nLutfen gecerli bir urun numarasi giriniz" << endl;
			} while (statement);

			cout << "Urunun adedini giriniz:"; getline(cin, project_supervisor);
			cout << "Urunun fiyatini giriniz:"; getline(cin, project_inspector);

			if (project_number_pp == 0 || name_per_period == "" || company == "" || project_supervisor == "" || project_inspector == "") {
				cout << "Lutfen verileri eksiksiz giriniz" << endl;
				loop = true;
			}

		} while (loop);
		system("CLS");
	}

	void AssignRecordNumbers(Data data) {

		project_number = data.Data::FindRecordNumber("../Data/Projeler.txt");
		first_project_file_control = false;

		product_number = data.Data::FindRecordNumber("../Data/Urunler.txt");
		first_product_file_control = false;
	}