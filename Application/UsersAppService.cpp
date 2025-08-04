#include "pch.h"
#include "UsersAppService.h"


CUsersAppService::CUsersAppService() 
{

}

CUsersAppService::~CUsersAppService()
{

}

bool CUsersAppService::GetAllUsers(CUsersArray& oUsersArray) 
{
	if (!m_oUsersTable.SelectAll(oUsersArray)) {
		//TRACE(_T(""))
		return false;
	}
	return true;
}

bool CUsersAppService::AddUser(USERS& recUser)
{
	if (!m_oUsersTable.Insert(recUser)) {
		return false;
	}
	return true;
}

bool CUsersAppService::UpdateUser(const long lID,USERS& recUser)
{
	if (!m_oUsersTable.UpdateWhereID(lID, recUser)) {
		return false;
	}
	return true;
}
bool CUsersAppService::DeleteUser(const long lID) 
{
	if (!m_oUsersTable.DeleteWhereID(lID)) {
		return false;
	}
	return true;
}