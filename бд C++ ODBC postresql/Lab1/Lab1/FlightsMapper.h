#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define NUM_SIZE 30
#define DATE_LENGTH 30
#define TIME_LENGTH 30
#define AIRCRAFT_LENGTH 30
#define CLASS_LENGTH 30
#define FREE_SIZE sizeof(long)

class FlightsMapper :
    public Mapper<Flights>
{
public:
    FlightsMapper(DataBase& db);
    void save(Flights& obj) override;
    void del(Flights& obj, long flights_key) override;
    void save(Flights& obj, bool update);

    int findAllInfo() override;

private:
    SQLCHAR num[NUM_SIZE];
    SQLDATE date[DATE_LENGTH];
    SQLTIME time[TIME_LENGTH];
    SQLCHAR aircraft[AIRCRAFT_LENGTH];
    SQLCHAR _class[CLASS_LENGTH];
    SQLINTEGER free;

    void _insert(Flights& obj) override;
    void _update(Flights& obj) override;
    void _delete(Flights& obj) override;
    bool int_signed(const string& s);
};

