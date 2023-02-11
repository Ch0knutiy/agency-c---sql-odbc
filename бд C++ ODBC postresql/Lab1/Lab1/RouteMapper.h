#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define NAME_LENGTH 100
#define CITY_SIZE sizeof(long)
#define DURATION_LENGTH 100
#define HOTEL_SIZE sizeof(long)
#define COMPANY_SIZE sizeof(long)
#define EMPLOYEE_SIZE sizeof(long)

class RouteMapper :
    public Mapper<Route>
{
public:
    RouteMapper(DataBase& db);
    void save(Route& obj) override;
    void del(Route& obj, long route_key);

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR name[NAME_LENGTH];
    SQLINTEGER city[CITY_SIZE];
    SQLCHAR duration[DURATION_LENGTH];
    SQLINTEGER hotel[HOTEL_SIZE];
    SQLINTEGER company[COMPANY_SIZE];
    SQLINTEGER employee[EMPLOYEE_SIZE];

    void _insert(Route& obj) override;
    void _update(Route& obj) override;
    void _delete(Route& obj) override;
    bool int_signed(const string& s);
};

