#include "TicketMapper.h"

using namespace std;

TicketMapper::TicketMapper(DataBase& _db) :
	Mapper(_db), id(), seat(), flights(), client() {}

bool TicketMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void TicketMapper::save(Ticket& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int TicketMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from ticket");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &flights, FLIGHTS_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_LONG, &seat, SEAT_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_LONG, &client, CLIENT_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Ticket _ticket;
				_ticket.setId(id);
				_ticket.setSeat(seat);

				map<long, Flights>* mapFlights = Repository::getInstance()->getFlightsMap();
				for (auto it = mapFlights->begin(); it != mapFlights->end(); it++) {
					if (it->second.getNum() == reinterpret_cast<char*>(flights))
						_ticket.setFlights(&it->second);
				}

				map<long, Client>* mapClient = Repository::getInstance()->getClientMap();
				for (auto it = mapClient->begin(); it != mapClient->end(); it++) {
					if (it->second.getId() == *client)
						_ticket.setClient(&it->second);
				}

				Repository::getInstance()->setTicket(_ticket);
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

void TicketMapper::_insert(Ticket& obj) {
	char sqlReq[512];
	long client_id;
	map<long, Client>* mapClient = Repository::getInstance()->getClientMap();
	for (auto it = mapClient->begin(); it != mapClient->end(); it++) {
		if (it->second.getId() == obj.getClient()->getId()) {
			client_id = it->second.getId();
			break;
		}
	}

	snprintf(sqlReq, 512, "insert into ticket (flight_num, seat, id_client) values ('%s', '%ld','%ld')",
		obj.getFlights()->getNum().c_str(), obj.getSeat(), client_id);
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from ticket ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_LONG, &seat, SEAT_SIZE, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &flights, FLIGHTS_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_LONG, &client, CLIENT_SIZE, nullptr);

	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setTicket(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void TicketMapper::_update(Ticket& obj) {

	char sqlReq[512];
	long client_id;
	map<long, Client>* mapClient = Repository::getInstance()->getClientMap();
	for (auto it = mapClient->begin(); it != mapClient->end(); it++) {
		if (it->second.getId() == obj.getClient()->getId()) {
			client_id = it->second.getId();
			break;
		}
	}
	snprintf(sqlReq, 512, "update ticket set flight_num = '%s', seat = '%ld', id_client = '%ld' where id = '%ld'",
		obj.getFlights()->getNum().c_str(), obj.getSeat(), client_id, obj.getId());
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

	Repository::getInstance()->setTicket(obj);
}

void TicketMapper::del(Ticket& obj, long ticket_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteTicket(ticket_key, obj);
}

void TicketMapper::_delete(Ticket& obj) {
	char sqlReq3[512];
	const char* tableTicket = "Ticket";

	snprintf(sqlReq3, 512, "delete from ticket where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableTicket << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
