#include "EmployeeMapper.h"

using namespace std;

EmployeeMapper::EmployeeMapper(DataBase& _db) :
	Mapper(_db), id(), surname(), name(), patronymic(), address(),birth(),post(),salary(),transfer_id(), phone() {}

bool EmployeeMapper::int_signed(const string& s)
{
	size_t offset = 0;
	if (s[offset] == '-')
		++offset;
	return s.find_first_not_of("0123456789", offset) == string::npos;
}

void EmployeeMapper::save(Employee& obj) {
	if (!obj.getId()) {

		this->_insert(obj);
	}
	else {
		this->_update(obj);
	}
}

int EmployeeMapper::findAllInfo() {

	try {
		SQLHSTMT statement = db.execSQL("select * from employee");
		SQLRETURN retcode;
		retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
		retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &surname, SURNAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, PATRONYMIC_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &address, ADDRESS_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &birth, BIRTH_SIZE, nullptr);
		retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &post, POST_LENGTH, nullptr);
		retcode = SQLBindCol(statement, 8, SQL_C_LONG, &salary, SALARY_SIZE, nullptr);
		retcode = SQLBindCol(statement, 9, SQL_C_LONG, &transfer_id, TRANSFER_SIZE, nullptr);
		retcode = SQLBindCol(statement, 10, SQL_C_CHAR, &phone, PHONE_LENGTH, nullptr);
		while (1) {
			retcode = SQLFetch(statement);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				Employee _employee;
				_employee.setId(id);
				_employee.setSurname(reinterpret_cast<char*>(surname));
				_employee.setName(reinterpret_cast<char*>(name));
				_employee.setPatronymic(reinterpret_cast<char*>(patronymic));
				_employee.setAddress(reinterpret_cast<char*>(address));
				_employee.setBirth(reinterpret_cast<char*>(birth));
				_employee.setPost(reinterpret_cast<char*>(post));
				_employee.setSalary(salary);
				_employee.setPhone(reinterpret_cast<char*>(phone));

				map<long, Transfer>* mapTransfer = Repository::getInstance()->getTransfMap();
				for (auto it = mapTransfer->begin(); it != mapTransfer->end(); it++) {
					if (it->second.getId() == *transfer_id)
						_employee.setTransferNum(&it->second);
				}
				Repository::getInstance()->setEmployee(_employee);
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

void EmployeeMapper::_insert(Employee& obj) {
	char sqlReq[512];
	long transfer_id;
	map<long, Transfer>* mapTransfer = Repository::getInstance()->getTransfMap();
	for (auto it = mapTransfer->begin(); it != mapTransfer->end(); it++) {
		if (it->second.getId() == obj.getTransferNum()->getId()) {
			transfer_id = it->second.getId();
			break;
		}
	}

	snprintf(sqlReq, 512, "insert into employee (surname, name, patronymic, address, birth, post, salary, transfer_id, phone) values ('%s', '%s','%s','%s','%s','%s','%ld','%ld', '%s')",
		obj.getSurname().c_str(), obj.getName().c_str(), obj.getPatronymic().c_str(), obj.getAddress().c_str(),
		obj.getBirth().c_str(), obj.getPost().c_str(), salary, transfer_id, obj.getPhone().c_str());
	try {
		db.execSQL(sqlReq);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_ERROR) {
			cout << "Error of insert!" << endl;
			return;
		}
	}
	SQLHSTMT statement = db.execSQL("select * from employee ORDER BY id DESC limit 1");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_SIZE, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &surname, SURNAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &name, NAME_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, PATRONYMIC_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &address, ADDRESS_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &birth, BIRTH_SIZE, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &post, POST_LENGTH, nullptr);
	retcode = SQLBindCol(statement, 8, SQL_C_LONG, &salary, SALARY_SIZE, nullptr);
	retcode = SQLBindCol(statement, 9, SQL_C_LONG, &transfer_id, TRANSFER_SIZE, nullptr);
	retcode = SQLBindCol(statement, 10, SQL_C_CHAR, &phone, PHONE_LENGTH, nullptr);
	retcode = SQLFetch(statement);
	obj.setId(id);
	Repository::getInstance()->setEmployee(obj);
	SQLFreeStmt(statement, SQL_CLOSE);
}

void EmployeeMapper::_update(Employee& obj) {

	char sqlReq[512];
	long transfer_id;
	map<long, Transfer>* mapTransfer = Repository::getInstance()->getTransfMap();
	for (auto it = mapTransfer->begin(); it != mapTransfer->end(); it++) {
		if (it->second.getId() == obj.getTransferNum()->getId()) {
			transfer_id = it->second.getId();
			break;
		}
	}
	snprintf(sqlReq, 512, "update employee set surname = '%s', name = '%s',patronymic = '%s', address = '%s',birth = '%s',post = '%s',salary = %ld, transfer_id = %ld, phone = '%s' where id = %ld",
		obj.getSurname().c_str(), obj.getName().c_str(), obj.getPatronymic().c_str(), obj.getAddress().c_str(),
		obj.getBirth().c_str(), obj.getPost().c_str(), salary, transfer_id, obj.getPhone().c_str(), obj.getId());
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

	Repository::getInstance()->setEmployee(obj);
}

void EmployeeMapper::del(Employee& obj, long employee_key) {
	this->_delete(obj);
	Repository::getInstance()->deleteEmployee(employee_key,obj);
}

void EmployeeMapper::_delete(Employee& obj) {
	char sqlReq3[512];
	const char* tableEmployee = "Employee";

	snprintf(sqlReq3, 512, "delete from employee where id = %ld", obj.getId());

	try {
		db.execSQL(sqlReq3);
	}
	catch (SQLRETURN sqlRet) {
		if (sqlRet == SQL_NO_DATA) {
			std::cout << "Entry in the table " << tableEmployee << "  id = " << obj.getId() << " doesn't exist!" << std::endl;
		}
		if (sqlRet == SQL_ERROR) {
			cout << "Error of delete!" << endl;
			return;
		}
	}
}
