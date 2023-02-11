#include "City.h"

City::City() {
   id = 0;
   city = "";
   country = NULL;
}
City::City(long id, string city, Country* country) {
   this->id = id;
   this->city = city;
   this->country = country;
}
City::City(const City& other) {
   id = other.id;
   city = other.city;
   country = other.country;
}

City::~City() {}

City& City::operator = (City other) {
   this->id = other.getId();
   this->city = other.getCity();
   this->country = other.getCountry();
   return *this;
}

void City::setId(long id) {
   this->id = id;
}
void City::setCity(string city) {
   this->city = city;
}
void City::setCountry(Country* country) {
   this->country = country;
}

int City::getId() {
   return id;
}
string City::getCity() {
   return city;
}
Country* City::getCountry() {
   return country;
}