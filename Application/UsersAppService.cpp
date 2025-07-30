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
	return m_oUsersTable.SelectAll(oUsersArray);

}

bool CUsersAppService::AddUser(USERS& recUser)
{
	return m_oUsersTable.Insert(recUser);
}

bool CUsersAppService::UpdateUser(const long lID,USERS& recUser)
{
	return m_oUsersTable.UpdateWhereID(lID, recUser);
}
bool CUsersAppService::DeleteUser(const long lID) 
{
	return m_oUsersTable.DeleteWhereID(lID);
}