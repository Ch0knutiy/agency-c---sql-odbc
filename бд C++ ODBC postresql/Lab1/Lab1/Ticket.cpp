#include "Ticket.h"

Ticket::Ticket() {
	id = 0;
	seat = 0;
	flights = NULL;
	client = NULL;
}

Ticket::Ticket(long id, int seat, Flights* flights, Client* client) {
	this->id = id;
	this->seat = seat;
	this->flights = flights;
	this->client = client;
}

Ticket::Ticket(const Ticket& other) {
	id = other.id;
	seat = other.seat;
	flights = other.flights;
	client = other.client;
}

Ticket::~Ticket() {}

Ticket& Ticket::operator = (Ticket other)
{
	this->id = other.getId();
	this->seat = other.getSeat();
	this->flights = other.getFlights();
	this->client = other.getClient();
	return *this;
}


void Ticket::setId(int id) {
	this->id = id;
}

void Ticket::setSeat(int seat) {
	this->seat = seat;
}

void Ticket::setFlights(Flights* flights) {
	this->flights = flights;
}

void Ticket::setClient(Client* client) {
	this->client = client;
}


int Ticket::getId() {
	return id;
}

int Ticket::getSeat() {
	return seat;
}


Flights* Ticket::getFlights() {
	return flights;
}

Client* Ticket::getClient() {
	return client;
}