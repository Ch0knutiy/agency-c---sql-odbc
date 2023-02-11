#include "Client.h"

Client::Client() {
	id = 0;
	surname = "";
	name = "";
	patronymic = "";
	phone = "";
	date_of_buy = "";
	time_of_buy = "";
	route = NULL;
}
Client::Client(long id, string surname, string name, string patronymic, string phone, string date_of_buy, string time_of_buy, Route* route) {
	this->id = id;
	this->surname = surname;
	this->name = name;
	this->patronymic = patronymic;
	this->phone = phone;
	this->date_of_buy = date_of_buy;
	this->time_of_buy = time_of_buy;
	this->route = route;
}
Client::Client(const Client& other) {
	this->id = other.id;
	this->surname = other.surname;
	this->name = other.name;
	this->patronymic = other.patronymic;
	this->phone = other.phone;
	this->date_of_buy = other.date_of_buy;
	this->time_of_buy = other.time_of_buy;
	this->route = other.route;
}

Client::~Client() {}

Client& Client::operator = (Client other) {
	this->id = other.getId();
	this->surname = other.getSurname();
	this->name = other.getName();
	this->patronymic = other.getPatronymic();
	this->phone = other.getPhone();
	this->date_of_buy = other.getDate();
	this->time_of_buy = other.getTime();
	this->route = other.getRoute();;
	return *this;
}

void Client::setId(int id) {
	this->id = id;
}
void Client::setSurname(string surname){
	this->surname = surname;
	}
void Client::setName(string name){
	this->name = name;
	}
void Client::setPatronymic(string patronymic){
	this->patronymic = patronymic;
	}
void Client::setPhone(string phone){
	this->phone = phone;
	}
void Client::setDate(string date){
	this->date_of_buy = date;
	}
void Client::setTime(string time){
	this->time_of_buy = time;
	}
void Client::setRoute(Route* route){
	this->route = route;
	}

int Client::getId(){
	return id;
	}
string Client::getSurname(){
	return surname;
	}
string Client::getName(){
	return name;
	}
string Client::getPatronymic(){
	return patronymic;
	}
string Client::getPhone(){
	return phone;
	}
string Client::getDate(){
	return date_of_buy;
	}
string Client::getTime(){
	return time_of_buy;
	}
Route* Client::getRoute(){
	return route;
	}