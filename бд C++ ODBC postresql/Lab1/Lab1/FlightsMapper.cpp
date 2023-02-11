#include "FlightsMapper.h"

using namespace std;

FlightsMapper::FlightsMapper(DataBase& _db) :
	Mapper(_db), num(), date(), time(), aircraft(), _class(), free() {}

bool FlightsMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void FlightsMapper::save(Flights& obj, bool update_flag) {
	if (!update_flag) {
		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}
void FlightsMapper::save(Flights& obj) { return; }

int FlightsMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from flights");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_CHAR, &num, NUM_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &date, DATE_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &time, TIME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &aircraft, AIRCRAFT_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &_class, CLASS_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_LONG, &free, FREE_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Flights _flights;
				_flights.setNum(reinterpret_cast<char*>(num));
				_flights.setDate(reinterpret_cast<char*>(date));
				_flights.setTime(reinterpret_cast<char*>(time));
				_flights.setAircraft(reinterpret_cast<char*>(aircraft));
				_flights.setClass(reinterpret_cast<char*>(_class));
				_flights.setFree(free);

				Repository::getInstance()->setFlights(_flights);
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

void FlightsMapper::_insert(Flights& obj) {
	char sqlReq[512];
	
	snprintf(sqlReq, 512, "insert into flights (num, date, time, aircraft, class, free) values ('%s', '%s','%s','%s','%s',%ld)",
		obj.getNum().c_str(), obj.getDate().c_str(), obj.getTime().c_str(), obj.getAircraft().c_str(), obj.getClass().c_str(), obj.getFree());
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	Repository::getInstance()->setFlights(obj);
}

void FlightsMapper::_update(Flights& obj) {

	char sqlReq[512];
	snprintf(sqlReq, 512, "update flights set date= '%s', time= '%s', aircraft= '%s', class= '%s', free = %ld where num = '%s'",
		obj.getDate().c_str(), obj.getTime().c_str(), obj.getAircraft().c_str(), obj.getClass().c_str(), obj.getFree(), obj.getNum().c_str());
	try {
		db.execSQL(sqlReq);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			cout << "An entry with this ID was not found! id = " << obj.getNum() << endl;
			return;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of update!" << endl;
			return;
		}
	}

	Repository::getInstance()->setFlights(obj);
}

void FlightsMapper::del(Flights& obj, long flights_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteFlights(flights_key, obj);
}

void FlightsMapper::_delete(Flights& obj) {
	char sqlReq3[512];
	const char* tableFlights = "Flights";

	snprintf(sqlReq3, 512, "delete from flights where num = '%s'", obj.getNum().c_str());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableFlights << "  id = " << obj.getNum() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
