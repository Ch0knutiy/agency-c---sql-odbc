#include "Flights.h"

Flights::Flights() {
	num = "";
	date = "";
	time = "";
	aircraft = "";
	_class = "";
	free = 0;
}

Flights::Flights(string num, string date, string time, string aircraft, string _class, int free) {
	this->num = num;
	this->date = date;
	this->time = time;
	this->aircraft = aircraft;
	this->_class = _class;
	this->free = free;
}

Flights::Flights(const Flights& other) {
	num = other.num;
	date = other.date;
	time = other.time;
	aircraft = other.aircraft;
	_class = other._class;
	free = other.free;
}

Flights::~Flights() {}

Flights& Flights::operator = (Flights other)
{
	this->num = other.getNum();
	this->date = other.getDate();
	this->time = other.getTime();
	this->aircraft = other.getAircraft();
	this->_class = other.getClass();
	this->free = other.getFree();
	return *this;
}


void Flights::setNum(string num) {
	this->num = num;
}
void Flights::setDate(string date){
	this->date = date;
}
void Flights::setTime(string time){
	this->time = time;
}
void Flights::setAircraft(string aircraft){
	this->aircraft = aircraft;
}
void Flights::setClass(string _class){
	this->_class = _class;
}
void Flights::setFree(int free){
	this->free = free;
}


string Flights::getNum() {
	return num;
}
string Flights::getDate(){
	return date;
}
string Flights::getTime(){
	return time;
}
string Flights::getAircraft(){
	return aircraft;
}

string Flights::getClass(){
	return _class;
}
int Flights::getFree(){
	return free;
}