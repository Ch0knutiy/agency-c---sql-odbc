#include "Transfer.h"

Transfer::Transfer() {
	id = 0;
	num = 0;
	post = "";
	reason = "";
	date = "";
}

Transfer::Transfer(long id, long num, string post, string reason, string date) {
	this->id = id;
	this->num = num;
	this->post = post;
	this->reason = reason;
	this->date = date;
}

Transfer::Transfer(const Transfer& other) {
	id = other.id;
	num = other.num;
	post = other.post;
	reason = other.reason;
	date = other.date;
}

Transfer::~Transfer() {}

Transfer& Transfer::operator = (Transfer other)
{
	this->id = other.getId();
	this->num = other.getNum();
	this->post = other.getPost();
	this->reason = other.getReason();
	this->date = other.date;
	return *this;
}


void Transfer::setId(long id) {
	this->id = id;
}

void Transfer::setNum(long num) {
	this->num = num;
}

void Transfer::setPost(string post) {
	this->post = post;
}

void Transfer::setReason(string reason) {
	this->reason = reason;;
}


void Transfer::setDate(string date) {
	this->date = date;;
}

int Transfer::getId() {
	return id;
}

long Transfer::getNum() {
	return num;
}


string Transfer::getPost() {
	return post;
}

string Transfer::getReason() {
	return reason;
}

string Transfer::getDate() {
	return date;
}