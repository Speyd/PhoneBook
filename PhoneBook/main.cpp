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
int amountcontact_onepage = 2; // ���������� �������� �� ����� ��������
#pragma region SpecialAbilities
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\t���������� �����" << endl;
}
void Enter(const int choice ) {
	if(choice != 3 && choice != 4)cin.ignore();//��� � ������ ���, ������-��� � ������ ������� git.ignore
	//� ��� ����, � �� ����� ���-�� ��� ���� �� �������� �� enter � ������ ���-���
	cout << "������� enter ��� ���������� ������: "; cin.get();;
}
#pragma endregion
#pragma region File
void InputInfoFile(const char* info, PhoneBook& phone_book) {
	ofstream file(info);
	file << "���������� ��������� �� ��������:" << amountcontact_onepage << endl << endl;
	for (int i = 0; i != phone_book.SizeFull_Name(); i++) {
		if (phone_book.GetFull_Name(i) != "���������� �����������")file << "��� " << i + 1 << " ��������:" << phone_book.GetFull_Name(i) << endl;
		else file << "��� " << i + 1 << " ��������:" << endl;
		if(phone_book.GetHome_Phone(i) != "���������� �����������")file << "�������� �������:" << phone_book.GetHome_Phone(i) << endl;
		else file << "�������� �������:"<< endl;
		if (phone_book.GetWork_Phone(i) != "���������� �����������")file << "������� �������:" << phone_book.GetWork_Phone(i) << endl;
		else file << "������� �������:" << endl;
		if (phone_book.GetMobile_Phone(i) != "���������� �����������")file << "��������� �������:" << phone_book.GetMobile_Phone(i) << endl;
		else file << "��������� �������: " << endl;
		if (phone_book.GetHome_Phone(i) != "���������� �����������")file << "�������������� ���������� � ��������:" << phone_book.GetContact_Addinformation(i) << endl << endl;
		else file << "�������������� ���������� � ��������:" << endl << endl;
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
		if (temp_text.find("���������� ��������� �� ��������") != string::npos)amountcontact_onepage = stoi(inscribed_text);
		else if (temp_text.find("���") != string::npos)phone_book.SetFull_Name(inscribed_text, 0, 0);
		else if (temp_text.find("�������� �������") != string::npos)phone_book.SetHome_Phone(inscribed_text, 0, 0);
		else if (temp_text.find("������� �������") != string::npos)phone_book.SetWork_Phone(inscribed_text, 0, 0);
		else if (temp_text.find("���������") != string::npos)phone_book.SetMobile_Phone(inscribed_text, 0, 0);
		else if (temp_text.find("�������������� ���������� � ��������") != string::npos)phone_book.SetContact_Addinformation(inscribed_text, 0, 0);
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
		cout << "�� �������� �� ��������� �� �������� ����������!\n���������� �����?::\n[1] - ���������\n[2] - �� ���������" << endl;
		if (choice_save >= 0 && choice_save <= 5)cout << "������� ��� �����: ";
		else cout << "���� ������ ������!\n������� ��� ����� �����: ";
		cin >> choice_save;
	} while (choice_save < 1 || choice_save > 2);
	if (choice_save == 1)InputInfoFile(info, phone_book);
}
#pragma endregion
#pragma region ActionsInformation
void AddNewContact(PhoneBook& phone_book) {
	char temp_text[1000];
	cin.ignore();
	cout << "������� ��� ������ ��������: ";cin.getline(temp_text, 50);
	phone_book.SetFull_Name(temp_text,0,0);
	cout << "������� �������� �������: "; cin.getline(temp_text, 30);
	phone_book.SetHome_Phone(temp_text, 0, 0);
	cout << "������� ������� �������: "; cin.getline(temp_text, 30);
	phone_book.SetWork_Phone(temp_text, 0, 0);
	cout << "������� ��������� �������: "; cin.getline(temp_text, 30);
	phone_book.SetMobile_Phone(temp_text, 0, 0);
	cout << "������� �������������� ���������� � �������� : "; cin.getline(temp_text, 1000);
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
	else  cout << "\n��� ������ ���� �������� ���������(����� ������ �������� ���� ����� ��������)" << endl << endl;
	for (int i = 0; i != amount_index; i++) {
		cout << find_contact[i] + 1 <<" - �� �������:\n���: " << phone_book.GetFull_Name(find_contact[i]) << endl;
		cout<<"����� ��������� ��������: " << phone_book.GetHome_Phone(find_contact[i]) << endl;
		cout << "����� �������� ��������: " << phone_book.GetWork_Phone(find_contact[i]) << endl;
		cout << "����� ���������� ��������: " << phone_book.GetMobile_Phone(find_contact[i]) << endl;
		cout << "�������������� ���������� � ��������("<< phone_book.GetFull_Name(find_contact[i]) <<"): " 
			 << phone_book.GetContact_Addinformation(find_contact[i]) << endl<<endl;

		if ((find_contact[i] + 1) % amountcontact_onepage == 0 && amount_index > amountcontact_onepage
			|| find_contact[i] + 1 == amount_index && amount_index > amountcontact_onepage ||
			amount_index > 1 && amount_index <= amountcontact_onepage && i + 1 == amount_index && choice == 4) {
			
			cout << page << "-�� �������� �� " << ceil(amount_index / float(amountcontact_onepage)) <<endl;
			if (page == 1 && amount_index > amountcontact_onepage) {
				cout << "[1] - ��������� ��������\n[0] - ����� � ����" << endl;
			}
			else if (ceil(amount_index / float(amountcontact_onepage)) >= 2) {

				if (page == ceil(amount_index
					/ float(amountcontact_onepage))) {
					
					cout << "[1] - ���������� ��������\n[0] - ����� � ����" << endl;
				}

				else if (page != 1 && page < ceil(amount_index
						/ float(amountcontact_onepage))) {

					cout << "[1] - ��������� ��������  |  [2] - ���������� ��������\n[0] - ����� � ����" << endl;
				}
			}
			else if (choice == 4) cout << "[3] - ������ ����� �������� ������� ������ ������\n[0] - ����� � ����" << endl;
			if (error_input == 0)cout << "������� ��� �����: ";
			else if (error_input == 1)cout << "���� ������ ������!\n������� ��� ����� �����: ";
			else if (error_input == 2)cout << "�� ����� ����� ������� �� ������������� ������� � ���� �����!\n����� ��� �����: ";
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
					cout << "������� ����� �������� � ���������� ����� ���-�� ��� �������(0 - ���-�� ����� � ������): ";
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
	if (choice == 3) { cout << "������� ��� ������� ������ �����: "; getline(cin, temp_name); }
	else if (choice == 4) { cout << "������� ��� ������� ������ �������: "; getline(cin, temp_name); }
	for (int i = 0; i != phone_book.SizeFull_Name(); i++) {
		if (phone_book.GetFull_Name(i) == temp_name) {
			find_contact.resize(find_contact.size() + 1);
			find_contact[find_contact.size() - 1] = i;
		}
	}
	cout << "����� � ���������� ����� � ���(" << temp_name << ") ������� " << find_contact.size() << " �������" << endl;
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
		cout << "������� ������� ������!" << endl;
	}
	else cout << "������� �� ������!" << endl;
	Enter(choice);
}
void Setting() {
	int choice_setting = 1;
	do {
		ClearScrean();
		cout << "���������\n�������� ��������:\n[1] - ����������� ��������� �� ����� ��������\n[0] - ����� � ����" << endl;
		if (choice_setting >= 0 && choice_setting <=1) cout << "������� ��� �����: ";
		else cout << "���� ������ ������!\n������� ��� ����� �����: ";
		cin >> choice_setting;
	} while (choice_setting < 0 || choice_setting > 1);
	if (choice_setting == 0)return;
	else if (choice_setting == 1) {
		int temp_amountcontact = amountcontact_onepage;
		do {
			ClearScrean();
			cout << "��������� �����" << endl;
			if (amountcontact_onepage >= 0) cout << "������� ����� ���������� ��������� �� ��������(0 ���-�� �����): ";
			else cout << "���������� ��������� �� �������� �� ����� ���� ������ 1!\n����� ������� ����� ���������� ��������� �� ��������(0 ���-�� �����): ";
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
		cout << "�������� ��������:\n[1] - ��������� ���������� �� �����\n[2] - �������� ���������� ������\n";
		if (choice >= 1 && choice <= 2) cout << "������� ��� �����: ";
		else cout << "���� ������ ������!\n������� ��� ����� �����: ";
		cin >> choice;
		if (choice == 1) {
			if (CheckEmptyFile("ContactInformation.txt") == 0) { cout << "���� ����!" << endl; Enter(choice); }
			else OutInfoFile("ContactInformation.txt", phone_book);
		}
	} while (choice < 1 || choice > 2);
	do {
		do {
			ClearScrean();
			cout << "�������� ��������:\n[1] - ������� ���������� �����\n[2] - �������� ����� �������"<<
				    "\n[3] - ����� ��������� �� ���\n[4] - ������� ��������\n[5] - ���������\n[6] - ��������� ����������\n[0] - ����� �� ���������" << endl;
			
			if (choice >= 0 && choice <= 6)cout << "������� ��� �����: ";
			else cout << "���� ������ ������!\n������� ��� ����� �����: ";
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
					cout << "��������� ����� ������!\n";
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