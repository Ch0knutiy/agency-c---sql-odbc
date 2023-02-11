#include "HotelMapper.h"

using namespace std;

HotelMapper::HotelMapper(DataBase& _db) :
	Mapper(_db), id(), name(), _class(), categories() {}

bool HotelMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void HotelMapper::save(Hotel& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int HotelMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from hotel");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name,NAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_LONG, &_class, CLASS_SIZE, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &categories, CATEGORIES_LENGTH, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Hotel _hotel;
				_hotel.setId(id);
				_hotel.setName(reinterpret_cast<char*>(name));
				_hotel.setClass(_class);
				_hotel.setCategories(reinterpret_cast<char*>(categories));

				Repository::getInstance()->setHotel(_hotel);
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

void HotelMapper::_insert(Hotel& obj) {
	char sqlReq[512];

	snprintf(sqlReq, 512, "insert into hotel (name, class, categories) values ('%s',%ld,'%s')",
		obj.getName().c_str(), obj.getClass(), obj.getCategories().c_str());
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from hotel ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_LONG, &_class, CLASS_SIZE, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &categories, CATEGORIES_LENGTH, nullptr);

	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setHotel(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void HotelMapper::_update(Hotel& obj) {

	char sqlReq[512];
	snprintf(sqlReq, 512, "update hotel set name = '%s', class = %ld, categories = '%s' where id = %ld",
		obj.getName().c_str(), obj.getClass(), obj.getCategories().c_str(), obj.getId());
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

	Repository::getInstance()->setHotel(obj);
}

void HotelMapper::del(Hotel& obj, long hotel_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteHotel(hotel_key, obj);
}

void HotelMapper::_delete(Hotel& obj) {
	char sqlReq3[512];
	const char* tableHotel = "Hotel";

	snprintf(sqlReq3, 512, "delete from hotel where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableHotel << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
