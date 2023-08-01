#pragma once
#include <iostream>

#pragma comment(lib, "libmysql.lib")

#ifdef __linux__
#include <mysql/mysql.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <mysql.h>
#else
#error Not implemented!
#endif
/*
Класс, обеспечивающий создание/подключение к базе данных mySQL.
*/

class mySQL_API_database
{
public:
	mySQL_API_database(const std::string& host, const std::string& userName, const std::string& userPassword);
	~mySQL_API_database();

	bool getStatus() const;
	std::string getName() const;
	MYSQL* getHandle();

	bool connect(const std::string& dbName);
	bool create(const std::string& dbName);
	bool connectAnyway(const std::string& dbName);

private:
	MYSQL _sqlHandle;
	bool _status;
	std::string _host;
	std::string _userName;
	std::string _userPassword;
	std::string _dbName;
};