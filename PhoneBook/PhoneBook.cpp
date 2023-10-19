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
using namespace std;
string temp_text = "Информация отсутствует";
void PhoneBook::SetFull_Name(const char* newtext, const int choice,const int deleteindex) {
	if (choice != 4) {
		full_name.resize(full_name.size() + 1);
		if (strlen(newtext) == 0) {
			full_name[full_name.size() - 1] = new char[temp_text.size() + 1];
			for (int i = 0; i <= temp_text.size(); i++)full_name[full_name.size() - 1][i] = temp_text[i];
		}
		else {
			full_name[full_name.size() - 1] = new char[strlen(newtext) + 1];
			for (int i = 0; i <= strlen(newtext); i++)full_name[full_name.size() - 1][i] = newtext[i];
		}
	}
	else {
		if(full_name.size() != 0)swap(full_name[deleteindex], full_name[full_name.size() - 1]);
		full_name.resize(full_name.size() - 1);
	}
}

void PhoneBook::SetHome_Phone(const char* newtext, const int choice, const int deleteindex) {
	if (choice != 4) {
		home_phone.resize(home_phone.size() + 1);
		if (strlen(newtext) == 0) {
			home_phone[home_phone.size() - 1] = new char[temp_text.size() + 1];
			for (int i = 0; i <= temp_text.size(); i++)home_phone[home_phone.size() - 1][i] = temp_text[i];
		}
		else {
			home_phone[home_phone.size() - 1] = new char[strlen(newtext) + 1];
			for (int i = 0; i <= strlen(newtext); i++)home_phone[home_phone.size() - 1][i] = newtext[i];
		}
	}
	else {
		if(home_phone.size() != 1)swap(home_phone[deleteindex], home_phone[home_phone.size() - 1]);
		home_phone.resize(home_phone.size() - 1);
	}
}

void PhoneBook::SetWork_Phone(const char* newtext, const int choice, const int deleteindex) {
	if (choice != 4) {
		work_phone.resize(work_phone.size() + 1);
		if (strlen(newtext) == 0) {
			work_phone[work_phone.size() - 1] = new char[temp_text.size() + 1];
			for (int i = 0; i <= temp_text.size(); i++)work_phone[work_phone.size() - 1][i] = temp_text[i];
		}
		else {
			work_phone[work_phone.size() - 1] = new char[strlen(newtext) + 1];
			for (int i = 0; i <= strlen(newtext); i++)work_phone[work_phone.size() - 1][i] = newtext[i];
		}
	}
	else {
		if(work_phone.size() != 1)swap(work_phone[deleteindex], work_phone[work_phone.size() - 1]);
		work_phone.resize(work_phone.size() - 1);
	}
}

void PhoneBook::SetMobile_Phone(const char* newtext, const int choice, const int deleteindex) {
	if (choice != 4) {
		mobile_phone.resize(mobile_phone.size() + 1);
		if (strlen(newtext) == 0) {
			mobile_phone[mobile_phone.size() - 1] = new char[temp_text.size() + 1];
			for (int i = 0; i <= temp_text.size(); i++)mobile_phone[mobile_phone.size() - 1][i] = temp_text[i];
		}
		else {
			mobile_phone[mobile_phone.size() - 1] = new char[strlen(newtext) + 1];
			for (int i = 0; i <= strlen(newtext); i++)mobile_phone[mobile_phone.size() - 1][i] = newtext[i];
		}
	}
	else {
		if(mobile_phone.size() != 1)swap(mobile_phone[deleteindex], mobile_phone[mobile_phone.size() - 1]);
		mobile_phone.resize(mobile_phone.size() - 1);
	}
}

void PhoneBook::SetContact_Addinformation(const char* newtext, const int choice, const int deleteindex) {
	if (choice != 4) {
		contact_addinformation.resize(contact_addinformation.size() + 1);
		if (strlen(newtext) == 0) {
			contact_addinformation[contact_addinformation.size() - 1] = new char[temp_text.size() + 1];
			for (int i = 0; i <= temp_text.size(); i++)contact_addinformation[contact_addinformation.size() - 1][i] = temp_text[i];
		}
		else {
			contact_addinformation[contact_addinformation.size() - 1] = new char[strlen(newtext) + 1];
			for (int i = 0; i <= strlen(newtext); i++)contact_addinformation[contact_addinformation.size() - 1][i] = newtext[i];
		}
	}
	else {
		if(contact_addinformation.size() != 1)swap(contact_addinformation[deleteindex], contact_addinformation[contact_addinformation.size() - 1]);
		contact_addinformation.resize(contact_addinformation.size() - 1);
	}
}
