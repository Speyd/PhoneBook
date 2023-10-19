#include <iostream>
#include <vector>
using namespace std;
class PhoneBook {
private:
	vector<char*> full_name;
	vector<char*> home_phone;
	vector<char*> work_phone;
	vector<char*> mobile_phone;
	vector<char*> contact_addinformation;
public:
	int amount_index;
	~PhoneBook() { 
		full_name.resize(0);
		home_phone.resize(0);
		work_phone.resize(0);
		mobile_phone.resize(0);
		contact_addinformation.resize(0);
	}
	void SetFull_Name(const char* newtext,const int choice, const int deleteindex);
	void SetHome_Phone(const char* newtext, const int choice, const int deleteindex);
	void SetWork_Phone(const char* newtext, const int choice, const int deleteindex);
	void SetMobile_Phone(const char* newtext, const int choice, const int deleteindex);
	void SetContact_Addinformation(const char* newtext, const int choice, const int deleteindex);
	const char* GetFull_Name(const int index) { return full_name[index]; }
	const char* GetHome_Phone(const int index) { return home_phone[index]; }
	const char* GetWork_Phone(const int index) { return work_phone[index]; }
	const char* GetMobile_Phone(const int index) { return mobile_phone[index]; }
	const char* GetContact_Addinformation(const int index) { return contact_addinformation[index]; }
	const int SizeFull_Name() { return full_name.size(); }

};