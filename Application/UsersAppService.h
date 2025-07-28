#pragma once
#include "Users.h"
#include "DllExport.h"

class ApplicationDLL_EXP CUsersAppService {
public:
	CUsersAppService();
	~CUsersAppService();
	bool GetAllUsers(CUsersArray& oUsersArray);
};