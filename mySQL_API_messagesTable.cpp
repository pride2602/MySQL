#include "mySQL_API_messagesTable.h"
#include <iostream>
#include <mysql.h>

using namespace std;
class mySQL_API_messagesTable : public mySQL_API_messagesTable
{
public:
	mySQL_API_messagesTable(mySQL_API_database* dbHandle);

	void addMessage(const std::string& SenderID, const std::string& receiverID, const std::string& text);

	const std::string getSenderById(const std::string& messageId);
	const std::string getReceiverById(const std::string& messageId);
	const std::string getTextById(const std::string& messageId);
	const std::string getSentTimeById(const std::string& messageId);
	const std::string getReceivedTimeById(const std::string& messageId);

	std::vector <std::string>& getUnreceivedMessagesIdsForUserId(const std::string& receiverId);

	void setReceived(const std::string& messageId);
	void setRecievedMultiple(std::vector<std::string>messageIds);
private:
};
