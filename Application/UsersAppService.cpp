#include "pch.h"
#include "UsersAppService.h"
#include "UsersTable.h"

CUsersAppService::CUsersAppService() 
{

}

CUsersAppService::~CUsersAppService()
{

}

bool CUsersAppService::GetAllUsers(CUsersArray& oUsersArray) 
{
	CUsersTable oUsersTable;
	return oUsersTable.SelectAll(oUsersArray);
}