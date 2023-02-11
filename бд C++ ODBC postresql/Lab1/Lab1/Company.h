#include <iostream>
#include <vector>
#include "Flights.h"

using namespace std;

class Company
{
public:
	Company();
	Company(long id,
		string name,
		Flights* flights);
	Company(const Company& other);
	~Company();

	Company& operator = (Company other);

	void setId(int id);
	void setName(string name);
	void setFlights(Flights* flights);

	int getId();
	string getName();
	Flights* getFlights();

private:
	int id;
	string name;
	Flights* flights;
};

