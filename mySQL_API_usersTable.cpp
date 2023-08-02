#pragma once
#include "mySQL_API_usersTable.h"
#include "mySQL_API_database.h"
#include <vector>
#include "mySQL_API_consts.h"
#include "mySQL_API_messagesTable.h"
#include "mySQL_API_table.h"

mySQL_API_usersTable::mySQL_API_usersTable(mySQL_API_database* dbHandle) : 
	mySQL_API_usersTable(constUsersTable_name, dbHandle, constUsersTable_columnTypes, constUsersTable_columnNames)
{
}
mySQL_API_usersTable::~mySQL_API_usersTable()
{
	updateValuesWhereEqual(constUsr_status, "offline", constUsr_status, "online");
}
std::string mySQL_API_usersTable::getIdByLogin(const std::string& userLogin)
{
	return selectOneRowWhereEqual(constUsr_id, constUsr_login, userLogin);
}

const std::string mySQL_API_usersTable::getLoginbyId(const std::string& userId)
{
	return selectOneRowWhereEqual(constUsr_login, constUsr_id, userId);
}
const std::string mySQL_API_usersTable::getPwHashById(const std::string& userId)
{
	return selectOneRowWhereEqual(constUsr_hash, constUsr_id, userId);
}
const std::string mySQL_API_usersTable::getNameById(const std::string& userId)
{
	return selectOneRowWhereEqual(constUsr_name, constUsr_id, userId);
}
const std::string mySQL_API_usersTable::getRegDateById(const std::string& userId)
{
	return selectOneRowWhereEqual(constUsr_regDate, constUsr_id, userId);
}

const std::string mySQL_API_usersTable::getEmailById(const std::string& userId)
{
	return selectOneRowWhereEqual(constUsr_eMail, constUsr_id, userId);
}

const std::string mySQL_API_usersTable::getStatusById(const std::string& userId)
{
	return selectOneRowWhereEqual(constUsr_status, constUsr_id, userId);
}

void mySQL_API_table::setOnline(const std::string& userId)
{
	updateValuesWhereEqual(constUsr_status, "online", constUsr_id, userId);
}
void mySQL_API_table::setOffline(const std::string& userId)
{
	updateValuesWhereEqual(constUsr_status, "offline", constUsr_id, userId);
}

bool mySQL_API_usersTable::isOnline(const std::string& userId)
{
	std::string statusStr = selectOneRowWhereEqual(constUsr_status, constUsr_id, userId);
	if (statusStr.compare("online") == 0)
		return true;
	else
		return false;
}

bool mySQL_API_usersTable::isOffline(const std::string& userId)
{
	std::string statusStr = selectOneRowWhereEqual(constUsr_status, constUsr_id, userId);
	if (statusStr.compare("offline") == 0)
		return true;
	else
		return false;
}
bool mySQL_API_usersTable::isDeleted(const std::string& userId)
{
	std::string statusStr = selectOneRowWhereEqual(constUsr_status, constUsr_id, userId);
	if (statusStr.compare("deleted") == 0)
		return true;
	else
		return false;
}
bool mySQL_API_usersTable::addUser(const std::string& userLogin, const std::string& userPwHash, const std::string& userName, const std::string& eMail)
{
	if ((userLogin.empty()) || (userPwHash.empty()) || (userName.empty()) || (eMail.empty()))
	{
#ifdef _DEBUG
		std::cout << "[FAILED] <<mySQL_API_usersTable::addUser> Empty account data!" << std::endl;
#endif
		return false;
	}
	std::string idExists = getIdByLogin(userLogin);
	if (idExists.empty())
	{
		std::vector<std::string> columnNames = { constUsr_login, constUsr_hash, constUsr_name, constUsr_eMail };
		std::vector<std::string> values = { usrlogin,             UsrPwHash,     userName,      eMail };
		insert(columnNames, values);

#ifdef _DEBUG
		std::cout << "[DEBUG] <mySQL_API_usersTable::addUser> Successfully added new user " << userLogin << "to DB" << std::endl;
#endif
		return true;
	}
	else
	{

#ifdef _DEBUG
		std::cout << "[DEBUG] <mySQL_API_usersTable::addUser> User " << userLogin << " already exists in DB!" << std::endl;
#endif
		return false;
	}
}
bool mySQL_API_usersTable::deleteUser(const std::string& userLogin)
{
	std::string idExists = getIdByLogin(userLogin);
	if (!idExists.empty())
	{
		if (isDeleted(idExists))
		{
#ifdef _DEBUG
			std::cout << "[DEBUG] <<mySQL_API_usersTable::deleteUser> User " << userLogin << " is already deleted! " << std::endl;
#endif
			return true;
		}
		updateValuesWhereEqual(constUsr_status, "deleted", constUsr_id, idExists);
		updateValuesWhereEqual(constUsr_hash, "", constUsr_id, idExists);
	}


#ifdef _DEBUG
		    std::cout << "[DEBUG] << mySQL_API_usersTable::deleteUser> Successfully deleted user " << userLogin << " from DB" << std::endl;
#endif		
		return true;
	}
	else
	{
#ifdef _DEBUG
		std::cout << "[DEBUG] << mySQL_API_usersTable::deleteUser > User " << userLogin << " unknown!" << std::endl;
#endif
			return false;
	}
}
bool mySQL_API_usersTable::login(const std::string & userLogin, const std::string & userPwHash)
{
		std::string idExists = getIdByLogin(userLogin);
		if (!idExists.empty())
		{
			if (isDeleted(idExists))
			{
#ifdef _DEBUG
				std::cout << "[FAILED] <mySQL_API_usersTable::login> User " << userLogin << "is deleted! " << std::endl;
#endif
				return false;
			}

			std::string bdHash = getPwHashById(idExists);
			if (bdHash.compare(userPwHash) == 0)
			{
				setOnline(idExists);
#ifdef _DEBUG
				std::cout << "[DEBUG] <mySQL_API_usersTable::login> User " << userLogin << "successfully logged in" << std::endl;
#endif
				updateValuesWhereEqualNoQuotes(constUsr_lastlogin, "CURRENT_TIMESTAMP", constUsr_id, idExists);
				return true;
			}
			else
			{
#ifdef _DEBUG
				std::cout << "[DEBUG] <mySQL_API_usersTable::login> Wrong password of user " << userLogin << " !" << std::endl;
#endif
				return false;
			}
		}
		else
		{
#ifdef _DEBUG
			std::cout << "[DEBUG] <mySQL_API_usersTable::login> User " << userLogin << "unknown!" < std::endl;
#endif
			return false;
		}
	
}
bool mySQL_API_usersTable::logout
{
	std::string idExists = getIdByLogin(userLogin)
	if (!idExists.empty())
	{
		if (isOnline(idExists))
		{
			setOffline(idExists))
			{
				setOffline(idExists))
				updateValuesWhereEqualNoQuotes(constUsr_lastLogin, "CURRENT_TIMESTAMP", constUsr_id, idExists);
#ifdef _DEBUG
			std::cout << "[DEBUG] <mySQL_API_usersTable::logout> User " << userLogin << "logged out " << std::endl;
#endif
			return true;
		}
		if (isOffline(idExists))
		{
#ifdef _DEBUG
			std::cout << "[	DEBUG ] <mySQL_API_usersTable::logout> User " << userLogin << "is already offline!" << std::endl;
#endif
		    return true;
		}
        if
		{
#ifdef _DEBUG
			std::cout << "[DEBUG] < mySQL_API_usersTable::logout> User" << userLogin << "is deleted!" << std::endl;
#endif
			return false;
		}
	}
	else
	{
#ifdef _DEBUG

		std::cout << "[DEBUG] <mySQL_API_usersTable::logout	> User " << userLogin << "unknown!" < std::endl;
#endif
		return false;
	}
}