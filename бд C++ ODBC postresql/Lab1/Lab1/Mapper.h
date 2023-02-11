#pragma once
#include "Connect.h"
#include <iostream>
#include <vector>


template <class DataT> class Mapper
{
public:
	Mapper(DataBase& _db) : db(_db) {

	}
	virtual void save(DataT& obj) = 0;
	virtual void del(DataT& obj, long key) = 0;

	virtual int findAllInfo() = 0;

protected:
	DataBase& db;

	virtual void _insert(DataT& obj) = 0;
	virtual void _update(DataT& obj) = 0;
	virtual void _delete(DataT& obj) = 0;
};


