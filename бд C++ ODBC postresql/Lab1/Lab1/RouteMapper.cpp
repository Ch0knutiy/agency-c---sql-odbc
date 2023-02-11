#include "RouteMapper.h"

using namespace std;

RouteMapper::RouteMapper(DataBase& _db) :
	Mapper(_db), id(), name(), city(), duration(), hotel(), company(), employee()  {}

bool RouteMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void RouteMapper::save(Route& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int RouteMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from route");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_LONG, &city, CITY_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &duration, DURATION_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_LONG, &hotel, HOTEL_SIZE, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_LONG, &company, COMPANY_SIZE, nullptr);
		retcode = SQLBindCol(statement, 7, SQL_C_LONG, &employee, EMPLOYEE_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Route _route;
				_route.setId(id);
				_route.setName(reinterpret_cast<char*>(name));

				map<long, City>* mapCity = Repository::getInstance()->getCityMap();
				for (auto it = mapCity->begin(); it != mapCity->end(); it++) {
					if (it->second.getId() == *city)
						_route.setCity(&it->second);
				}

				_route.setDuration(reinterpret_cast<char*>(duration));

				map<long, Hotel>* mapHotel = Repository::getInstance()->getHotelMap();
				for (auto it = mapHotel->begin(); it != mapHotel->end(); it++) {
					if (it->second.getId() == *hotel)
						_route.setHotel(&it->second);
				}

				map<long, Company>* mapCompany = Repository::getInstance()->getCompMap();
				for (auto it = mapCompany->begin(); it != mapCompany->end(); it++) {
					if (it->second.getId() == *company)
						_route.setCompany(&it->second);
				}

				map<long, Employee>* mapEmployee = Repository::getInstance()->getEmplMap();
				for (auto it = mapEmployee->begin(); it != mapEmployee->end(); it++) {
					if (it->second.getId() == *employee)
						_route.setEmployee(&it->second);
				}

				Repository::getInstance()->setRoute(_route);
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

void RouteMapper::_insert(Route& obj) {
	char sqlReq[512];
	long city_id;
	map<long, City>* mapCity = Repository::getInstance()->getCityMap();
	for (auto it = mapCity->begin(); it != mapCity->end(); it++) {
		if (it->second.getId() == obj.getCity()->getId()) {
			city_id = it->second.getId();
			break;
		}
	}

	long hotel_id;
	map<long, Hotel>* mapHotel = Repository::getInstance()->getHotelMap();
	for (auto it = mapHotel->begin(); it != mapHotel->end(); it++) {
		if (it->second.getId() == obj.getHotel()->getId()) {
			hotel_id = it->second.getId();
			break;
		}
	}

	long company_id;
	map<long, Company>* mapCompany = Repository::getInstance()->getCompMap();
	for (auto it = mapCompany->begin(); it != mapCompany->end(); it++) {
		if (it->second.getId() == obj.getCompany()->getId()) {
			company_id = it->second.getId();
			break;
		}
	}

	long employee_id;
	map<long, Employee>* mapEmployee = Repository::getInstance()->getEmplMap();
	for (auto it = mapEmployee->begin(); it != mapEmployee->end(); it++) {
		if (it->second.getId() == obj.getEmployee()->getId()) {
			employee_id = it->second.getId();
			break;
		}
	}

	snprintf(sqlReq, 512, "insert into route (name, city_id, duration, hotel_id, company_id, employee_id) values ('%s', %ld, '%s', %ld, %ld, %ld)",
		obj.getName().c_str(), city_id, obj.getDuration().c_str(), hotel_id, company_id, employee_id);
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from route ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_LONG, &city, CITY_SIZE, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &duration, DURATION_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_LONG, &hotel, HOTEL_SIZE, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_LONG, &company, COMPANY_SIZE, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_LONG, &employee, EMPLOYEE_SIZE, nullptr);
	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setRoute(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void RouteMapper::_update(Route& obj) {

	char sqlReq[512];
	long city_id;
	map<long, City>* mapCity = Repository::getInstance()->getCityMap();
	for (auto it = mapCity->begin(); it != mapCity->end(); it++) {
		if (it->second.getId() == obj.getCity()->getId()) {
			city_id = it->second.getId();
			break;
		}
	}

	long hotel_id;
	map<long, Hotel>* mapHotel = Repository::getInstance()->getHotelMap();
	for (auto it = mapHotel->begin(); it != mapHotel->end(); it++) {
		if (it->second.getId() == obj.getHotel()->getId()) {
			hotel_id = it->second.getId();
			break;
		}
	}

	long company_id;
	map<long, Company>* mapCompany = Repository::getInstance()->getCompMap();
	for (auto it = mapCompany->begin(); it != mapCompany->end(); it++) {
		if (it->second.getId() == obj.getCompany()->getId()) {
			company_id = it->second.getId();
			break;
		}
	}

	long employee_id;
	map<long, Employee>* mapEmployee = Repository::getInstance()->getEmplMap();
	for (auto it = mapEmployee->begin(); it != mapEmployee->end(); it++) {
		if (it->second.getId() == obj.getEmployee()->getId()) {
			employee_id = it->second.getId();
			break;
		}
	}
	snprintf(sqlReq, 512, "update route set name = '%s', city_id = %ld, duration = '%s', hotel_id = %ld, company_id = %ld, employee_id = %ld where id = %ld",
		obj.getName().c_str(), city_id, obj.getDuration().c_str(), hotel_id, company_id, employee_id, obj.getId());
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

	Repository::getInstance()->setRoute(obj);
}

void RouteMapper::del(Route& obj, long route_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteRoute(route_key, obj);
}

void RouteMapper::_delete(Route& obj) {
	char sqlReq3[512];
	const char* tableRoute = "Route";

	snprintf(sqlReq3, 512, "delete from route where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableRoute << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
