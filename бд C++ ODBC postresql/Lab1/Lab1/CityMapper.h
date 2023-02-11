#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define CITY_LENGTH 168
#define COUNTRY_SIZE sizeof(long)

class CityMapper :
    public Mapper<City>
{
public:
    CityMapper(DataBase& db);
    void save(City& obj) override;
    void del(City& obj, long city_key) override;

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR city[CITY_LENGTH];
    SQLINTEGER country;
    
    void _insert(City& obj) override;
    void _update(City& obj) override;
    void _delete(City& obj) override;
    bool int_signed(const string& s);
};

