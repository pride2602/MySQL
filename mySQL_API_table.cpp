#include "mySQL_API_table.h"
#include "mySQL_API_consts.h"
#include "mySQL_API_messagesTable.h"
#include <vector>
#include <iostream>
#include "mySQL_API_database.h"


mySQL_API_table::mySQL_API_table(const std::string& tableName, mySQL_API_database* dbHandle, const std::vector<std::string>& columnTypes, const std::vector<std::string>& columnNames) :
	_tableName(tableName), _dbHandle(dbHandle)
{
	std::string req;
	if (!checkifColumnNamesOk(columnNames))
	{
		std::cout << "[FAILED] <mySQL_API_table::Could not connect to" << tableName << " in " << _dbHandle->getName() << "!" << std::endl;
		return;
	}
	else
	{
		req = "CREATE TABLE IF NOT EXISTS " + _tableName + "(";
		for (size_t i = 0; i < columnTypes.size(); i++)
		{
			if (i != 0)
				req = req + ", ";
			req = req + columnNames.at(i) + " " + columnTypes.at(i);
		}
		req = req + ")";
#ifdef _DEBUG
		std::cout << "[DEBUG ] <mySQL_API_table::mySQL_API_table> CREATE request: " << req << std::endl;
#endif
		mysql_query(_dbHandle->getHandle(), req.c_str());
	}
}
bool mySQL_API_table::checkIfColumnNamesOK(const std::vector<std::string>& columnNames)
{
	std::string tmpStr;
	std::vector<std::string> tmpVect;
	bool tableExists = false;
	MYSQL_RES* res;
	MYSQL_ROW* row;
	std::string req = "SELECT COLUMN_NAME FROM information schema.COLUMN WHERE TABLE_SCHEMA = '" + _dbHandle->getName() + "'AND TABLE_NAME = '" + _tableName + "'";
	mysql_query(_dbHandle->getHandle(), req.c_str());
#ifdef _DEBUG
	std::cout << "[DEBUG ] <mySQL_API_table::checkIfColumnNamesOK> SELECT request: " << req << std::endl;
#endif
	if (res = mysql_store_result(_dbHandle->getHandle())) {
		while (row = mysql_fetch_row(res))
		{
			tableExists = true;
			if (mysql_num_field(res) == 0)
			{
#ifdef _DEBUG
				std::cout << "[FAILED] <<mySQL_API_table::checkIfColumnNamesOK> SELECT returned NULL! " << std::endl;
#endif
				return false;
			}
			tmpStr = row[0];
			tmpVect.push_back(tmpStr);
		}
		if (tableExists)
		{
			if (tmpVect.size() != columnNames.size())
			{
#ifdef _DEBUG
				std::cout << "[FAILED] <mySQL_API_table::checkIfColumnNamesOK> Table exists and contains wrong number of column! Manual redesign needed!" << std::endl;
#endif
				return false;
			}
			else
			{
			}
		}
	}
	else
	{
#ifdef _DEBUG
		std::cout << "[FAILED]<mySQL_API_table::checkIfColumnNamesOK " << mysql_error(_dbHandle->getHandle()) << std::endl;
#endif
		return false;
	}
}

void mySQL_API_table::insert(const std::vector<std::string>& collumnNames, const std::vector<std::string>& values)
{
	std::string req = "INSERT " + _tableName + "(";
	for (size_t i = 0; i < collumnNames.size(); i++)
	{
		if (i != 0)
			req = req + ", ";
		req = req + collumnNames.at(i) + " ";
	}
	req = req + ") VALUES (";
	for (size_t i = 0; i < values.size(); i++)
	{
		if (i != 0)
			req = req + ", ";
		req = req + "'" + values.at(i) + "'";
	}
	req = req + ")";
#ifdef _DEBUG
	std::cout << "[DEBUG] <mySQL_API_table::insert> INSERT request: " << req << std::endl;
#endif
	mysql_query(_dbHandle->getHandle(), req.c.str());
}
std::string mySQL_API_table::selectOneRowWhereEqual(const std::string& fieldNameReturn, const std::string& fieldNameCompare, const std::string& compareValue)
{
	std::vector<std::string> tmpVect = selectSeveralRowsWhereEqual(fieldNameReturn, fieldNameCompare, compareValue);
	std::string retVal;

	if (tmpVect.size() == 0)
	{
#ifdef _DEBUG
		std::cout << "[ WARN ] <mySQL_API_table::selectOneRowWhereEqual> SELECT returned NULL! " << std::endl;
#endif
		return std::string();
	}
	if (tmpVect.size() > 1)
	{
#ifdef _DEBUG
		std::cout << " [ WARN ] <mySQL_API_table::selectOneRowWhereEqual> SELECT returned several rows! Using the first!" << std::endl;
#endif
	}
	retVal = tmpVect[0];
	return retVal;
}
std::vector<std::string> mySQL_API_table::selectSeveralRowsWhereEqual(const std::string& fieldNameReturn, const std::fieldCompare, const std::string& compareValue)
{
	std::vector<std::string>retVal;
	std::string tmpStr;
	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string req = "SELECT " + fieldNameReturn + " FROM " + _tableName + " WHERE " + fieldNameCompare + "='" + compareValue + "'";
#ifdef _DEBUG
	std::cout << "[DEBUG ] <mySQL_API_table::selectSeveralWhereEqual> SELECT request: " << req << std::endl;
#endif
	mysql_query(_dbHandle->getHandle(), req.c._str());

	if (res = mysql_store_result(_dbHandle->getHandle())) {
		while (row = mysql_fetch_row(res))
		{
			if (mysql_num_fields(res) == 0)
			{
#ifdef  _DEBUG

				std::cout << "[ WARN ] <mySQL_API_table::selectSeveralRowsWhereEqual> SELECT returned NULL!" << std::endl;
#endif
			}
			if (mysql_num_fields(res) > 1)
			{
#ifdef _DEBUG

				std::cout << "[WARN] <mySQL_API_table::selectSeveralRowsWhereEqual> SELECT returned several columns!" << std::endl;
#endif

			}
			tmpStr = row[0];
			retVal.push_back(tmpStr);
		}
	}
	else
	{
#ifdef _DEBUG
		std::cout << "[FAILED] <mySQL_API_table::selectSeveralRowsWhereEqual> " << mysql_error(_dbHandle->getHandle()) << std::endl;
#endif
		return std::vector < std::string>();
	}
}

	//CREATE TABLE IF NOT EXISTS tasks(
	//	task_id     SERIAL PRIMARY KEY,
	//	title       VARCHAR(255) NOT NULL,
//		start_date  DATE,
//		due_date    DATE,
//		status int  NOT NULL,
//		description TEXT,
	//	created_at  TIMESTAMP DEFAULT CURRENT_TIMESTAMP

		//CREATE DATABASE <имя базы данных>;

	//CREATE TRIGGER testref
		//BEFORE INSERT ON test1
		//FOR EACH ROW
		//EXECUTE PROCEDURE testref();

	//Пример функции триггера :
//	CREATE OR REPLACE FUNCTION testref() RETURNS TRIGGER
	//	AS $testtr$
		//BEGIN
//		insert into "Test2"("Id", "Label2") values(New.Id, Null);
//	return new;
//	END;
//	$testtr$ LANGUAGE plpgsql;


//	CREATE TABLE CUSTOMERS(
//		ID   INT       NOT NULL,
//		PRIMARY KEY(ID)
//	);

//	ALTER TABLE customers
//		ADD CONSTRAINT id PRIMARY KEY(id);

//	ALTER TABLE orders
//		ADD FOREIGN KEY(customer_id) REFERENCES customers(id);

//	INSERT products
//	(productname,
//		manufacturer,
//		price,
//		productcount)
//		VALUES('iPhone 8',
//			'Apple',
//			51000,
//			3),
//		('P20 Lite',
//			'Huawei',
//			34000,
//			4),
//		('Galaxy S8',
//			'Samsung',
//			46000,
//			2);
//
//	mysql > SELECT*
//		FROM      table1
//		LEFT JOIN table2
//		using     (id);
//	mysql > SELECT*
//		FROM      table1
//		LEFT JOIN table2
//		ON        table1.id = table2.id;
//	mysql > SELECT*
//		FROM   table1,
//		table2
//		WHERE  table1.id = table2.id;
//

//	SELECT NAME
//		FROM   USER
//		GROUP  BY NAME
//		HAVING Count(*) > 1;

//	SELECT*
//		FROM   USER
//		WHERE  NAME IN
//		(
//			SELECT   NAME
//			FROM     USER
//			GROUP BY NAME
//			HAVING   Count(*) > 1;);


//	SELECT*
//		FROM   test
//		WHERE  int_i = 7;//