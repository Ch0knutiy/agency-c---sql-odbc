#include <iostream>
#include "City.h"
#include "Hotel.h"
#include "Company.h"
#include "Employee.h"

using namespace std;

class Route
{
public:
	Route();
	Route(long id,
		string name,
		City* city,
		string duration,
		Hotel* hotel,
		Company* company,
		Employee* employee);
	Route(const Route& other);
	~Route();

	Route& operator = (Route other);

	void setId(int id);
	void setName(string name);
	void setCity(City* city);
	void setDuration(string duration);
	void setHotel(Hotel* hotel);
	void setCompany(Company* company);
	void setEmployee(Employee* employee);

	int getId();
	string getName();
	City* getCity();
	string getDuration();
	Hotel* getHotel();
	Company* getCompany();
	Employee* getEmployee();

private:
	int id;
	string name;
	City* city;
	string duration;
	Hotel* hotel;
	Company* company;
	Employee* employee;
};

