#include "TransferMapper.h"

using namespace std;

TransferMapper::TransferMapper(DataBase& _db) :
	Mapper(_db), id(), num(), post(), reason(),date() {}

bool TransferMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void TransferMapper::save(Transfer& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int TransferMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from transfer");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_LONG, &num, NUM_SIZE, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &post, POST_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &reason, REASON_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &date, DATE_SIZE, nullptr);

		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Transfer _transfer;
				_transfer.setId(id);
				_transfer.setNum(num);
				_transfer.setPost(reinterpret_cast<char*>(post));
				_transfer.setReason(reinterpret_cast<char*>(reason));
				_transfer.setDate(reinterpret_cast<char*>(date));

				Repository::getInstance()->setTransfer(_transfer);
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

void TransferMapper::_insert(Transfer& obj) {
	char sqlReq[512];

	snprintf(sqlReq, 512, "insert into transfer (num, post, reason, date) values ('%ld', '%s', '%s','%s')",
		num, obj.getPost().c_str(), obj.getReason().c_str(), obj.getDate().c_str());
	try {
		db.execSQL(sqlReq);

	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from transfer ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_LONG, &num, NUM_SIZE, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &post, POST_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &reason, REASON_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &date, DATE_SIZE, nullptr);

	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setTransfer(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void TransferMapper::_update(Transfer& obj) {

	char sqlReq[512];

	snprintf(sqlReq, 512, "update transfer set num = '%ld', post = '%s', reason = '%s',date = '%s' where id = '%ld'",
		num, obj.getPost().c_str(), obj.getReason().c_str(), obj.getDate().c_str(), obj.getId());
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

	Repository::getInstance()->setTransfer(obj);
}

void TransferMapper::del(Transfer& obj, long transfer_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteTransfer(transfer_key, obj);
}

void TransferMapper::_delete(Transfer& obj) {
	char sqlReq3[512];
	const char* tableTransfer = "Transfer";

	snprintf(sqlReq3, 512, "delete from transfer where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableTransfer << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
