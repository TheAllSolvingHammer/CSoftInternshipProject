#include "pch.h"
#include "UsersTable.h"
#include "afxwin.h"


CUsersTable::CUsersTable()
{
    if (!OpenConnection(m_oDataSource, m_oSession))
    {
        AfxMessageBox(_T("Error connecting to the database"));
    }
}

CUsersTable::~CUsersTable()
{
    m_oCommand.Close();
    m_oSession.Close();
    m_oDataSource.Close();
}

bool CUsersTable::SelectAll(CUsersArray& oUsersArray)
{
    HRESULT hRes = m_oCommand.Open(m_oSession, _T("SELECT * FROM USERS"));
    if (FAILED(hRes)) 
    {
        return false;
    }

    while (m_oCommand.MoveNext() == S_OK) {
        USERS* pUser = new USERS();
        (*pUser) = m_oCommand.m_recUser;
        oUsersArray.Add(pUser);
    }

    m_oCommand.Close();
    return true;
}

void CUsersTable::HandleUsersArray(CUsersArray& oUsersArray)
{
    for (INT_PTR i = 0;i < oUsersArray.GetCount();i++) {
        delete oUsersArray[i];
    }
    oUsersArray.RemoveAll();
}

bool CUsersTable::SelectWhereID(const long lID, USERS& recUser)
{
    if (!OpenRowByID(lID, m_oDataSource, m_oSession, false))
    {
        return false;
    }

    recUser = m_oCommand.m_recUser;

    m_oCommand.Close();
    return true;
}

bool CUsersTable::OpenRowByID(long lID, CDataSource& oDataSource, CSession& oSession, bool bUpdatable)
{
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM USERS WHERE ID = %d"), lID);

    HRESULT hRes;
    if (bUpdatable)
    {
        CDBPropSet props(DBPROPSET_ROWSET);
        props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
        props.AddProperty(DBPROP_IRowsetScroll, true);
        props.AddProperty(DBPROP_IRowsetChange, true);
        props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);
        hRes = m_oCommand.Open(oSession, strSQL, &props);
    }
    else
    {
        hRes = m_oCommand.Open(oSession, strSQL);
    }

    if (FAILED(hRes)) {
        return false;
    }

    if (m_oCommand.MoveFirst() != S_OK) {
        return false;
    }
    return true;

}

bool CUsersTable::UpdateWhereID(const long lID, USERS& recUser)
{
    if (!OpenRowByID(lID, m_oDataSource, m_oSession, true))
    {
        return false;
    }

    if (m_oCommand.m_recUser.nUpdateCounter != recUser.nUpdateCounter)
    {
        return false;
    }

    m_oCommand.m_recUser = recUser;
    m_oCommand.m_recUser.nUpdateCounter++;
    recUser = m_oCommand.m_recUser;

    HRESULT hRes = m_oCommand.SetData(USERS_DATA_ACCESSOR_INDEX);

    m_oCommand.Close();
    return SUCCEEDED(hRes);
}

bool CUsersTable::Insert(USERS& recUser)
{
    CString strSQL = _T("SELECT * FROM USERS");

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_IRowsetChange, true);
    
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    props.AddProperty(DBPROP_QUICKRESTART, true);

    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
    if (FAILED(hRes)) {
        return false;
    }

    m_oCommand.m_recUser = recUser;
    hRes = m_oCommand.Insert(USERS_DATA_ACCESSOR_INDEX);
    if (FAILED(hRes))
    {
        return false;
    }

    hRes = m_oCommand.MoveLast();
    if (FAILED(hRes))
    {
        return false;
    }

    recUser = m_oCommand.m_recUser;
    m_oCommand.Close();
    return SUCCEEDED(hRes);
}

bool CUsersTable::DeleteWhereID(const long lID)
{
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM USERS WHERE ID = %d"), lID);

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_IRowsetChange, true);
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
    if (FAILED(hRes)) 
    {
        return false;
    }

    if (m_oCommand.MoveFirst() != S_OK) 
    {
        return false;
    }

    hRes = m_oCommand.Delete();
    if (FAILED(hRes)) 
    {
        return false;
    }

    m_oCommand.Close();
    return true;
}

