#include <include/Boost_Asio/Boost_Asio_server.h>
#include <iostream>
#include "Boost_Asio_client.h"
#include "mySQL_API_consts.h"
#include "mySQL_API_messagesTable.h"
#include "mySQL_API_table.h"
#include "mySQL_API_usersTable.h"
#include <asio.hpp>

contexpr boost::asio::ip::port_type serverPortNumber = 5190;
contexpr boost::asio::io_service service;

contexpr const char* constDB_host = "localhost";
contexpr const char* constDB_name = "chat";
contexpr const char* constDB_password = "password";
contexpr const char* constDB_user = "user";

void onClientConnected(boost::shared_ptr <Boost_Asio_server> client, boost::asio::io_service* _ioService, const boost::system::error_code& err)
{
	client->onStart();
	boost::shared_ptr <Boost_Asio_server> new_client(new Boost_Asio_server(client.get()));
	_listenAcceptor.async_accept(new_client->getSocket(), boost::bind(onClientConnected, new_client, _ioService, boost::placeholders::_1));
}


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");

	struct utsname utsname;
	uname(&utname);
	std::cout << "Chat server (" << chatVersion << "_" << utsname.machine << ") running on '" << utsname.noname << "' under "
		<< utsname.sysname << " " << utsname.release << " build " << utsname.version << std::endl;

	boost::shared_ptr <Boost_Asio_server> firstClient(new Boost_Asio_server(&ioService, constDB_host, constDB_user, constDB_password, constDB_name));
	_listenAcceptor.async_accept(firstClient->getSocket(), boost::bind(onClientConnected, firstClient, &ioService, boost::placeholders::_1));
	ioService.run();


	mySQL_API_database chatDB(constDB_host, constDB_user, constDB_password);
	chatDB.connectAnyway(constDB_name);
	mySQL_API_usersTable chatUsers(&chatDB);
	mySQL_API_messagesTable chatMessage(&chatDB);

	chatUsers.addUser("user1", "HASH1234567898", "name1", "test@test.ru");
	chatUsers.addUser("user2", "pass2", "name2", "test@test.ru");
	chatUsers.addUser("user3", "pass3", "name3", "test@test.ru");

	chatUsers.login("user1", "HASH1234567898");
	chatUsers.login("user2", "pass2");
	chatUsers.login("user3", "wrong");

	chatMessage.addMessage("1", "2", "1-2");
	chatMessage.addMessage("1", "2", "2-3");
	chatMessage.addMessage("3", "1", "3-1");
	chatMessage.addMessage("1", "3", "1-3");
	chatMessage.addMessage("2", "1", "2-1");
	chatMessage.addMessage("3", "2", "3-2");

	chatMessages.setReceieverMultiple(chatMessages.getUnreceieverMessagesIdsForUserId("1"))

	chatUsers.logout("user1");
	chatUsers.deleteUser("user2");

	return 0;
};