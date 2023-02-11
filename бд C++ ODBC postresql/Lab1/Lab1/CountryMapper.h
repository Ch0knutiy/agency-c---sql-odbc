#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define COUNTRY_LENGTH 168

class CountryMapper :
    public Mapper<Country>
{
public:
    CountryMapper(DataBase& db);
    void save(Country& obj) override;
    void del(Country& obj, long country_key);

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR country[COUNTRY_LENGTH];
   
    void _insert(Country& obj) override;
    void _update(Country& obj) override;
    void _delete(Country& obj) override;
    bool int_signed(const string& s);
};


