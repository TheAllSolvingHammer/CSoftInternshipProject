#include "pch.h"
#include "UsersAppService.h"


CUsersAppService::CUsersAppService():m_oArrayManager(CArrayManager::getInstance())
{

}

CUsersAppService::~CUsersAppService()
{

}

bool CUsersAppService::GetAllUsers(CUsersArray& oUsersArray) 
{
	//CArrayManager& oArrayManager = CArrayManager::getInstance();
	//CUsersArray* pNewUsersArray = new CUsersArray();

	//if (!m_oUsersTable.SelectAll(*pNewUsersArray)) {
	//	delete pNewUsersArray;
	//	return false;
	//}

	//CArrayManager::getInstance().AddCollection(COLLECTION_USERS, pNewUsersArray);
	//oArrayManager.GetCollection<USERS>(COLLECTION_USERS, *pNewUsersArray);
	//return true;

	if (!m_oUsersTable.SelectAll(oUsersArray)) {
		return false;
	}

	CArrayManager& oArrayManager = CArrayManager::getInstance();

	CUsersArray* pNewUsersArray = new CUsersArray();
	pNewUsersArray->Copy(oUsersArray);

	oArrayManager.AddCollection(COLLECTION_USERS, pNewUsersArray);

	CUsersArray* pGetUsersArray = new CUsersArray();

	pGetUsersArray=oArrayManager.GetCollection<USERS>(COLLECTION_USERS);
	CString str;
	str.Format(_T("Found %d users"), pGetUsersArray->GetCount());
	AfxMessageBox(str);
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