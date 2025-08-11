#include "pch.h"
#include "UsersTable.h"
#define QUERY_SELECT_BY_USERNAME  "SELECT * FROM %s WHERE NAME = %s"

CUsersTable::CUsersTable() : CBaseTable(m_oCommand.m_recUser, _T(USERS_TABLE_NAME))
{

}

CUsersTable::~CUsersTable()
{

}

bool CUsersTable::SelectUserByUsername(const CString& strUsername, USERS& recUser)
{
    HRESULT hRes = m_oSession.StartTransaction();
    if (FAILED(hRes))
    {
        AfxMessageBox(_T(ERR_TRANSACTION_START), MB_ICONERROR);
        return false;
    }

    CString strSQL;
    strSQL.Format(_T(QUERY_SELECT_BY_USERNAME), m_strTableName.GetString(),strUsername.GetString());

    hRes = m_oCommand.Open(m_oSession, strSQL);
    if (FAILED(hRes))
    {
        m_oSession.Abort();
        return false;
    }

    hRes = m_oCommand.MoveFirst();
    if (FAILED(hRes))
    {
        m_oCommand.Close();
        m_oSession.Abort();
        return false;
    }

    recUser = m_oCommand.m_recUser;

    m_oCommand.Close();
    m_oSession.Commit();
    return true;
}


