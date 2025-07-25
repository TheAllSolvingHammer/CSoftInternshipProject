#include "pch.h"
#include "JobTitlesTable.h"
#include "afxwin.h"


CJobTitlesTable::CJobTitlesTable() : CDatabaseTableConnection2 (m_oCommand.m_recJobTitle, _T("JOB_TITLES"))
{
    //super(var1,var2)
    if (!OpenConnection(m_oDataSource, m_oSession))
    {
        AfxMessageBox(_T("Error connecting to the database"));
    }
}

CJobTitlesTable::~CJobTitlesTable()
{
    m_oCommand.Close();
    m_oSession.Close();
    m_oDataSource.Close();
}

bool CJobTitlesTable::SelectAllUsers(CJobTitlesArray& oArray)
{
    this->SelectAll(oArray);
    return true;
}
bool CJobTitlesTable::SelectSingle(const long lID, JOB_TITLES& rec)
{
    this->SelectWhereID(lID, rec);
    return true;
}


bool CJobTitlesTable::Insert(JOB_TITLES& recJobTitle)
{
    CString strSQL = _T("SELECT * FROM JOB_TITLES");

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_IRowsetChange, true);

    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    props.AddProperty(DBPROP_QUICKRESTART, true);

    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
    if (FAILED(hRes)) {
        return false;
    }

    //m_oCommand.m_recJobTitle = recJobTitle;
    hRes = m_oCommand.Insert(JOB_TITLES_DATA_ACCESSOR_INDEX);
    if (FAILED(hRes))
    {
        return false;
    }

    hRes = m_oCommand.MoveLast();
    if (FAILED(hRes))
    {
        return false;
    }
    //recJobTitle = m_oCommand.m_recJobTitle;
    return SUCCEEDED(hRes);
}

bool CJobTitlesTable::DeleteWhereID(const long lID)
{
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM JOB_TITLES WHERE ID = %d"), lID);

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_IRowsetChange, true);
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
    if (FAILED(hRes)) {
        return false;
    }

    if (m_oCommand.MoveFirst() != S_OK) {
        return false;
    }

    hRes = m_oCommand.Delete();
    if (FAILED(hRes)) {
        return false;
    }
    return true;
}