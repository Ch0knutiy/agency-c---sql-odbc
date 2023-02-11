#pragma once
#include "Mapper.h"
#include "Repository.h"

using namespace std;

#define ID_SIZE sizeof(long)
#define NAME_LENGTH 100
#define CLASS_SIZE sizeof(long)
#define CATEGORIES_LENGTH 100

class HotelMapper :
    public Mapper<Hotel>
{
public:
    HotelMapper(DataBase& db);
    void save(Hotel& obj) override;
    void del(Hotel& obj, long hotel_key) override;

    int findAllInfo() override;

private:
    SQLINTEGER id;
    SQLCHAR name[NAME_LENGTH];
    SQLINTEGER _class;
    SQLCHAR categories[CATEGORIES_LENGTH];

    void _insert(Hotel& obj) override;
    void _update(Hotel& obj) override;
    void _delete(Hotel& obj) override;
    bool int_signed(const string& s);
};


