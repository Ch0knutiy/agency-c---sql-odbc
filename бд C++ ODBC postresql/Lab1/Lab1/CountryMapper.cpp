#include "CountryMapper.h"

using namespace std;

CountryMapper::CountryMapper(DataBase& _db) :
	Mapper(_db), id(), country(){}

bool CountryMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void CountryMapper::save(Country& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int CountryMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from country");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &country, COUNTRY_LENGTH, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Country _country;
				_country.setId(id);
				_country.setCountry(reinterpret_cast<char*>(country));
				Repository::getInstance()->setCountry(_country);
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

void CountryMapper::_insert(Country& obj) {
	char sqlReq[512];
	
	snprintf(sqlReq, 512, "insert into country (country) values ('%s')",
		obj.getCountry().c_str());
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from country ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &country, COUNTRY_LENGTH, nullptr);
	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setCountry(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void CountryMapper::_update(Country& obj) {

	char sqlReq[512];
	
	snprintf(sqlReq, 512, "update country set country = '%s' where id = %ld",
		obj.getCountry().c_str(), obj.getId());
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

	Repository::getInstance()->setCountry(obj);
}

void CountryMapper::del(Country& obj, long country_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteCountry(country_key, obj);
}

void CountryMapper::_delete(Country& obj) {
	char sqlReq3[512];
	const char* tableCountry = "Country";

	snprintf(sqlReq3, 512, "delete from country where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableCountry << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
