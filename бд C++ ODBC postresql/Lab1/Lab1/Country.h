#include <iostream>

using namespace std;

class Country
{
public:
	Country();
	Country(long id,
		string country);
	Country(const Country& other);
	~Country();

	Country& operator = (Country other);

	void setId(int id);
	void setCountry(string country);

	int getId();
	string getCountry();

private:
	int id;
	string country;
};

