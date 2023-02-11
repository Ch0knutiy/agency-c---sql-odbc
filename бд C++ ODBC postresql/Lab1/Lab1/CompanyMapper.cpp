#include "CompanyMapper.h"

using namespace std;

CompanyMapper::CompanyMapper(DataBase& _db) :
	Mapper(_db), id(), name(), flights() {}

bool CompanyMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void CompanyMapper::save(Company& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int CompanyMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from company");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &flights, NUMF_LENGHT, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Company _company;
				_company.setId(id);
				_company.setName(reinterpret_cast<char*>(name));
				map<long, Flights>* mapFlights = Repository::getInstance()->getFlightsMap();
				for (auto it = mapFlights->begin(); it != mapFlights->end(); it++) {
					if (it->second.getNum() == (reinterpret_cast<char*>(flights)))
						_company.setFlights(&it->second);
				}
				Repository::getInstance()->setCompany(_company);
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

void CompanyMapper::_insert(Company& obj) {
	char sqlReq[512];
	string flights_num;
	map<long, Flights>* mapFlights = Repository::getInstance()->getFlightsMap();
	for (auto it = mapFlights->begin(); it != mapFlights->end(); it++) {
		if (it->second.getNum() == obj.getFlights()->getNum()) {
			flights_num = it->second.getNum();
			break;
		}
	}
	
	snprintf(sqlReq, 512, "insert into company (name, flights_num) values ('%s', '%s')",
		obj.getName().c_str(), flights_num.c_str());
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from company ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_LONG, &flights, NUMF_LENGHT, nullptr);
	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setCompany(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void CompanyMapper::_update(Company& obj) {

	char sqlReq[512];
	string flights_num;
	map<long, Flights>* mapFlights = Repository::getInstance()->getFlightsMap();
	for (auto it = mapFlights->begin(); it != mapFlights->end(); it++) {
		if (it->second.getNum() == obj.getFlights()->getNum()) {
			flights_num = it->second.getNum();
			break;
		}
	}
	snprintf(sqlReq, 512, "update company set name = '%s',flights_num = '%s' where id = %ld",
		obj.getName().c_str(), flights_num.c_str(), obj.getId());
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

	Repository::getInstance()->setCompany(obj);
}

void CompanyMapper::del(Company& obj, long company_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteCompany(company_key, obj);
}

void CompanyMapper::_delete(Company& obj) {
	char sqlReq3[512];
	const char* tableCompany = "Company";

	snprintf(sqlReq3, 512, "delete from company where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableCompany << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
