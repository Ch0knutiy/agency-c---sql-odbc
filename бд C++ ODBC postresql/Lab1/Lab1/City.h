#include <iostream>
#include "Country.h"

using namespace std;

class City
{
public:
	City();
	City(long id,
		string city,
		Country* country);
	City(const City& other);
	~City();

	City& operator = (City other);

	void setId(long id);
	void setCity(string city);
	void setCountry(Country* country);

	int getId();
	string getCity();
	Country* getCountry();

private:
	int id;
	string city;
	Country* country;
};