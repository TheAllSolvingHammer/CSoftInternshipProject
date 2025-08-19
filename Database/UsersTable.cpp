#include "pch.h"
#include "UsersTable.h"
#define QUERY_SELECT_BY_USERNAME  "SELECT * FROM %s WHERE NAME = %s"

CUsersTable::CUsersTable() : CBaseTable(m_oCommand.m_recUser, _T(USERS_TABLE_NAME))
{

}

CUsersTable::CUsersTable(CSession* pSession) : CBaseTable(m_oCommand.m_recUser, _T(USERS_TABLE_NAME), *pSession)
{

}

CUsersTable::~CUsersTable()
{

}

bool CUsersTable::SelectUserByUsername(const CString& strUsername, USERS& recUser)
{
	if (FAILED(StartOrContinueTransaction()))
	{
		return false;
	}

	CString strSQL;
	strSQL.Format(_T(QUERY_SELECT_BY_USERNAME), m_strTableName.GetString(), strUsername.GetString());

	HRESULT hRes = m_oCommand.Open(m_oSession, strSQL);
	if (FAILED(hRes))
	{
		CommitOrAbortTransaction(false);
		return false;
	}

	hRes = m_oCommand.MoveFirst();
	if (hRes != S_OK)
	{
		m_oCommand.Close();
		CommitOrAbortTransaction(false);
		return false;
	}

	recUser = m_recRecord;

	m_oCommand.Close();
	return SUCCEEDED(CommitOrAbortTransaction(true));
}


