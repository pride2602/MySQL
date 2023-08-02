#include "mySQL_API_database.h"

class mySQL_API_usersTable : public mySQL_API_table
{
public:
	mySQL_API_usersTable(mySQL_API_database* dbHandle);
	~mySQL_API_usersTable();

	std::string getIdByLogin(const std::string& userLogin);
	const std::string getLoginById(const std::string& userId);
	const std::string getPwHashById(const std::string& userId);
	const std::string getNameById(const std::string& userId);
	const std::string getRegDatebyId(const std::string& userId);
	const std::string getEmailById(const std::string& userId);
	const std::string getStatusById(const std::string& userId);
	void setOnline(const std::string& userId);
	void setOffline(const std::string& userId);
	bool isOnline(const std::string& userId);
	bool isOffline(const std::string& userId);
	bool isDeleted(const std::string& userId);

	bool addUser(const std::string& userLogin, const std::string& userPwHash, const std::string& userName, const std::string& eMail);
	bool deleteUser(const std::string& userLogin);
	bool login(const std::string& userLogin, const std::string& userPwHash);
	bool logout(const std::string& userLogin);

private:
};