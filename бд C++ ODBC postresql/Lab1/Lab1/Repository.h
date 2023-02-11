#pragma once
#include <iostream>
#include <map>
#include "Ticket.h"

using namespace std;

class Repository
{
private:
	Repository();
	map <long, City> city;
	map <long, Client> client;
	map <long, Company> company;
	map <long, Country> country;
	map <long, Employee> employee;
	map <long, Flights> flights;
	map <long, Hotel> hotel;
	map <long, Route> route;
	map <long, Ticket> ticket;
	map <long, Transfer> transfer;
	static Repository* instance;


public:
	Repository(Repository& other) = delete;//
	void operator=(const Repository& other) = delete;//

	static Repository* getInstance();//

	int setCity(City city);//
	int setClient(Client client);//
	int setCompany(Company company);//
	int setCountry (Country country);//
	int setEmployee(Employee employee);//
	int setFlights(Flights flights);//
	int setHotel(Hotel hotel);//
	int setRoute(Route route);//
	int setTicket(Ticket ticket);//
	int setTransfer(Transfer transfer);//

	City* getCity(long city_key);//
	Client* getClient(long client_key);//
	Company* getCompany(long comp_key);//
	Country* getCountry(long coun_key);//
	Employee* getEmployee(long empl_key);//
	Flights* getFlights(long flights_key);//
	Hotel* getHotel(long hotel_key);//
	Route* getRoutey(long route_key);//
	Ticket* getTicket(long ticket_key);//
	Transfer* getTransfer(long trans_key);//

	map<long, City>* getCityMap();//
	map<long, Client>* getClientMap();//
	map<long, Company>* getCompMap();//
	map<long, Country>* getCounMap();//
	map<long, Employee>* getEmplMap();//
	map<long, Flights>* getFlightsMap();//
	map<long, Hotel>* getHotelMap();//
	map<long, Route>* getRouteMap();//
	map<long, Ticket>* getTicketMap();//
	map<long, Transfer>* getTransfMap();//

	void deleteCity(long city_key, City& obj);//
	void deleteClient(long client_key, Client& obj);//
	void deleteCompany(long comp_key, Company& obj);//
	void deleteCountry(long coun_key, Country& obj);//
	void deleteEmployee(long empl_key, Employee& obj);//
	void deleteFlights(long flights_key, Flights& obj);//
	void deleteHotel(long hotel_key, Hotel& obj);//
	void deleteRoute(long route_key ,Route& obj);//
	void deleteTicket(long ticket_key, Ticket& obj);//
	void deleteTransfer(long trans_key, Transfer& obj);//
};
