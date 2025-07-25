#include "pch.h"
#include "JobTitlesTable.h"
#include "afxwin.h"


CJobTitlesTable::CJobTitlesTable()
{
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


bool CJobTitlesTable::SelectAll(CJobTitlesArray& oJobTitlesArray)
{
 
    HRESULT hRes = m_oCommand.Open(m_oSession, _T("SELECT * FROM JOB_TITLES"));
    if (FAILED(hRes))
    {
        return false;
    }

    while (m_oCommand.MoveNext() == S_OK)
        oJobTitlesArray.Add(m_oCommand.m_recJobTitle);

    return true;
}

bool CJobTitlesTable::SelectWhereID(const long lID, JOB_TITLES& recJobTitle)
{
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM JOB_TITLES WHERE ID = %d"), lID);

    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL);
    if (FAILED(hRes))
    {
        return false;
    }

    if (m_oCommand.MoveFirst() == S_OK)
    {
        recJobTitle = m_oCommand.m_recJobTitle;
        return true;
    }
    else
    {
        return false;
    }
}


bool CJobTitlesTable::UpdateWhereID(const long lID, JOB_TITLES& recJobTitle)
{
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM JOB_TITLES WHERE ID = %d"), lID);

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    props.AddProperty(DBPROP_IRowsetScroll, true);
    props.AddProperty(DBPROP_IRowsetChange, true);
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
    if (FAILED(hRes)) {
        return false;
    }

    if (m_oCommand.MoveFirst() != S_OK) {
        return false;
    }

    if (m_oCommand.m_recJobTitle.nUpdateCounter != recJobTitle.nUpdateCounter) {
        return false;
    }
    
    m_oCommand.m_recJobTitle = recJobTitle;
    m_oCommand.m_recJobTitle.nUpdateCounter++;
    recJobTitle = m_oCommand.m_recJobTitle;

    hRes = m_oCommand.SetData(JOB_TITLES_DATA_ACCESSOR_INDEX);
    return SUCCEEDED(hRes);


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

    m_oCommand.m_recJobTitle = recJobTitle;
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
    recJobTitle = m_oCommand.m_recJobTitle;
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