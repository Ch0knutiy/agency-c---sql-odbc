#include <iostream>
#include <vector>
#include "Transfer.h"

using namespace std;

class Employee
{
public:
	Employee();
	Employee(long id, 
		string surname, 
		string name, 
		string patronymic, 
		string address,
		string birth,
		string post,
		int salary,
		Transfer* transfer_id,
		string phone,
		bool hasRow);
	Employee(const Employee& other);
	~Employee();

	Employee& operator = (Employee other);

	void setId(int id);
	void setSurname(string surname);
	void setName(string name);
	void setPatronymic(string patronymic);
	void setAddress(string address);
	void setBirth(string birth);
	void setPost(string post);
	void setSalary(int salary);
	void setTransferNum(Transfer* transfer_num);
	void setPhone(string phone);
	void setHasRow(bool _hasRow);

	int getId();
	string getSurname();
	string getName();
	string getPatronymic();
	string getAddress();
	string getBirth();
	string getPost();
	int getSalary();
	Transfer* getTransferNum();
	string getPhone();
	bool getHasRow();

private:
	int id;
	string surname;
	string name;
	string patronymic;
	string address;
	string birth;
	string post;
	int salary;
	Transfer* transfer_num;
	string phone;
	bool hasRow;
};
