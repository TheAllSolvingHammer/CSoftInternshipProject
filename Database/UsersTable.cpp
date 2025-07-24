#include "pch.h"
#include "UsersTable.h"
#include "afxwin.h"


CUsersTable::CUsersTable()
{

}

CUsersTable::~CUsersTable()
{
    
}


void CUsersTable::CloseAll(CDataSource& oDataSource, CSession& oSession)
{
    m_oCommand.Close();
    oSession.Close();
    oDataSource.Close();
}

bool CUsersTable::SelectAll(CUsersArray& oUsersArray)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession)) 
    {
        return false;
    }

    HRESULT hRes = m_oCommand.Open(oSession, _T("SELECT * FROM USERS"));
    if (FAILED(hRes)) 
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    while (m_oCommand.MoveNext() == S_OK) {
        USERS* pUser = new USERS();
        (*pUser) = m_oCommand.m_recUser;
        oUsersArray.Add(pUser);
    }

    CloseAll(oDataSource, oSession);
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
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenRowByID(lID, oDataSource, oSession, false))
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    recUser = m_oCommand.m_recUser;

    CloseAll(oDataSource, oSession);
    return true;
}

bool CUsersTable::OpenRowByID(long lID, CDataSource& oDataSource, CSession& oSession, bool bUpdatable)
{
    if (!OpenConnection(oDataSource, oSession))
        return false;

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

    if (FAILED(hRes))
        return false;

    if (m_oCommand.MoveFirst() != S_OK)
        return false;

    return true;

}

bool CUsersTable::UpdateWhereID(const long lID, USERS& recUser)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenRowByID(lID, oDataSource, oSession, true))
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    if (m_oCommand.m_recUser.nUpdateCounter != recUser.nUpdateCounter)
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    m_oCommand.m_recUser = recUser;
    m_oCommand.m_recUser.nUpdateCounter++;
    recUser = m_oCommand.m_recUser;

    HRESULT hRes = m_oCommand.SetData(USERS_DATA_ACCESSOR_INDEX);

    CloseAll(oDataSource, oSession);
    return SUCCEEDED(hRes);
}

bool CUsersTable::Insert(USERS& recUser)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
    {
        return false;
    }

    CString strSQL = _T("SELECT * FROM USERS");

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_IRowsetChange, true);
    
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    props.AddProperty(DBPROP_QUICKRESTART, true);

    HRESULT hRes = m_oCommand.Open(oSession, strSQL, &props);
    if (FAILED(hRes)) {
        CloseAll(oDataSource, oSession);
        return false;
    }

    m_oCommand.m_recUser = recUser;
    hRes = m_oCommand.Insert(USERS_DATA_ACCESSOR_INDEX);
    if (FAILED(hRes))
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    hRes = m_oCommand.MoveLast();
    if (FAILED(hRes))
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    recUser = m_oCommand.m_recUser;
    CloseAll(oDataSource, oSession);
    return SUCCEEDED(hRes);
}

bool CUsersTable::DeleteWhereID(const long lID)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
    {
        return false;
    }

    CString strSQL;
    strSQL.Format(_T("SELECT * FROM USERS WHERE ID = %d"), lID);

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_IRowsetChange, true);
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

    HRESULT hRes = m_oCommand.Open(oSession, strSQL, &props);
    if (FAILED(hRes)) {
        CloseAll(oDataSource, oSession);
        return false;
    }

    if (m_oCommand.MoveFirst() != S_OK) {
        CloseAll(oDataSource, oSession);
        return false;
    }

    hRes = m_oCommand.Delete();
    if (FAILED(hRes)) {
        CloseAll(oDataSource, oSession);
        return false;
    }

    CloseAll(oDataSource, oSession);
    return true;
}

