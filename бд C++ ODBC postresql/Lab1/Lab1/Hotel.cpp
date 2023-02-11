#include "Hotel.h"

Hotel::Hotel() {
	id = 0;
	name = "";
	_class = 0;
	categories = "";
}

Hotel::Hotel(long id, string name, int _class, string categories) {
	this->id = id;
	this->name = name;
	this->_class = _class;
	this->categories = categories;
}

Hotel::Hotel(const Hotel& other) {
	id = other.id;
	name = other.name;
	_class = other._class;
	categories = other.categories;
}

Hotel::~Hotel() {}

Hotel& Hotel::operator = (Hotel other)
{
	this->id = other.getId();
	this->name = other.getName();
	this->_class = other.getClass();
	this->categories = other.getCategories();
	return *this;
}


void Hotel::setId(int id) {
	this->id = id;
}
void Hotel::setName(string name){
	this->name = name;
}
void Hotel::setClass(int _class){
	this->_class = _class;
}
void Hotel::setCategories(string categories){
	this->categories = categories;
}

int Hotel::getId() {
	return id;
}
string Hotel::getName(){
	return name;
}
int Hotel::getClass(){
	return _class;
}
string Hotel::getCategories(){
	return categories;
}