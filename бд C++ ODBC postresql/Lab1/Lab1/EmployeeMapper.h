#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define SURNAME_LENGTH 20
#define NAME_LENGTH 20
#define PATRONYMIC_LENGTH 20
#define ADDRESS_LENGTH 20
#define BIRTH_SIZE sizeof(string)
#define POST_LENGTH 100
#define SALARY_SIZE sizeof(long)
#define TRANSFER_SIZE sizeof(long)
#define PHONE_LENGTH 11

class EmployeeMapper :
    public Mapper<Employee>
{
public:
    EmployeeMapper(DataBase& db);
    void save(Employee& obj) override;
    void del(Employee& obj, long employee_key) override;

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR surname[SURNAME_LENGTH];
    SQLCHAR name[NAME_LENGTH];
    SQLCHAR patronymic[PATRONYMIC_LENGTH];
    SQLCHAR address[ADDRESS_LENGTH];
    SQLDATE birth[BIRTH_SIZE];
    SQLCHAR post[POST_LENGTH];
    SQLINTEGER salary;
    SQLINTEGER transfer_id[TRANSFER_SIZE];
    SQLCHAR phone[PHONE_LENGTH];

    void _insert(Employee& obj) override;
    void _update(Employee& obj) override;
    void _delete(Employee& obj) override;
    bool int_signed(const string& s);
};

