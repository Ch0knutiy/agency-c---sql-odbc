#include "Connect.h"
#pragma warning(disable : 4996)

using namespace std;

void DataBase::connToDb() {
	try {
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) == SQL_ERROR)
			throw exception("Error: Unable to allocate an environment handle");
		if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) == SQL_ERROR)
			throw exception("Error: Unable to set an environment variable");
		if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn) == SQL_ERROR)
			throw exception("Error: Unable to allocate an connection handle");
		if (SQLConnect(hConn, (SQLWCHAR*)L"PostgreSQL35W", SQL_NTS,
			(SQLWCHAR*)L"postgres", SQL_NTS, (SQLWCHAR*)L"root", SQL_NTS) == SQL_ERROR)
			throw exception("Error: Unable to connect to database");
		if (SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStat) == SQL_ERROR)
			throw exception("Error: Unable to allocate stmt handle");
		createTables();
	}
	catch (exception& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}
}

DataBase::DataBase() {
	connToDb();
	cout << "Successful connection to database!" << endl;
}

DataBase::~DataBase() {
	if (hStat != SQL_NULL_HSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, hStat);

	if (hConn != SQL_NULL_HDBC) {
		SQLDisconnect(this->hConn);
		SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	}
	if (hEnv != SQL_NULL_HENV)
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}


const wchar_t* str2wchar(const string& str) {
	const char* pstr = str.c_str();
	int bufLen = sizeof(char) * str.length() + 1;
	wchar_t* pRes = new wchar_t[bufLen];
	mbstowcs(pRes, pstr, bufLen);
	return pRes;
}


string DataBase::sqlRetToStr(SQLRETURN status) {
	switch (status)
	{
	case SQL_SUCCESS_WITH_INFO:
		return "SQL_SUCCESS_WITH_INFO";
		break;
	case SQL_NEED_DATA:
		return "SQL_NEED_DATA";
		break;
	case SQL_STILL_EXECUTING:
		return "SQL_STILL_EXECUTING";
		break;
	case SQL_ERROR:
		return "SQL_ERROR";
		break;
	case SQL_NO_DATA:
		return "SQL_NO_DATA";
		break;
	case SQL_INVALID_HANDLE:
		return "SQL_INVALID_HANDLE";
		break;
	case SQL_SUCCESS:
		return "SQL_SUCCESS";
		break;
	default:
		return "return value not found";
		break;
	}
}

void DataBase::createTables() {
	SQLRETURN status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS city(\
			id integer NOT NULL DEFAULT nextval('city_id_seq'::regclass),\
			city character varying(168) NOT NULL,\
			country_id integer NOT NULL,\
			CONSTRAINT city_pkey PRIMARY KEY(id),\
			CONSTRAINT city_city_key UNIQUE(city),\
			CONSTRAINT country_id FOREIGN KEY(country_id)\
			REFERENCES public.country(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS client(\
			id integer NOT NULL DEFAULT nextval('client_id_seq'::regclass),\
			surname character varying(30) COLLATE NOT NULL,\
			name character varying(30) COLLATE NOT NULL,\
			patronymic character varying(30) COLLATE  NOT NULL,\
			phone character varying(11) COLLATE NOT NULL,\
			date_of_buy date NOT NULL,\
			time_of_buy time without time zone NOT NULL,\
			route_id integer NOT NULL,\
			CONSTRAINT client_pkey PRIMARY KEY(id),\
			CONSTRAINT route_id FOREIGN KEY(route_id)\
			REFERENCES public.route(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE,\
			CONSTRAINT client_date_of_buy_check CHECK(date_of_buy <= CURRENT_DATE)\
		);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS company(\
			id integer NOT NULL DEFAULT nextval('company_id_seq'::regclass),\
			name character varying(100) COLLATE  NOT NULL,\
			flights_num character varying(15) COLLATE,\
			CONSTRAINT company_pkey PRIMARY KEY(id),\
			CONSTRAINT company_name_key UNIQUE(name),\
			CONSTRAINT flights_num FOREIGN KEY(flights_num)\
			REFERENCES public.flights(num) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE\
		);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS country(\
			id integer NOT NULL DEFAULT nextval('country_id_seq'::regclass),\
			country character varying(168) COLLATE NOT NULL,\
			CONSTRAINT country_pkey PRIMARY KEY(id),\
			CONSTRAINT country_country_key UNIQUE(country)\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS employee(\
			id integer NOT NULL GENERATED ALWAYS AS IDENTITY(INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 100 CACHE 1),\
			surname character varying(20) COLLATE NOT NULL,\
			name character varying(20) COLLATE NOT NULL,\
			patronymic character varying(20) COLLATE NOT NULL,\
			address character varying(20) COLLATE NOT NULL,\
			birth date NOT NULL,\
			post character varying(100) COLLATE NOT NULL,\
			salary integer NOT NULL,\
			transfer_id integer,\
			phone character varying(11) COLLATE NOT NULL,\
			CONSTRAINT employee_pkey PRIMARY KEY(id),\
			CONSTRAINT transfer_id FOREIGN KEY(transfer_id)\
			REFERENCES public.transfer(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE SET NULL\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS flights(\
			num character varying(13) COLLATE NOT NULL,\
			date date NOT NULL,\
			'time' time without time zone NOT NULL, \
			aircraft character varying(12) COLLATE NOT NULL,\
			class character varying(1) COLLATE NOT NULL,\
			free integer NOT NULL,\
			CONSTRAINT flights_num_key UNIQUE(num)\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS hotel(\
			id integer NOT NULL DEFAULT nextval('hotel_id_seq'::regclass),\
			name character varying(100) COLLATE NOT NULL\
			class integer NOT NULL,\
			categories character varying(100) COLLATE NOT NULL,\
			CONSTRAINT hotel_pkey PRIMARY KEY(id),\
			CONSTRAINT hotel_name_key UNIQUE(name)\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS public.route(\
			id integer NOT NULL DEFAULT nextval('route_id_seq'::regclass),\
			name character varying(100) COLLATE  NOT NULL,\
			city_id integer NOT NULL,\
			duration character varying(100) COLLATE  NOT NULL,\
			hotel_id integer NOT NULL,\
			company_id integer NOT NULL,\
			employee_id integer NOT NULL,\
			CONSTRAINT route_pkey PRIMARY KEY(id),\
			CONSTRAINT city_id FOREIGN KEY(city_id)\
			REFERENCES public.city(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE,\
			CONSTRAINT company_id FOREIGN KEY(company_id)\
			REFERENCES public.company(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE,\
			CONSTRAINT employee_id FOREIGN KEY(employee_id)\
			REFERENCES public.employee(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE,\
			CONSTRAINT hotel_id FOREIGN KEY(hotel_id)\
			REFERENCES public.hotel(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS public.transfer(\
			id integer NOT NULL DEFAULT nextval('transfer_id_seq'::regclass),\
			num integer NOT NULL,\
			post character varying(100) COLLATE NOT NULL,\
			reason character varying(100) COLLATE NOT NULL,\
			date date NOT NULL,\
			CONSTRAINT transfer_pkey PRIMARY KEY(id),\
			CONSTRAINT transfer_date_check CHECK(date <= CURRENT_DATE)\
			);",
		SQL_NTS);
	status = SQLExecDirect(hStat,
		(SQLWCHAR*)L"CREATE TABLE IF NOT EXISTS ticket(\
			id integer NOT NULL DEFAULT nextval('ticket_id_seq'::regclass),\
			flight_num character varying(13) COLLATE NOT NULL,\
			seat integer NOT NULL,\
			id_client integer NOT NULL,\
			CONSTRAINT ticket_pkey PRIMARY KEY(id),\
			CONSTRAINT flight_num FOREIGN KEY(flight_num)\
			REFERENCES public.flights(num) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE,\
			CONSTRAINT id_client FOREIGN KEY(id_client)\
			REFERENCES public.client(id) MATCH SIMPLE\
			ON UPDATE CASCADE\
			ON DELETE CASCADE,\
			CONSTRAINT ticket_seat_check CHECK(seat > 0 AND seat < 201)\
			); ",
		SQL_NTS);
}

const SQLHSTMT& DataBase::execSQL(string sqlStr) {
	SQLRETURN status = SQLExecDirect(hStat, (SQLWCHAR*)str2wchar(sqlStr),
		SQL_NTS);
	if (status == SQL_SUCCESS) {
		cout << sqlRetToStr(status) << endl;
		return hStat;
	}
	else {
		throw status;
	}
	return nullptr;
}
