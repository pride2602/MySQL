#pragma once
#include <string>

class User
{
	const std::string login_;
	std::string password_;
	std::string name_;
	const char* constUsersTable_name = "users";
	const char* constUsr_id = "id";
	const char* constUsrType_id = "INT AUTO_INCREMENT PRIMARY KEY";
	const char* constUsr_login = "login";
	const char* constUsrType_login = "VARCHAR(20) NOT NULL";
	const char* constUsr_hash = "pw_hash";
	const char* constUsrType_hash = "VARCHAR(40) NOT NULL";
	const char* constUsr_name = "name";
	const char* constUsrType_name = "VARCHAR(40) NOT NULL";
	const char* constUsr_regDate = "reg_date";
	const char* constUsrType_regDate = "TIMESTAMP DEFAULT CURRENT_TIMESTAMP";
	const char* constUsr_eMail = "email";
	const char* constUsrType_eMail = "VARCHAR(40)";
	const char* constUsr_status = "status";
	const char* constUsrType_status = "VARCHAR(20) DEFAULT 'offline'";
	const char* constUsrLast_login = "Last_login";
	const char* constUsrType_Last_login = "TIMESTAMP DEFAULT NULL";

public:
	User(const std::string& login, const std::string& password, const std::string& name)
		: login_(login), password_(password), name_(name) {}
	const std::string& getUserByLogin()  const  { return login_; }

	const std::string& getUserByPassword() const { return password_; }
	void setUserPassword(const std::string& password) { password_ = password; }

	const std::string& getUserByName() const { return name_; }
	void setUserName(const std::string& name) { name_ = name; }

	const std::vector<std::string> constUsersTable_columnNames = { constUsr_id,     constUsr_login,     constUsr_hash,     constUsr_name,     constUsr_regDate,     constUsr_eMail,     constUsr_status,     constUsrLast_login };
	const std::vector<std::string> constUsersTable_columnTypes = { constUsrType_id, constUsrType_login, constUsrType_hash, constUsrType_name, constUsrType_regDate, constUsrType_eMail, constUsrType_status, constUsrType_Last_login };
};