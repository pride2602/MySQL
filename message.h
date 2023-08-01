#pragma once
#include "User.h"

class Message
{
	const std::string _from;
	const std::string _to;
	const std::string _text;
	const char* constMessageTable_name = "messages";
	const char* constMsg_id = "id";
	const char* constMsgType_id = "INT AUTO_INCREMENT PRIMARY KEY";
	const char* constMsg_sender = "sender_id";
	const char* constMsgType_sender = "INT NOT NULL REFERENCES users(id)";
	const char* constMsg_receiver = "receiver_id";
	const char* constMsgType_receiver = "INT NOT NULL REFERENCES users(id)";
	const char* constMsg_text = "text";
	const char* constMsgType_text = "TEXT";
	const char* constMsg_sent = "sent";
	const char* constMsgType_sent = "TIMESTAMP DEFAULT CURRENT_TIMESTAMP";
	const char* constMsg_recieved = "recieved";
	const char* constMsgType_recieved = "TIMESTAMP DEFAULT NULL";
public:

	Message(const std::string& from,const std::string& to, const std::string&text) : _from(from), _to(to), _text(text) {}

	const std::string &getFrom() const { return _from; }
	const std::string &getTo() const { return _to; }
	const std::string &getText() const { return _text; }
	const std::vector<std::string>constMessegesTable_collumnNames = { constMsg_id,     constMsg_sender,     constMsg_receiver,     constMsg_text,     constMsg_sent,     constMsg_recieved };
	const std::vector<std::string>constMessegesTable_collumnTypes = { constMsgType_id, constMsgType_sender, constMsgType_receiver, constMsgType_text, constMsgType_sent, constMsgType_recieved };
};

