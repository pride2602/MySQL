#pragma once

constexpr const char* constUsersTable_name = "users";
constexpr const char* constUsr_id = "id";
constexpr const char* constUsrType_id = "INT AUTO_INCREMENT PRIMARY KEY";
constexpr const char* constUsr_login = "login";
constexpr const char* constUsrType_login = "VARCHAR(20) NOT NULL";
constexpr const char* constUsr_hash = "pw_hash";
constexpr const char* constUsrType_hash = "VARCHAR(40) NOT NULL";
constexpr const char* constUsr_name = "name";
constexpr const char* constUsrType_name = "VARCHAR(40) NOT NULL";
constexpr const char* constUsr_regDate = "reg_date";
constexpr const char* constUsrType_regDate = "TIMESTAMP DEFAULT CURRENT_TIMESTAMP";
constexpr const char* constUsr_eMail = "email";
constexpr const char* constUsrType_eMail = "VARCHAR(40)";
constexpr const char* constUsr_status = "status";
constexpr const char* constUsrType_status = "VARCHAR(20) DEFAULT 'offline'";
constexpr const char* constUsr_lastLogin = "last_login";
constexpr const char* constUsrType_lastLogin = "TIMESTAMP DEFAULT NULL";
const std::vector<std::string> constUsersTable_columnNames = { constUsr_id,     constUsr_login,     constUsr_hash,     constUsr_name,     constUsr_regDate,     constUsr_eMail,     constUsr_status,     constUsr_lastlogin };
const std::vector<std::string> constUsersTable_columnTypes = { constUsrType_id, constUsrType_login, constUsrType_hash, constUsrType_name, constUsrType_regDate, constUsrType_eMail, constUsrType_status, constUsrType_lastlogin };


constexpr const char* constMessageTable_name = "messages";
constexpr const char* constMsg_id = "id";
constexpr const char* constMsgType_id = "INT AUTO_INCREMENT PRIMARY KEY";
constexpr const char* constMsg_sender = "sender_id";
constexpr const char* constMsgType_sender = "INT NOT NULL REFERENCES users(id)";
constexpr const char* constMsg_receiver = "receiver_id";
constexpr const char* constMsgType_receiver = "INT NOT NULL REFERENCES users(id)";
constexpr const char* constMsg_text = "text";
constexpr const char* constMsgType_text = "TEXT";
constexpr const char* constMsg_sent = "sent";
constexpr const char* constMsgType_sent = "TIMESTAMP DEFAULT CURRENT_TIMESTAMP";
constexpr const char* constMsg_recieved = "recieved";
constexpr const char* constMsgType_recieved = "TIMESTAMP DEFAULT NULL";
const std::vector<std::string>constMessegesTable_collumnNames = { constMsg_id,     constMsg_sender,     constMsg_receiver,     constMsg_text,     constMsg_sent,     constMsg_recieved };
const std::vector<std::string>constMessegesTable_collumnTypes = { constMsgType_id, constMsgType_sender, constMsgType_receiver, constMsgType_text, constMsgType_sent, constMsgType_recieved };