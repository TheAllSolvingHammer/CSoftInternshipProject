#include "pch.h"
#include "UsersAppService.h"
#include <UsersTable.h>


CUsersAppService::CUsersAppService()
{

}

CUsersAppService::~CUsersAppService()
{

}

bool CUsersAppService::GetAllUsers(CUsersArray& oUsersArray) 
{
	
	if (!CUsersTable().SelectAll(oUsersArray)) {
		return false;
	}

	return true;
}

bool CUsersAppService::AddUser(USERS& recUser)
{
	if (!CUsersTable().Insert(recUser)) {
		return false;
	}
	return true;
}

bool CUsersAppService::UpdateUser(const long lID,USERS& recUser)
{
	if (!CUsersTable().UpdateWhereID(lID, recUser)) {
		return false;
	}
	return true;
}
bool CUsersAppService::DeleteUser(const long lID) 
{
	if (!CUsersTable().DeleteWhereID(lID)) {
		return false;
	}
	return true;
}