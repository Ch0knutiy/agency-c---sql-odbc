#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define SEAT_SIZE sizeof(long)
#define FLIGHTS_LENGTH 30
#define CLIENT_SIZE sizeof(long)

class TicketMapper :
    public Mapper<Ticket>
{
public:
    TicketMapper(DataBase& db);
    void save(Ticket& obj) override;
    void del(Ticket& obj, long ticket_key) override;

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLINTEGER seat;
    SQLCHAR flights[FLIGHTS_LENGTH];
    SQLINTEGER client[CLIENT_SIZE];

    void _insert(Ticket& obj) override;
    void _update(Ticket& obj) override;
    void _delete(Ticket& obj) override;
    bool int_signed(const string& s);
};


