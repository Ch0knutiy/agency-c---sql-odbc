#include "Route.h"

Route::Route() {
	id = 0;
	name = "";
	city = NULL;
	duration = "";
	hotel = NULL;
	company = NULL;
	employee = NULL;
}

Route::Route(long id, string name, City* city, string duration, Hotel* hotel, Company* company, Employee* employee) {
	this->id = id;
	this->name = name;
	this->city = city;
	this->duration = duration;
	this->hotel = hotel;
	this->company = company;
	this->employee = employee;
}

Route::Route(const Route& other) {
	id = other.id;
	name = other.name;
	city = other.city;
	duration = other.duration;
	hotel = other.hotel;
	company = other.company;
	employee = other.employee;
}

Route::~Route() {}

Route& Route::operator = (Route other)
{
	this->id = other.getId();
	this->name = other.getName();
	this->city = other.getCity();
	this->duration = other.getDuration();
	this->hotel = other.getHotel();
	this->company = other.getCompany();
	this->employee = other.getEmployee();
	return *this;
}


void Route::setId(int id) {
	this->id = id;
}

void Route::setName(string name) {
	this->name = name;
}

void Route::setCity(City* city) {
	this->city = city;
}
void Route::setDuration(string duration) {
	this->duration = duration;
}
void Route::setHotel(Hotel* hotel){
	this->hotel = hotel;
}
void Route::setCompany(Company* company){
	this->company = company;
}
void Route::setEmployee(Employee* employee){
	this->employee = employee;
}

int Route::getId() {
	return id;
}
string Route::getName(){
	return name;

}
City* Route::getCity(){
	return city;
}
string Route::getDuration(){
	return duration;
}
Hotel* Route::getHotel(){
	return hotel;
}
Company* Route::getCompany(){
	return company;
}
Employee* Route::getEmployee(){
	return employee;
}