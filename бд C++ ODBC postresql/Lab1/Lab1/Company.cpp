#include "Company.h"

Company::Company() : flights(0) {
   id = 0;
   name = "";
}
Company::Company(long id, string name, Flights* flights) {
   this->id = id;
   this->name = name;
   this->flights = flights;
}
Company::Company(const Company& other)
{
   this->id = other.id;
   this->name = other.name;
   this->flights = other.flights;
}

Company::~Company() {}

Company& Company::operator = (Company other)
{
   this->id = other.getId();
   this->name = other.getName();
   this->flights = other.getFlights();
   return *this;
}

void Company::setId(int id) {
   this->id = id;
}
void Company::setName(string name) {
   this->name = name;
}
void Company::setFlights(Flights* flights) {
   this->flights = flights;
}

int Company::getId() { 
   return id; 
}
string Company::getName() {
   return name; 
}
Flights* Company::getFlights() {
   return flights; 
}