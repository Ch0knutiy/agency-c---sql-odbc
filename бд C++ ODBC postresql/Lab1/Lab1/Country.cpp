#include "Country.h"

Country::Country() {
   id = 0;
   country = "";
}
Country::Country(long id, string country) {
   this->id = id;
   this->country = country;
}
Country::Country(const Country& other) {
   this->id = other.id;
   this->country = other.country;
}

Country::~Country() {}

Country& Country::operator = (Country other) {
   this->id = other.getId();
   this->country = other.getCountry();
   return *this;
}

void Country::setId(int id) {
   this->id = id;
}
void Country::setCountry(string country) {
   this->country = country;
}

int Country::getId() {
   return id;
}
string Country::getCountry() {
   return country;
}