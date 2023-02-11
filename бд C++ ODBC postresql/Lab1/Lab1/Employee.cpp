#include "Employee.h"


Employee::Employee() : transfer_num(0) {
	id = 0;
	surname = "";
	name = "";
	patronymic = "";
	address = "";
	birth = "";
	post = "";
	salary = 0;
	phone = "";
	hasRow = 0;
}

Employee::Employee(long id, string surname, string name, string patronymic, string address, string birth, string post, int salary, Transfer* transfer_num, string phone, bool hasRow) {
	this->id = id;
	this->surname = surname;
	this->name = name;
	this->patronymic = patronymic;
	this->address = address;
	this->birth = birth;
	this->post = post;
	this->salary = salary;
	this->transfer_num = transfer_num;
	this->phone = phone;
	this->hasRow = hasRow;
}
Employee::Employee(const Employee& other) {
	this->id = other.id;
	this->surname = other.surname;
	this->name = other.name;
	this->patronymic = other.patronymic;
	this->address = other.address;
	this->birth = other.birth;
	this->post = other.post;
	this->salary = other.salary;
	this->transfer_num = other.transfer_num;
	this->phone = other.phone;
	this->hasRow = other.hasRow;
}
Employee::~Employee() {}

Employee& Employee::operator = (Employee other) {
	this->id = other.getId();
	this->surname = other.getSurname();
	this->name = other.getName();
	this->patronymic = other.getPatronymic();
	this->address = other.getAddress();
	this->birth = other.getBirth();
	this->post = other.getPost();
	this->salary = other.getSalary();
	this->transfer_num = other.getTransferNum();
	this->phone = other.getPhone();
	this->hasRow = other.getHasRow();
	return *this;
}

void Employee::setId(int id) {
	this->id = id;
}
void Employee::setSurname(string surname){
	this->surname = surname;
}
void Employee::setName(string name){
	this->name = name;
}
void Employee::setPatronymic(string patronymic){
	this->patronymic = patronymic;
}
void Employee::setAddress(string address){
	this->address = address;
}
void Employee::setBirth(string birth){
	this->birth = birth;
}
void Employee::setPost(string post){
	this->post = post;
}
void Employee::setSalary(int salary){
	this->salary = salary;
}
void Employee::setTransferNum(Transfer* transfer_num){
	this->transfer_num = transfer_num;
}
void Employee::setPhone(string phone){
	this->phone = phone;
}
void Employee::setHasRow(bool hasRow){
	this->hasRow = hasRow;
}

int Employee::getId(){
	return id;
}
string Employee::getSurname(){
	return surname;
}
string Employee::getName(){
	return name;
}
string Employee::getPatronymic(){
	return patronymic;
}
string Employee::getAddress(){
	return address;
}
string Employee::getBirth(){
	return birth;
}
string Employee::getPost(){
	return post;
}
int Employee::getSalary(){
	return salary;
}
Transfer* Employee::getTransferNum(){
	return transfer_num;
}
string Employee::getPhone(){
	return phone;
}
bool Employee::getHasRow(){
	return hasRow;
}