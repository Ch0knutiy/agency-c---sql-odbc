#include "ClientMapper.h"

using namespace std;

ClientMapper::ClientMapper(DataBase& _db) :
	Mapper(_db), id(), surname(), name(), patronymic(), phone(), date(), time(), route() {}

bool ClientMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void ClientMapper::save(Client& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int ClientMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from client");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &surname, SURNAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, PATRONYMIC_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &phone, PHONE_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &date, DATE_SIZE, nullptr);
		retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &time, TIME_SIZE, nullptr);
		retcode = SQLBindCol(statement, 8, SQL_C_LONG, &route, ROUTE_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Client _client;
				_client.setId(id);
				_client.setSurname(reinterpret_cast<char*>(surname));
				_client.setName(reinterpret_cast<char*>(name));
				_client.setPatronymic(reinterpret_cast<char*>(patronymic));
				_client.setPhone(reinterpret_cast<char*>(phone));
				_client.setDate(reinterpret_cast<char*>(date));
				_client.setTime(reinterpret_cast<char*>(time));

				map<long, Route>* mapRoute = Repository::getInstance()->getRouteMap();
				for (auto it = mapRoute->begin(); it != mapRoute->end(); it++) {
					if (it->second.getId() == *route)
						_client.setRoute(&it->second);
				}
				Repository::getInstance()->setClient(_client);
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

void ClientMapper::_insert(Client& obj) {
	char sqlReq[512];
	long route_id;
	map<long, Route>* mapRoute = Repository::getInstance()->getRouteMap();
	for (auto it = mapRoute->begin(); it != mapRoute->end(); it++) {
		if (it->second.getId() == obj.getRoute()->getId()) {
			route_id = it->second.getId();
			break;
		}
	}

	snprintf(sqlReq, 512, "insert into client (surname, name, patronymic, phone, date_of_buy, time_of_buy, route_id) values ('%s', '%s','%s','%s','%s','%s','%ld')",
		obj.getSurname().c_str(), obj.getName().c_str(), obj.getPatronymic().c_str(),  obj.getPhone().c_str(), 
		obj.getDate().c_str(), obj.getTime().c_str(), route_id);
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from client ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &surname, SURNAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, PATRONYMIC_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &phone, PHONE_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_DATE, &date, DATE_SIZE, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_TIME, &time, TIME_SIZE, nullptr);
	retcode = SQLBindCol(statement, 8, SQL_C_LONG, &route, ROUTE_SIZE, nullptr);
	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setClient(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void ClientMapper::_update(Client& obj) {

	char sqlReq[512];
	long route_id;
	map<long, Route>* mapRoute = Repository::getInstance()->getRouteMap();
	for (auto it = mapRoute->begin(); it != mapRoute->end(); it++) {
		if (it->second.getId() == obj.getRoute()->getId()) {
			route_id = it->second.getId();
			break;
		}
	}
	snprintf(sqlReq, 512, "update client set surname = '%s', name = '%s', patronymic = '%s', phone = '%s', date_of_buy = '%s', time_of_buy = '%s', route_id = %ld where id = %ld",
		obj.getSurname().c_str(), obj.getName().c_str(), obj.getPatronymic().c_str(), obj.getPhone().c_str(),
		obj.getDate().c_str(), obj.getTime().c_str(), route_id, obj.getId());
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

	Repository::getInstance()->setClient(obj);
}

void ClientMapper::del(Client& obj, long client_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteClient(client_key, obj);
}

void ClientMapper::_delete(Client& obj) {
	char sqlReq3[512];
	const char* tableClient = "Client";

	snprintf(sqlReq3, 512, "delete from client where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableClient << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
