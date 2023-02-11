#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define NUM_SIZE sizeof(long)
#define POST_LENGTH 100
#define REASON_LENGTH 100
#define DATE_SIZE sizeof(string)

class TransferMapper :
    public Mapper<Transfer>
{
public:
    TransferMapper(DataBase& db);
    void save(Transfer& obj) override;
    void del(Transfer& obj, long transfer_key) override;

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLINTEGER num;
    SQLCHAR post[POST_LENGTH];
    SQLCHAR reason[REASON_LENGTH];
    SQLDATE date[DATE_SIZE];
   

    void _insert(Transfer& obj) override;
    void _update(Transfer& obj) override;
    void _delete(Transfer& obj) override;
    bool int_signed(const string& s);
};


