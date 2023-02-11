#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define NAME_LENGTH 100
#define NUMF_LENGHT 15

class CompanyMapper :
    public Mapper<Company>
{
public:
    CompanyMapper(DataBase& db);
    void save(Company& obj) override;
    void del(Company& obj, long company_key);

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR name[NAME_LENGTH];
    SQLCHAR flights[NUMF_LENGHT];

    void _insert(Company& obj) override;
    void _update(Company& obj) override;
    void _delete(Company& obj) override;
    bool int_signed(const string& s);
};

