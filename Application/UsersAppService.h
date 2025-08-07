#pragma once
#include "Users.h"
#include "DllExport.h"
#include "..\Database\UsersTable.h"
#include "ArrayManager.h"

class ApplicationDLL_EXP CUsersAppService {
public:
	CUsersAppService();
	~CUsersAppService();
	bool GetAllUsers(CUsersArray& oUsersArray);
	bool AddUser(USERS& recUser);
	bool UpdateUser(const long lID,USERS& recUser);
	bool DeleteUser(const long lID);
private:
	CUsersTable m_oUsersTable;
	CArrayManager& m_oArrayManager;
};