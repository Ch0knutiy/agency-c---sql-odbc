#include <iostream>
#include <vector>
#include "Route.h"

using namespace std;

class Client
{
public:
	Client();
	Client(long id,
		string surname,
		string name,
		string patronymic,
		string phone,
		string date_of_buy,
		string time_of_buy,
		Route* route);
	Client(const Client& other);
	~Client();

	Client& operator = (Client other);

	void setId(int id);
	void setSurname(string surname);
	void setName(string name);
	void setPatronymic(string patronymic);
	void setPhone(string phone);
	void setDate(string date);
	void setTime(string time);
	void setRoute(Route* route);

	int getId();
	string getSurname();
	string getName();
	string getPatronymic();
	string getPhone();
	string getDate();
	string getTime();
	Route* getRoute();
	
private:
	int id;
	string surname;
	string name;
	string patronymic;
	string phone;
	string date_of_buy;
	string time_of_buy;
	Route* route;
};
