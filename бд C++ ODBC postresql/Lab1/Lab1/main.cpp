#include <iostream>
#include <utility>
#include <Windows.h>
#include "CityMapper.h"
#include "ClientMapper.h"
#include "CompanyMapper.h"
#include "CountryMapper.h"
#include "EmployeeMapper.h"
#include "FlightsMapper.h"
#include "HotelMapper.h"
#include "RouteMapper.h"
#include "TicketMapper.h"
#include "TransferMapper.h"
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

void city_out(long city_key, City city) {
      setiosflags(ios::left);
      cout << left  << setw(7) << city_key << left << setw(17) << city.getCity() << setw(15) << left << city.getCountry()->getCountry() << endl;
   }
void cities_out() {
      map<long, City> cities = *(Repository::getInstance()->getCityMap());
      cout << endl;
      cout << left << setw(7) << "[No]" << left << setw(17) << "City" << setw(15) <<left << "Country" << endl;
      for (auto it = cities.begin(); it != cities.end(); it++) {
         city_out(it->first, it->second);
      }
      cout << endl;
   }

void client_out(long client_key, Client client) {
    cout << left << setw(7) << client_key << left << setw(15) << client.getSurname() << left << setw(13) << client.getName() << left << setw(15)<< client.getPatronymic() << left << setw(18) << client.getPhone() << left << setw(15) << client.getDate() << left << setw(15) << client.getTime() << left << setw(19) << client.getRoute()->getName() << endl;
}
void clients_out() {

    map<long, Client> cities = *(Repository::getInstance()->getClientMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << left << setw(15) << "Surname" << left << setw(13) << "Name" << left << setw(15) << "Patronymic" << left << setw(18) << "Phone" << left << setw(15) << "Date_of_buy" << left << setw(15) << "Time_of_buy" << left << setw(15) << "Route" << endl;
    for (auto it = cities.begin(); it != cities.end(); it++) {
        client_out(it->first, it->second);
    }
    cout << endl;
}

void company_out(long company_key, Company company) {
    cout << left << setw(7) << company_key << left << setw(20) << company.getName() << setw(13) << left << company.getFlights()->getNum() << endl;
}
void companies_out() {
    map<long, Company> company = *(Repository::getInstance()->getCompMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << left << setw(20) << "Company_name" << setw(13) << left << "Flights" << endl;
    for (auto it = company.begin(); it != company.end(); it++) {
        company_out(it->first, it->second);
    }
    cout << endl;
}

void country_out(long country_key, Country country) {
    cout << left << setw(7) << country_key << left << setw(10) << country.getCountry() << endl;
}
void countries_out() {
    map<long, Country> country = *(Repository::getInstance()->getCounMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << setw(10) << left << "Country" << endl;
    for (auto it = country.begin(); it != country.end(); it++) {
        country_out(it->first, it->second);
    }
    cout << endl;
}

void employee_out(long employee_key, Employee employee) {
    cout << left << setw(7) << employee_key << left << setw(15) << employee.getSurname() << left << setw(13) << employee.getName() << left << setw(15) << employee.getPatronymic() << left << setw(18)<< employee.getAddress() << left << setw(15) << employee.getBirth() << left << setw(15) << employee.getPost() << left << setw(10) << employee.getSalary() << left << setw(12) << employee.getTransferNum() << left << setw(15) << employee.getPhone() << endl;
}
void employees_out() {
    map<long, Employee> employee = *(Repository::getInstance()->getEmplMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << left << setw(15) << "Surname" << left << setw(13) << "Name" << left << setw(15) << "Patronymic" << left << setw(18) << "Address" << left << setw(15) << "Birth" << left << setw(15) << "Post" << left << setw(10) << "Salary" << left << setw(12) << "Transfer" << left << setw(15) << "Phone" << endl;

    for (auto it = employee.begin(); it != employee.end(); it++) {
        employee_out(it->first, it->second);
    }
    cout << endl;
}

void flight_out(long flights_key, Flights flights) {
    cout << left << setw(7) << flights_key << left << setw(15) << flights.getNum() << left << setw(15) << flights.getDate() << left << setw(15) << flights.getTime() << left << setw(15) << flights.getAircraft() << left << setw(7) << flights.getClass() << left << setw(5) << flights.getFree() << endl;
}
void flights_out() {
    map<long, Flights> flights = *(Repository::getInstance()->getFlightsMap());
    cout << endl;
    cout << left << setw(7) << "[No]"<< left << setw(15) << "Num of flights" << left << setw(15) << "Date" << left << setw(15) << "Time" << left << setw(15) << "Aircraft" << left << setw(7) << "Class" << left << setw(5) << "Free_seats" << endl;
    for (auto it = flights.begin(); it != flights.end(); it++) {
        flight_out(it->first, it->second);
    }
    cout << endl;
}

void hotel_out(long hotel_key, Hotel hotel) {
    cout << left << setw(7) << hotel_key << left << setw(20) << hotel.getName() << left << setw(7) << hotel.getClass() << left << setw(7) << hotel.getCategories() << endl;
}
void hotels_out() {
    map<long, Hotel> hotel = *(Repository::getInstance()->getHotelMap());
    cout << endl;
    cout << left << setw(7) << "[No]"<< left << setw(20) << "Name"<< left << setw(7) <<  "Class" << left << setw(7) <<  "Categories" << endl;
    for (auto it = hotel.begin(); it != hotel.end(); it++) {
        hotel_out(it->first, it->second);
    }
    cout << endl;
}

void route_out(long route_key, Route route) {
    cout << left << setw(7) << route_key << left << setw(15) << route.getName() << left << setw(19) << route.getCity()->getCity() << left << setw(15) << route.getDuration() << left << setw(20) << route.getHotel()->getName() << left << setw(15) << route.getCompany()->getName() << left << setw(15) << route.getEmployee()->getSurname() << endl;
}
void routes_out() {
    map<long, Route> route = *(Repository::getInstance()->getRouteMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << left << setw(15) << "Name" << left << setw(19) << "City" << left << setw(15) << "Duration" << left << setw(20) << "Hotel" << left << setw(15) << "Company" << left << setw(15) << "Employee" << endl;
    for (auto it = route.begin(); it != route.end(); it++) {
        route_out(it->first, it->second);
    }
    cout << endl;
}

void ticket_out(long ticket_key, Ticket ticket) {
    cout << left << setw(7) << ticket_key << left << setw(5) << ticket.getSeat() << left << setw(15) << ticket.getFlights()->getNum() << left << setw(15) << ticket.getClient()->getSurname() << endl;
}
void tickets_out() {
    map<long, Ticket> ticket = *(Repository::getInstance()->getTicketMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << left << setw(5) << "Seat" << left << setw(15) << "Flights" << left << setw(15) << "Client" << endl;
    for (auto it = ticket.begin(); it != ticket.end(); it++) {
        ticket_out(it->first, it->second);
    }
    cout << endl;
}

void transfer_out(long transfer_key, Transfer transfer) {
    cout << left << setw(7) << transfer_key << left << setw(12) << transfer.getNum() << left << setw(15) << transfer.getPost() << left << setw(40) << transfer.getReason() << left << setw(12) << transfer.getDate() << endl;
}
void transfers_out() {
    map<long, Transfer> transfer = *(Repository::getInstance()->getTransfMap());
    cout << endl;
    cout << left << setw(7) << "[No]" << left << setw(12) << "Number" << left << setw(15) << "Post" << left << setw(40) << "Reason" << left << setw(12) << "Date" << endl;
    for (auto it = transfer.begin(); it != transfer.end(); it++) {
        transfer_out(it->first, it->second);
    }
    cout << endl;
}

void menu() {
    cout << "[1] City" << endl;
    cout << "[2] Client" << endl;
    cout << "[3] Company" << endl;
    cout << "[4] Country" << endl;
    cout << "[5] Employee" << endl;
    cout << "[6] Flights" << endl;
    cout << "[7] Hotel" << endl;
    cout << "[8] Route" << endl;
    cout << "[9] Ticket" << endl;
    cout << "[10] Transfer" << endl;
    cout << "[11] Exit" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    DataBase db;

    CityMapper cityMap(db);
    ClientMapper clientMap(db);
    CompanyMapper companyMap(db);
    CountryMapper countryMap(db);
    EmployeeMapper employeeMap(db);
    FlightsMapper flightsMap(db);
    HotelMapper hotelMap(db);
    RouteMapper routeMap(db);
    TicketMapper ticketMap(db);
    TransferMapper transferMap(db);
    Repository* instanse = Repository::getInstance();

    bool exit = false;
    while (!exit) {
        menu();
        string tmp = "";
        string choice;
        cin >> choice;
        switch (atoi(choice.c_str())) {
        case 1: {
            string city_menu;
            bool city_exit = false;
            countryMap.findAllInfo();
            cityMap.findAllInfo();
            cities_out();
            while (!city_exit) {
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> city_menu;
                switch (atoi(city_menu.c_str())) {
                case 1: {
                    City city;
                    cout << "Enter the city: ";
                    cin >> tmp;
                    city.setCity(tmp);
                    cout << "\nChoise the country: " << endl;
                    countries_out();
                    cin >> tmp;
                    city.setCountry(instanse->getCountry(atoi(tmp.c_str())));
                    cityMap.save(city);
                    cities_out();
                    break;
                }
                case 2: {
                    City city;
                    cout << "Choise [No] of city: ";
                    cin >> tmp;
                    city.setId(instanse->getCity(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter City: ";
                    cin >> tmp;
                    city.setCity(tmp);
                    cout << "\nChoise the country: " << endl;
                    countries_out();
                    cin >> tmp;
                    city.setCountry(instanse->getCountry(atoi(tmp.c_str())));
                    cityMap.save(city);
                    cities_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of city: ";
                    cin >> tmp;
                    cityMap.del(*instanse->getCity(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    cities_out();
                    break;
                }
                case 4: {
                    city_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 2: {
            bool client_exit = false;
            countryMap.findAllInfo();
            cityMap.findAllInfo();
            hotelMap.findAllInfo();
            flightsMap.findAllInfo();
            companyMap.findAllInfo();
            transferMap.findAllInfo();
            employeeMap.findAllInfo();
            routeMap.findAllInfo();
            clientMap.findAllInfo();
            clients_out();
            while (!client_exit) {
                string client_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> client_menu;
                switch (atoi(client_menu.c_str())) {
                case 1: {
                    Client client;
                    cout << "\nEnter surname name patronymic: ";
                    cin >> tmp;
                    client.setSurname(tmp);
                    cin >> tmp;
                    client.setName(tmp);
                    cin >> tmp;
                    client.setPatronymic(tmp);
                    cout << "\nEnter phone: ";
                    cin >> tmp;
                    client.setPhone(tmp);
                    cout << "\nEnter date_of_buy time_of_buy: ";
                    cin >> tmp;
                    client.setDate(tmp);
                    cin >> tmp;
                    client.setTime(tmp);
                    cout << "\nChoise the route: " << endl;
                    routes_out();
                    cin >> tmp;
                    client.setRoute(instanse->getRoutey(atoi(tmp.c_str())));
                    clientMap.save(client);
                    clients_out();
                    break;
                }
                case 2: {
                    Client client;
                    cout << "Choise [No] of client: ";
                    cin >> tmp;
                    client.setId(instanse->getClient(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter surname name patronymic: ";
                    cin >> tmp;
                    client.setSurname(tmp);
                    cin >> tmp;
                    client.setName(tmp);
                    cin >> tmp;
                    client.setPatronymic(tmp);
                    cout << "\nEnter phone: ";
                    cin >> tmp;
                    client.setPhone(tmp);
                    cout << "\nEnter date_of_buy time_of_buy: ";
                    cin >> tmp;
                    client.setDate(tmp);
                    cin >> tmp;
                    client.setTime(tmp);
                    cout << "\nChoise the route: " << endl;
                    routes_out();
                    cin >> tmp;
                    client.setRoute(instanse->getRoutey(atoi(tmp.c_str())));
                    clientMap.save(client);
                    clients_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of client: ";
                    cin >> tmp;
                    clientMap.del(*instanse->getClient(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    clients_out();
                    break;
                }
                case 4: {
                    client_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 3: {
            bool company_exit = false;
            flightsMap.findAllInfo();
            companyMap.findAllInfo();
            companies_out();
            while (!company_exit) {
                string company_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> company_menu;
                switch (atoi(company_menu.c_str())) {
                case 1: {
                    Company company;
                    cout << "\nEnter name of company: ";
                    cin >> tmp;
                    company.setName(tmp);
                    cout << "\nChoise the flight: " << endl;
                    flights_out();
                    cin >> tmp;
                    company.setFlights(instanse->getFlights(atoi(tmp.c_str())));
                    companyMap.save(company);
                    companies_out();
                    break;
                }
                case 2: {
                    Company company;
                    cout << "Choise [No] of company: ";
                    cin >> tmp;
                    company.setId(instanse->getCompany(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter name of company: ";
                    cin >> tmp;
                    company.setName(tmp);
                    cout << "\nChoise the flight: " << endl;
                    flights_out();
                    cin >> tmp;
                    company.setFlights(instanse->getFlights(atoi(tmp.c_str())));
                    companyMap.save(company);
                    companies_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of company: ";
                    cin >> tmp;
                    companyMap.del(*instanse->getCompany(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    companies_out();
                    break;
                }
                case 4: {
                    company_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 4: {
            bool country_exit = false;
            countryMap.findAllInfo();
            countries_out();
            while (!country_exit) {
                string country_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> country_menu;
                switch (atoi(country_menu.c_str())) {
                case 1: {
                    Country country;
                    cout << "\nEnter country: ";
                    cin >> tmp;
                    country.setCountry(tmp);
                    countryMap.save(country);
                    countries_out();
                    break;
                }
                case 2: {
                    Country country;
                    cout << "Choise [No] of country: ";
                    cin >> tmp;
                    country.setId(instanse->getCountry(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter country: ";
                    cin >> tmp;
                    country.setCountry(tmp);
                    countryMap.save(country);
                    countries_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of country: ";
                    cin >> tmp;
                    countryMap.del(*instanse->getCountry(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    countries_out();
                    break;
                }
                case 4: {
                    country_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 5: {
            bool employee_exit = false;
            transferMap.findAllInfo();
            employeeMap.findAllInfo();
            employees_out();
            while (!employee_exit) {
                string employee_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> employee_menu;
                switch (atoi(employee_menu.c_str())) {
                case 1: {
                    Employee employee;
                    cout << "\nEnter surname name patronymic: ";
                    cin >> tmp;
                    employee.setSurname(tmp);
                    cin >> tmp;
                    employee.setName(tmp);
                    cin >> tmp;
                    employee.setPatronymic(tmp);
                    cout << "\nEnter Address: ";
                    cin >> tmp;
                    employee.setAddress(tmp);
                    cout << "\nEnter date of birth: ";
                    cin >> tmp;
                    employee.setBirth(tmp);
                    cout << "\nEnter post: ";
                    cin >> tmp;
                    employee.setPost(tmp);
                    cout << "\nEnter phone: ";
                    cin >> tmp;
                    employee.setPhone(tmp);
                    cout << "\nEnter salary: ";
                    cin >> tmp;
                    employee.setSalary(atoi(tmp.c_str()));
                    cout << "\nChoise the transfer num: " << endl;
                    transfers_out();
                    cin >> tmp;
                    employee.setTransferNum(instanse->getTransfer(atoi(tmp.c_str())));
                    employeeMap.save(employee);
                    employees_out();
                    break;
                }
                case 2: {
                    Employee employee;
                    cout << "Choise [No] of employee: ";
                    cin >> tmp;
                    employee.setId(instanse->getEmployee(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter surname name patronymic: ";
                    cin >> tmp;
                    employee.setSurname(tmp);
                    cin >> tmp;
                    employee.setName(tmp);
                    cin >> tmp;
                    employee.setPatronymic(tmp);
                    cout << "\nEnter Address: ";
                    cin >> tmp;
                    employee.setAddress(tmp);
                    cout << "\nEnter date of birth: ";
                    cin >> tmp;
                    employee.setBirth(tmp);
                    cout << "\nEnter post: ";
                    cin >> tmp;
                    employee.setPost(tmp);
                    cout << "\nEnter phone: ";
                    cin >> tmp;
                    employee.setPhone(tmp);
                    cout << "\nEnter salary: ";
                    cin >> tmp;
                    employee.setSalary(atoi(tmp.c_str()));
                    cout << "\nChoise the transfer num: " << endl;
                    transfers_out();
                    cin >> tmp;
                    employee.setTransferNum(instanse->getTransfer(atoi(tmp.c_str())));
                    employeeMap.save(employee);
                    employees_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of employee: ";
                    cin >> tmp;
                    employeeMap.del(*instanse->getEmployee(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    employees_out();
                    break;
                }
                case 4: {
                    employee_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 6: {
            bool flights_exit = false;
            flightsMap.findAllInfo();
            flights_out();
            while (!flights_exit) {
                string flights_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> flights_menu;
                switch (atoi(flights_menu.c_str())) {
                case 1: {
                    Flights flights;
                    cout << "\nEnter num: ";
                    cin >> tmp;
                    flights.setNum(tmp);
                    cout << "\nEnter date: ";
                    cin >> tmp;
                    flights.setDate(tmp);
                    cout << "\nEnter time: ";
                    cin >> tmp;
                    flights.setTime(tmp);
                    cout << "\nEnter aircraft: ";
                    cin >> tmp;
                    flights.setAircraft(tmp);
                    cout << "\nEnter _class: ";
                    cin >> tmp;
                    flights.setClass(tmp);
                    cout << "\nEnter free: ";
                    cin >> tmp;
                    flights.setFree(atoi(tmp.c_str()));
                    flightsMap.save(flights, false);
                    flights_out();
                    break;
                }
                case 2: {
                    Flights flights;
                    cout << "Choise [No] of flight: ";
                    cin >> tmp;
                    flights.setNum(instanse->getFlights(atoi(tmp.c_str()))->getNum());
                    cout << "\nEnter num: ";
                    cin >> tmp;
                    flights.setNum(tmp);
                    cout << "\nEnter date: ";
                    cin >> tmp;
                    flights.setDate(tmp);
                    cout << "\nEnter time: ";
                    cin >> tmp;
                    flights.setTime(tmp);
                    cout << "\nEnter aircraft: ";
                    cin >> tmp;
                    flights.setAircraft(tmp);
                    cout << "\nEnter _class: ";
                    cin >> tmp;
                    flights.setFree(atoi(tmp.c_str()));
                    cout << "\nEnter free: ";
                    cin >> tmp;
                    flights.setNum(tmp);
                    flightsMap.save(flights, true);
                    flights_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of flight: ";
                    cin >> tmp;
                    flightsMap.del(*instanse->getFlights(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    flights_out();
                    break;
                }
                case 4: {
                    flights_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 7: {
            bool hotel_exit = false;
            hotelMap.findAllInfo();
            hotels_out();
            while (!hotel_exit) {
                string hotel_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> hotel_menu;
                switch (atoi(hotel_menu.c_str())) {
                case 1: {
                    Hotel hotel;
                    cout << "\nEnter hotel: ";
                    cin >> tmp;
                    hotel.setName(tmp);
                    cout << "\nEnter _class: ";
                    cin >> tmp;
                    hotel.setClass(atoi(tmp.c_str()));
                    cout << "\nEnter categories: ";
                    cin >> tmp;
                    hotel.setCategories(tmp);
                    hotelMap.save(hotel);
                    hotels_out();
                    break;
                }
                case 2: {
                    Hotel hotel;
                    cout << "Choise [No] of hotel: ";
                    cin >> tmp;
                    hotel.setId(instanse->getHotel(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter hotel: ";
                    cin >> tmp;
                    hotel.setName(tmp);
                    cout << "\nEnter _class: ";
                    cin >> tmp;
                    hotel.setClass(atoi(tmp.c_str()));
                    cout << "\nEnter categories: ";
                    cin >> tmp;
                    hotel.setCategories(tmp);
                    hotelMap.save(hotel);
                    hotels_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of hotel: ";
                    cin >> tmp;
                    hotelMap.del(*instanse->getHotel(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    hotels_out();
                    break;
                }
                case 4: {
                    hotel_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 8: {
            bool route_exit = false;
            countryMap.findAllInfo();
            cityMap.findAllInfo();
            hotelMap.findAllInfo();
            flightsMap.findAllInfo();
            companyMap.findAllInfo();
            transferMap.findAllInfo();
            employeeMap.findAllInfo();
            routeMap.findAllInfo();
            routes_out();
            while (!route_exit) {
                string route_menu;
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> route_menu;
                switch (atoi(route_menu.c_str())) {
                case 1: {
                    Route route;
                    cout << "\nEnter name: ";
                    cin >> tmp;
                    route.setName(tmp);
                    cout << "\nEnter duration: ";
                    cin >> tmp;
                    route.setDuration(tmp);
                    cout << "\nChoise the city: " << endl;
                    cities_out();
                    cin >> tmp;
                    route.setCity(instanse->getCity(atoi(tmp.c_str())));
                    cout << "\nChoise the hotel: " << endl;
                    hotels_out();
                    cin >> tmp;
                    route.setHotel(instanse->getHotel(atoi(tmp.c_str())));
                    cout << "\nChoise the company: " << endl;
                    companies_out();
                    cin >> tmp;
                    route.setCompany(instanse->getCompany(atoi(tmp.c_str())));
                    cout << "\nChoise the employee: " << endl;
                    employees_out();
                    cin >> tmp;
                    route.setEmployee(instanse->getEmployee(atoi(tmp.c_str())));
                    routeMap.save(route);
                    routes_out();
                    break;
                }
                case 2: {
                    Route route;
                    cout << "Choise [No] of route: ";
                    cin >> tmp;
                    route.setId(instanse->getRoutey(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter name: ";
                    cin >> tmp;
                    route.setName(tmp);
                    cout << "\nEnter duration: ";
                    cin >> tmp;
                    route.setDuration(tmp);
                    cout << "\nChoise the city: " << endl;
                    cities_out();
                    cin >> tmp;
                    route.setCity(instanse->getCity(atoi(tmp.c_str())));
                    cout << "\nChoise the hotel: " << endl;
                    hotels_out();
                    cin >> tmp;
                    route.setHotel(instanse->getHotel(atoi(tmp.c_str())));
                    cout << "\nChoise the company: " << endl;
                    companies_out();
                    cin >> tmp;
                    route.setCompany(instanse->getCompany(atoi(tmp.c_str())));
                    cout << "\nChoise the employee: " << endl;
                    employees_out();
                    cin >> tmp;
                    route.setEmployee(instanse->getEmployee(atoi(tmp.c_str())));
                    routeMap.save(route);
                    routes_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of route: ";
                    cin >> tmp;
                    routeMap.del(*instanse->getRoutey(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    routes_out();
                    break;
                }
                case 4: {
                    route_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 9: {
            routeMap.findAllInfo();
            clientMap.findAllInfo();
            flightsMap.findAllInfo();
            ticketMap.findAllInfo();
            tickets_out();
            string ticket_menu;
            bool ticket_exit = false;
            while (!ticket_exit) {
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> ticket_menu;
                switch (atoi(ticket_menu.c_str())) {
                case 1: {
                    Ticket ticket;

                    cout << "Choise [No] of flight: ";
                    flights_out();
                    cin >> tmp;
                    ticket.setFlights(instanse->getFlights(atoi(tmp.c_str())));
                    
                    cout << "\nEnter seat: ";
                    cin >> tmp;
                    ticket.setSeat(atoi(tmp.c_str()));

                    cout << "\nChoise [No] of client: ";
                    clients_out();
                    cin >> tmp;
                    ticket.setClient(instanse->getClient(atoi(tmp.c_str())));


                    ticketMap.save(ticket);
                    tickets_out();
                    break;
                }
                case 2: {
                    Ticket ticket;
                    
                    cout << "Choise [No] of the ticket: ";
                    cin >> tmp;
                    ticket.setId(instanse->getTicket(atoi(tmp.c_str()))->getId());

                    cout << "Choise [No] of the flight num: ";
                    flights_out();
                    cin >> tmp;
                    ticket.setFlights(instanse->getFlights(atoi(tmp.c_str())));
                    
                    cout << "\nEnter seat: ";
                    cin >> tmp;

                    ticket.setSeat(atoi(tmp.c_str()));
                    cout << "\nChoise [No] of client: ";
                    clients_out();
                    cin >> tmp;
                    ticket.setClient(instanse->getClient(atoi(tmp.c_str())));


                    ticketMap.save(ticket);
                    tickets_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of the flight num: ";
                    cin >> tmp;
                    ticketMap.del(*instanse->getTicket(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    tickets_out();
                    break;
                    break;
                }
                case 4: {
                    ticket_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 10: {
            string transf_menu;
            bool transf_exit = false;
            transferMap.findAllInfo();
            transfers_out();
            while (!transf_exit) {
                cout << "Choice function:\n";
                cout << "[1]Insert\n[2]Update\n[3]Delete\n[4]Return\n";
                cin >> transf_menu;
                switch (atoi(transf_menu.c_str())) {
                case 1: {
                    Transfer trans;
                    cout << "Enter the num of transfer: ";
                    cin >> tmp;
                    trans.setNum(atoi(tmp.c_str()));
                    cout << "\nEnter post: ";
                    std::getline(std::cin, tmp);
                    std::getline(std::cin, tmp);
                    trans.setPost(tmp);

                    cout << "\nEnter reason: ";
                    std::getline(std::cin, tmp);
                    trans.setReason(tmp);
                    cout << "\nEnter Date: ";
                    cin >> tmp;
                    trans.setDate(tmp);

                    transferMap.save(trans);
                    transfers_out();
                    break;
                }
                case 2: {
                    Transfer trans;
                    cout << "Choise [No] of transfer: ";
                    cin >> tmp;
                    trans.setId(instanse->getTransfer(atoi(tmp.c_str()))->getId());
                    cout << "\nEnter num: ";
                    cin >> tmp;
                    trans.setNum(atoi(tmp.c_str()));
                    cout << "\nEnter post: ";
                    cin >> tmp;
                    trans.setPost(tmp);
                    cout << "\nEnter reason: ";
                    cin >> tmp;
                    trans.setReason(tmp);
                    cout << "\nEnter date: ";
                    cin >> tmp;
                    trans.setDate(tmp);

                    transferMap.save(trans);
                    transfers_out();
                    break;
                }
                case 3: {
                    cout << "Choise [No] of transfer: ";
                    cin >> tmp;
                    transferMap.del(*instanse->getTransfer(atoi(tmp.c_str())), atoi(tmp.c_str()));
                    transfers_out();
                    break;
                }
                case 4: {
                    transf_exit = true;
                    break;
                }
                default: {
                    cout << "Incorrect choise!" << endl;
                    break;
                }
                }
            }
            break;
        }
        case 11: {
            cout << "Exit";
            exit = true;
            break;
        }
        default: {
            cout << "Incorrect choise!" << endl;
            break;
        }
        }

    }
    return 0;
}