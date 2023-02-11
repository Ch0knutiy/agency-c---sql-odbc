#include "CityMapper.h"

using namespace std;

CityMapper::CityMapper(DataBase& _db) :
	Mapper(_db), id(), city(), country() {}

bool CityMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void CityMapper::save(City& obj) {
	if (!obj.getId()) {
		
		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int CityMapper::findAllInfo() {
	Repository* instanse = Repository::getInstance();
	map<long, Country>* mapCountry;
	try {
		SQLHSTMT statement = db.execSQL("select * from city");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &city, CITY_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_LONG, &country, COUNTRY_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				City _city;
				_city.setId(id);
				_city.setCity(reinterpret_cast<char*>(city));
				mapCountry = instanse->getCounMap();
				for (auto it = mapCountry->begin(); it != mapCountry->end(); it++) {
					if (it->second.getId() == country) {
						_city.setCountry(&it->second);
						instanse->setCity(_city);
						break;
					}
				}
			}
			else {
				if (retcode != SQL_NO_DATA) {
					cout << "No data\n";
					return 1;
				}
				break;
			}
		}
		SQLFreeStmt(statement, SQL_CLOSE);
	}
	catch (SQLRETURN sqlRet) {
		db.sqlRetToStr(sqlRet);
	}
	return 0;
}

void CityMapper::_insert(City& obj) {
	char sqlReq[512];
	long country_id;
	map<long, Country>* mapCountry = Repository::getInstance()->getCounMap();
	for (auto it = mapCountry->begin(); it != mapCountry->end(); it++) {
		if (it->second.getId() == obj.getCountry()->getId()){
			country_id = it->second.getId();
			break;
		}
	}

	snprintf(sqlReq, 512, "insert into city (city, country_id) values ('%s', %ld)",
		obj.getCity().c_str(), country_id);
	try {
		db.execSQL(sqlReq);
		
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from city ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &city, CITY_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_LONG, &country, COUNTRY_SIZE, nullptr);
	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setCity(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void CityMapper::_update(City& obj) {

	char sqlReq[512];
	long country_id;
	map<long, Country>* mapCountry = Repository::getInstance()->getCounMap();
	for (auto it = mapCountry->begin(); it != mapCountry->end(); it++) {
		if (it->second.getId() == obj.getCountry()->getId()) {
			country_id = it->second.getId();
			break;
		}
	}
	snprintf(sqlReq, 512, "update city set city = '%s',country_id = %ld where id = %ld",
		obj.getCity().c_str(), country_id, obj.getId());
	try {
		db.execSQL(sqlReq);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			cout << "An entry with this ID was not found! id = " << obj.getId() << endl;
			return;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of update!" << endl;
			return;
		}
	}

	Repository::getInstance()->setCity(obj);
}

void CityMapper::del(City& obj, long city_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteCity(city_key, obj);
}

void CityMapper::_delete(City& obj) {
	char sqlReq3[512];
	const char* tableCity = "City";

	snprintf(sqlReq3, 512, "delete from city where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableCity << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
