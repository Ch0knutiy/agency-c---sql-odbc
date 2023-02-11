#include "Repository.h"

Repository* Repository::instance;

Repository::Repository() : city(), client(), company(), country(), employee(), flights(), hotel(), route(), ticket(), transfer() {}

Repository* Repository::getInstance()
{
	if (instance == nullptr) {
		instance = new Repository();
	}
	return instance;
}

////////////////////////////////////////////////////////////////////

int Repository::setCity(City city)
{
	long max = 0;
	for (auto it = this->city.begin(); it != this->city.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == city.getId()) {
			it->second = city;
			return 1;
		}
	}
	this->city[++max] = city;
	return 0;
}
int Repository::setClient(Client client) {
	long max = 0;
	for (auto it = this->client.begin(); it != this->client.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == client.getId()) {
			it->second = client;
			return 1;
		}
	}
	this->client[++max] = client;
	return 0;
}
int Repository::setCompany(Company company) {
	long max = 0;
	for (auto it = this->company.begin(); it != this->company.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == company.getId()) {
			it->second = company;
			return 1;
		}
	}
	this->company[++max] = company;
	return 0;
}
int Repository::setCountry(Country country) {
	long max = 0;
	for (auto it = this->country.begin(); it != this->country.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == country.getId()) {
			it->second = country;
			return 1;
		}
	}
	this->country[++max] = country;
	return 0;
}
int Repository::setEmployee(Employee employee) {
	long max = 0;
	for (auto it = this->employee.begin(); it != this->employee.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == employee.getId()) {
			it->second = employee;
			return 1;
		}
	}
	this->employee[++max] = employee;
	return 0;
}
int Repository::setFlights(Flights flights) {
	long max = 0;
	for (auto it = this->flights.begin(); it != this->flights.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getNum() == flights.getNum()) {
			it->second = flights;
			return 1;
		}
	}
	this->flights[++max] = flights;
	return 0;
}
int Repository::setHotel(Hotel hotel) {
	long max = 0;
	for (auto it = this->hotel.begin(); it != this->hotel.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == hotel.getId()) {
			it->second = hotel;
			return 1;
		}
	}
	this->hotel[++max] = hotel;
	return 0;
}
int Repository::setRoute(Route route) {
	long max = 0;
	for (auto it = this->route.begin(); it != this->route.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == route.getId()) {
			it->second = route;
			return 1;
		}
	}
	this->route[++max] = route;
	return 0;
}
int Repository::setTicket(Ticket ticket) {
	long max = 0;
	for (auto it = this->ticket.begin(); it != this->ticket.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == ticket.getId()) {
			it->second = ticket;
			return 1;
		}
	}
	this->ticket[++max] = ticket;
	return 0;
}
int Repository::setTransfer(Transfer transfer) {
	long max = 0;
	for (auto it = this->transfer.begin(); it != this->transfer.end(); it++)
	{
		if (max < it->first)
			max = it->first;
		if (it->second.getId() == transfer.getId()) {
			it->second = transfer;
			return 1;
		}
	}
	this->transfer[++max] = transfer;
	return 0;
}

//////////////////////////////////////////////////////////

City* Repository::getCity(long city_key)
{
	auto it = this->city.find(city_key);
	if (it == city.end())
		return nullptr;
	return &(it->second);
}
Client* Repository::getClient(long client_key) {
	auto it = this->client.find(client_key);
	if (it == client.end())
		return nullptr;
	return &(it->second);
}
Company* Repository::getCompany(long comp_key) {
	auto it = this->company.find(comp_key);
	if (it == company.end())
		return nullptr;
	return &(it->second);
}
Country* Repository::getCountry(long coun_key) {
	auto it = this->country.find(coun_key);
	if (it == country.end())
		return nullptr;
	return &(it->second);
}
Employee* Repository::getEmployee(long empl_key) {
	auto it = this->employee.find(empl_key);
	if (it == employee.end())
		return nullptr;
	return &(it->second);
}
Flights* Repository::getFlights(long flights_key) {
	auto it = this->flights.find(flights_key);
	if (it == flights.end())
		return nullptr;
	return &(it->second);
}
Hotel* Repository::getHotel(long hotel_key) {
	auto it = this->hotel.find(hotel_key);
	if (it == hotel.end())
		return nullptr;
	return &(it->second);
}
Route* Repository::getRoutey(long route_key) {
	auto it = this->route.find(route_key);
	if (it == route.end())
		return nullptr;
	return &(it->second);
}
Ticket* Repository::getTicket(long ticket_key) {
	auto it = this->ticket.find(ticket_key);
	if (it == ticket.end())
		return nullptr;
	return &(it->second);
}
Transfer* Repository::getTransfer(long trans_key) {
	auto it = this->transfer.find(trans_key);
	if (it == transfer.end())
		return nullptr;
	return &(it->second);
}
//////////////////////////////////////////////////////////////

map<long, City>* Repository::getCityMap() {
	return &city;
}
map<long, Client>* Repository::getClientMap() {
	return &client;
}
map<long, Company>* Repository::getCompMap() {
	return &company;
}
map<long, Country>* Repository::getCounMap() {
	return &country;
}
map<long, Employee>* Repository::getEmplMap() {
	return &employee;
}
map<long, Flights>* Repository::getFlightsMap() {
	return &flights;
}
map<long, Hotel>* Repository::getHotelMap() {
	return &hotel;
}
map<long, Route>* Repository::getRouteMap() {
	return &route;
}
map<long, Ticket>* Repository::getTicketMap() {
	return &ticket;
}
map<long, Transfer>* Repository::getTransfMap() {
	return &transfer;
}

///////////////////////////////////////////////////////////////////////

void Repository::deleteCity(long city_key, City& obj) {
	for (auto it = this->route.begin(); it != this->route.end(); it++) {
		if (it->second.getCity()->getId() == obj.getId())
			deleteRoute(it->first, it->second);
	}
	city.erase(city_key);
}
void Repository::deleteRoute(long route_key, Route& obj) {
	for (auto it = this->client.begin(); it != this->client.end(); it++) {
		if (it->second.getRoute()->getId() == obj.getId())
			deleteClient(it->first, it->second);
	}
	route.erase(route_key);
}
void Repository::deleteClient(long client_key, Client& obj) {
	for (auto it = this->ticket.begin(); it != this->ticket.end(); it++) {
		if (it->second.getClient()->getId() == obj.getId())
			deleteTicket(it->first, it->second);
	}
	client.erase(client_key);
}
void Repository::deleteCompany(long comp_key, Company& obj) {
	for (auto it = this->route.begin(); it != this->route.end(); it++) {
		if (it->second.getCompany()->getId() == obj.getId())
			deleteRoute(it->first, it->second);
	}
	company.erase(comp_key);
}
void Repository::deleteCountry(long coun_key, Country& obj) {
	for (auto it = this->city.begin(); it != this->city.end(); it++) {
		if (it->second.getCountry()->getId() == obj.getId())
			deleteCity(it->first, it->second);
	}
	country.erase(coun_key);
}
void Repository::deleteEmployee(long empl_key, Employee& obj) {
	for (auto it = this->route.begin(); it != this->route.end(); it++) {
		if (it->second.getEmployee()->getId() == obj.getId())
			deleteRoute(it->first, it->second);
	}
	employee.erase(empl_key);
}
void Repository::deleteFlights(long flights_key, Flights& obj) {
	for (auto it = this->company.begin(); it != this->company.end(); it++) {
		if (it->second.getFlights()->getNum() == obj.getNum())
			deleteCompany(it->first, it->second);
	}
	for (auto it = this->ticket.begin(); it != this->ticket.end(); it++) {
		if (it->second.getFlights()->getNum() == obj.getNum())
			deleteTicket(it->first, it->second);
	}
	flights.erase(flights_key);
}
void Repository::deleteHotel(long hotel_key, Hotel& obj) {
	for (auto it = this->route.begin(); it != this->route.end(); it++) {
		if (it->second.getHotel()->getId() == obj.getId())
			deleteRoute(it->first, it->second);
	}
	hotel.erase(hotel_key);
}
void Repository::deleteTicket(long ticket_key, Ticket& obj) {
	ticket.erase(ticket_key);
}
void Repository::deleteTransfer(long trans_key, Transfer& obj) {
	for (auto it = this->employee.begin(); it != this->employee.end(); it++) {
		if (it->second.getTransferNum()->getId() == obj.getId())
			it->second.setTransferNum(nullptr);
	}
	transfer.erase(trans_key);
}