#include "PhoneBook.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <limits>
using namespace std;
PhoneBook phone_book;
int amountcontact_onepage = 2; // Количество кнтактов на одной странице
#pragma region SpecialAbilities
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tТелефонная книга" << endl;
}
void Enter(const int choice ) {
	if(choice != 3 && choice != 4)cin.ignore();//Тут я зделал так, потому-что у дригих функция git.ignore
	//и тут тоже, и по этому что-бы два раза не нажимать на enter я зделал вот-так
	cout << "Нажимте enter для продожения работы: "; cin.get();;
}
#pragma endregion
#pragma region File
void InputInfoFile(const char* info, PhoneBook& phone_book) {
	ofstream file(info);
	file << "Количество контактов на странице:" << amountcontact_onepage << endl << endl;
	for (int i = 0; i != phone_book.SizeFull_Name(); i++) {
		if (phone_book.GetFull_Name(i) != "Информация отсутствует")file << "Имя " << i + 1 << " контакта:" << phone_book.GetFull_Name(i) << endl;
		else file << "Имя " << i + 1 << " контакта:" << endl;
		if(phone_book.GetHome_Phone(i) != "Информация отсутствует")file << "Домашний телефон:" << phone_book.GetHome_Phone(i) << endl;
		else file << "Домашний телефон:"<< endl;
		if (phone_book.GetWork_Phone(i) != "Информация отсутствует")file << "Рабочий телефон:" << phone_book.GetWork_Phone(i) << endl;
		else file << "Рабочий телефон:" << endl;
		if (phone_book.GetMobile_Phone(i) != "Информация отсутствует")file << "Мобильный телефон:" << phone_book.GetMobile_Phone(i) << endl;
		else file << "Мобильный телефон: " << endl;
		if (phone_book.GetHome_Phone(i) != "Информация отсутствует")file << "Дополнительная информация о контакте:" << phone_book.GetContact_Addinformation(i) << endl << endl;
		else file << "Дополнительная информация о контакте:" << endl << endl;
	}
	file.close();
}
void OutInfoFile(const char* info, PhoneBook& phone_book) {//ContactInformation
	ifstream file(info);
	string temp_text;
	while (!file.eof()) {
		getline(file, temp_text);
		char inscribed_text[1000] = "";
		if (temp_text.find(':') != temp_text.size()) {
			for (int i = temp_text.find(':') + 1, index = 0; i != temp_text.size(); i++, index++) inscribed_text[index] = temp_text[i];
		}
		if (temp_text.find("Количество контактов на странице") != string::npos)amountcontact_onepage = stoi(inscribed_text);
		else if (temp_text.find("Имя") != string::npos)phone_book.SetFull_Name(inscribed_text, 0, 0);
		else if (temp_text.find("Домашний телефон") != string::npos)phone_book.SetHome_Phone(inscribed_text, 0, 0);
		else if (temp_text.find("Рабочий телефон") != string::npos)phone_book.SetWork_Phone(inscribed_text, 0, 0);
		else if (temp_text.find("Мобильный") != string::npos)phone_book.SetMobile_Phone(inscribed_text, 0, 0);
		else if (temp_text.find("Дополнительная информация о контакте") != string::npos)phone_book.SetContact_Addinformation(inscribed_text, 0, 0);
	}
	file.close();
}
int CheckEmptyFile(const char* info) {
	fstream file(info);
	file.seekg(0, std::ios::end);
	int size_file = file.tellg();
	file.close();
	return size_file;
}
void SaveNotification(const char* info, PhoneBook& phone_book) {
	int choice_save = 1;
	do {
		ClearScrean();
		cout << "Вы выходите из программы не сохранив информацию!\nИнформацию будем?::\n[1] - Сохранить\n[2] - Не сохранять" << endl;
		if (choice_save >= 0 && choice_save <= 5)cout << "Введите ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
		cin >> choice_save;
	} while (choice_save < 1 || choice_save > 2);
	if (choice_save == 1)InputInfoFile(info, phone_book);
}
#pragma endregion
#pragma region ActionsInformation
void AddNewContact(PhoneBook& phone_book) {
	char temp_text[1000];
	cin.ignore();
	cout << "Введите ФИО нового контакта: ";cin.getline(temp_text, 50);
	phone_book.SetFull_Name(temp_text,0,0);
	cout << "Введите домашний телефон: "; cin.getline(temp_text, 30);
	phone_book.SetHome_Phone(temp_text, 0, 0);
	cout << "Введите рабочий телефон: "; cin.getline(temp_text, 30);
	phone_book.SetWork_Phone(temp_text, 0, 0);
	cout << "Введите мобильный телефон: "; cin.getline(temp_text, 30);
	phone_book.SetMobile_Phone(temp_text, 0, 0);
	cout << "Введите дополнительная информация о контакте : "; cin.getline(temp_text, 1000);
	phone_book.SetContact_Addinformation(temp_text, 0, 0);
}
int PrintInfoContact(PhoneBook& phone_book,const int amount_index,
					  vector<int> find_contact, const int choice,int& delete_index) {
	int page = 1,choice_print,error_input = 0;
	if (find_contact.size() == 0) {
		for (int i = 0; i != amount_index; i++) {
			find_contact.resize(find_contact.size() + 1);
			find_contact[find_contact.size() - 1] = i;
		}
	}
	else  cout << "\nЭто список всех найденых контактов(после любого действия этот текст пропадет)" << endl << endl;
	for (int i = 0; i != amount_index; i++) {
		cout << find_contact[i] + 1 <<" - ый Контакт:\nФИО: " << phone_book.GetFull_Name(find_contact[i]) << endl;
		cout<<"Номер домашнего телефона: " << phone_book.GetHome_Phone(find_contact[i]) << endl;
		cout << "Номер рабочего телефона: " << phone_book.GetWork_Phone(find_contact[i]) << endl;
		cout << "Номер мобильного телефона: " << phone_book.GetMobile_Phone(find_contact[i]) << endl;
		cout << "дополнительная информация о контакте("<< phone_book.GetFull_Name(find_contact[i]) <<"): " 
			 << phone_book.GetContact_Addinformation(find_contact[i]) << endl<<endl;

		if ((find_contact[i] + 1) % amountcontact_onepage == 0 && amount_index > amountcontact_onepage
			|| find_contact[i] + 1 == amount_index && amount_index > amountcontact_onepage ||
			amount_index > 1 && amount_index <= amountcontact_onepage && i + 1 == amount_index && choice == 4) {
			
			cout << page << "-ая страинца из " << ceil(amount_index / float(amountcontact_onepage)) <<endl;
			if (page == 1 && amount_index > amountcontact_onepage) {
				cout << "[1] - Следуйщая страница\n[0] - Выйти в меню" << endl;
			}
			else if (ceil(amount_index / float(amountcontact_onepage)) >= 2) {

				if (page == ceil(amount_index
					/ float(amountcontact_onepage))) {
					
					cout << "[1] - Предыдущая страница\n[0] - Выйти в меню" << endl;
				}

				else if (page != 1 && page < ceil(amount_index
						/ float(amountcontact_onepage))) {

					cout << "[1] - Следуйщая страница  |  [2] - Предыдущая страница\n[0] - Выйти в меню" << endl;
				}
			}
			else if (choice == 4) cout << "[3] - Ввести номер контакта который хотите удлить\n[0] - Выйти в меню" << endl;
			if (error_input == 0)cout << "Введите ваш выбор: ";
			else if (error_input == 1)cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
			else if (error_input == 2)cout << "Вы ввели номер который не соответствует номерам в этом спике!\nВведе ваш выбор: ";
			cin >> choice_print;
			error_input = 0;
			if (choice_print == 0)return 0;
			else if (choice_print == 3 && choice != 4)error_input = 1;
			else if (choice_print == 3 && choice == 4)error_input = 0;
			else if (page == 1 && choice_print != 1)error_input = 1;
			else if (ceil(amount_index / float(amountcontact_onepage)) >= 2) {
				if (page == ceil(amount_index / float(amountcontact_onepage)) && choice_print != 1)error_input = 1;

				else if(page != 1 && page != ceil(amount_index / float(amountcontact_onepage)) && choice_print < 1 ||
					    page != 1 && page != ceil(amount_index 
						/ float(amountcontact_onepage)) && choice_print > 2)error_input = 1;

			}
			else error_input = 1;

			if (error_input == 1) {
				ClearScrean();
				if (page == ceil(amount_index / float(amountcontact_onepage)) &&
					amount_index / float(amountcontact_onepage) != amount_index / amountcontact_onepage) {

					i -= ceil(float(amount_index) / (amountcontact_onepage * page));
				}
				else i -= amountcontact_onepage;
			}
			else if (error_input == 0) {
				ClearScrean();
				if (choice_print == 1) {
					if (page == 1 || page != 1 && page != ceil(amount_index / float(amountcontact_onepage)))page++;
					else if (page == ceil(amount_index / float(amountcontact_onepage))) {
						page--;
						if (amount_index / float(amountcontact_onepage)
							== ceil(amount_index / float(amountcontact_onepage)))i -= amountcontact_onepage + 1;
						else i -= amountcontact_onepage;
					}
				}
				else if (choice_print == 2 && page != 1 && page != ceil(amount_index / float(amountcontact_onepage))) {
					page--;
					i -= amountcontact_onepage + 2;
				}
				else if (choice_print == 3) {
					int delete_index;
					cout << "Введите номер контакта в телефонной книге что-бы его удалить(0 - что-бы выйти к списку): ";
					cin >> delete_index;
					if (delete_index != 0) {
						if (delete_index >= 1 && delete_index <= amount_index) {
							for (int l = 0; l != amount_index; l++) {
								if (delete_index - 1 == find_contact[l])break;
								else if (l + 1 == amount_index)delete_index = 0;
							}
						}
						else delete_index = -1;
						ClearScrean();
						if (delete_index == 0) {
							error_input = 2;
							if (page == ceil(amount_index / float(amountcontact_onepage)) &&
								amount_index / float(amountcontact_onepage) != amount_index / amountcontact_onepage) {

								i -= ceil(float(amount_index) / (amountcontact_onepage * page));
							}
							else i -= amountcontact_onepage;
						}
						else return delete_index;
					}
					else {
						ClearScrean();
						if (page == ceil(amount_index / float(amountcontact_onepage)) &&
							amount_index / float(amountcontact_onepage) != amount_index / amountcontact_onepage) {

							i -= ceil(float(amount_index) / (amountcontact_onepage * page));
						}
						else i -= amountcontact_onepage;
					}
				}
			}
		}
		else if (amount_index <= amountcontact_onepage && i + 1 == amount_index) {
			Enter(choice);
			return 0;
		}
	}
}
void FindInformation(PhoneBook& phone_book,const int choice,int& delete_index) {
	string temp_name;
	vector<int> find_contact;
	cin.ignore();
	if (choice == 3) { cout << "Введите ФИО которое хотите найти: "; getline(cin, temp_name); }
	else if (choice == 4) { cout << "Введите ФИО которое хотите удалить: "; getline(cin, temp_name); }
	for (int i = 0; i != phone_book.SizeFull_Name(); i++) {
		if (phone_book.GetFull_Name(i) == temp_name) {
			find_contact.resize(find_contact.size() + 1);
			find_contact[find_contact.size() - 1] = i;
		}
	}
	cout << "Всего в телефонной книге с ФИО(" << temp_name << ") найдено " << find_contact.size() << " человек" << endl;
	Enter(choice);
	ClearScrean();
	if (find_contact.size() != 0) {
		if (find_contact.size() == 1 && choice == 4 || choice == 3) {
			delete_index = find_contact[0];
			PrintInfoContact(phone_book, find_contact.size(), find_contact, choice, delete_index);

		}else if(find_contact.size() > 1 && choice == 4)delete_index = PrintInfoContact(phone_book, find_contact.size(), find_contact, choice, delete_index);
	}
	else delete_index = -1;
}
void DeleteInfoContact(PhoneBook& phone_book, const int choice,int& delete_index) {
	FindInformation(phone_book, choice,delete_index);
	if (delete_index != -1) {
		phone_book.SetFull_Name("", choice, delete_index);
		phone_book.SetHome_Phone("", choice, delete_index);
		phone_book.SetWork_Phone("", choice, delete_index);
		phone_book.SetMobile_Phone("", choice, delete_index);
		phone_book.SetContact_Addinformation("", choice, delete_index);
		cout << "Контакт успешно удален!" << endl;
	}
	else cout << "Контакт не удален!" << endl;
	Enter(choice);
}
void Setting() {
	int choice_setting = 1;
	do {
		ClearScrean();
		cout << "Настройки\nВыберете действие:\n[1] - Количсество контактов на одной странице\n[0] - Выйти в меню" << endl;
		if (choice_setting >= 0 && choice_setting <=1) cout << "Введите ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
		cin >> choice_setting;
	} while (choice_setting < 0 || choice_setting > 1);
	if (choice_setting == 0)return;
	else if (choice_setting == 1) {
		int temp_amountcontact = amountcontact_onepage;
		do {
			ClearScrean();
			cout << "Настройки вывод" << endl;
			if (amountcontact_onepage >= 0) cout << "Введите новое количество контактов на странице(0 что-бы выйти): ";
			else cout << "Количество контактов на странице не может быть меньше 1!\nСнова введите новое количество контактов на странице(0 что-бы выйти): ";
			cin >> amountcontact_onepage;
		} while (amountcontact_onepage < 0);
		if (amountcontact_onepage == 0)amountcontact_onepage = temp_amountcontact;
	}
}
#pragma endregion
int main() {
	setlocale(LC_ALL, "Rus");
	int choice = 1, delete_index;
	bool check_save = true;
	vector<int> null_mass;
	do {
		ClearScrean();
		cout << "Выберете действие:\n[1] - Загрузить информацию из файла\n[2] - Записать информацию самому\n";
		if (choice >= 1 && choice <= 2) cout << "Введите ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
		cin >> choice;
		if (choice == 1) {
			if (CheckEmptyFile("ContactInformation.txt") == 0) { cout << "Файл пуст!" << endl; Enter(choice); }
			else OutInfoFile("ContactInformation.txt", phone_book);
		}
	} while (choice < 1 || choice > 2);
	do {
		do {
			ClearScrean();
			cout << "Выберете действие:\n[1] - Вывести телефонную книгу\n[2] - Добавить новый контакт"<<
				    "\n[3] - Поиск контактов по ФИО\n[4] - Удалить контакты\n[5] - Настройки\n[6] - Сохранить информацию\n[0] - Выйти из программы" << endl;
			
			if (choice >= 0 && choice <= 6)cout << "Введите ваш выбор: ";
			else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";
			cin >> choice;
		} while (choice < 0 || choice > 6);
		ClearScrean();
		switch (choice) {
			case 0: 
				if (check_save == false)SaveNotification("ContactInformation.txt", phone_book);
				break;
				break;
			case 1:
				if (phone_book.SizeFull_Name() != 0) {
					PrintInfoContact(phone_book, phone_book.SizeFull_Name(), null_mass, choice, delete_index);
				}
				else {
					cout << "Телефонна книга пустая!\n";
					Enter(choice);
				}
				break;
			case 2:AddNewContact(phone_book); check_save = false; break;
			case 3:FindInformation(phone_book, choice, delete_index); break;
			case 4:DeleteInfoContact(phone_book, choice, delete_index); check_save = false; break;
			case 5:Setting(); check_save = false; break;
			case 6:InputInfoFile("ContactInformation.txt", phone_book); check_save = true; break;
		}
	} while (choice != 0);
	return 0;
}