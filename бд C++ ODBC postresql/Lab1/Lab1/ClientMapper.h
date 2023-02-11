#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define SURNAME_LENGTH 30
#define NAME_LENGTH 30
#define PATRONYMIC_LENGTH 30
#define PHONE_LENGTH 11
#define DATE_SIZE sizeof(string)
#define TIME_SIZE sizeof(string)
#define ROUTE_SIZE sizeof(long)

class ClientMapper :
    public Mapper<Client>
{
public:
    ClientMapper(DataBase& db);
    void save(Client& obj) override;
    void del(Client& obj, long client_key) override;

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR surname[SURNAME_LENGTH];
    SQLCHAR name[NAME_LENGTH];
    SQLCHAR patronymic[PATRONYMIC_LENGTH];
    SQLCHAR phone[PHONE_LENGTH];
    SQLDATE date[DATE_SIZE];
    SQLTIME time[TIME_SIZE];
    SQLINTEGER route[ROUTE_SIZE];

    void _insert(Client& obj) override;
    void _update(Client& obj) override;
    void _delete(Client& obj) override;
    bool int_signed(const string& s);
};

