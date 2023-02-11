#include <windows.h> 
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <iostream>

class DataBase
{
public:
	DataBase();
	~DataBase();
	const SQLHSTMT& execSQL(std::string sqlStr);
	std::string sqlRetToStr(SQLRETURN status);
private:
	SQLHENV hEnv = SQL_NULL_HENV;
	SQLHDBC hConn = SQL_NULL_HDBC;
	SQLHSTMT hStat = SQL_NULL_HSTMT;
	void connToDb();
	void createTables();
};
