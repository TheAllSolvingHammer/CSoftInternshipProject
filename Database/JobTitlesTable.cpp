#include "pch.h"
#include "JobTitlesTable.h"
#include "afxwin.h"


CJobTitlesTable::CJobTitlesTable()
{

}

CJobTitlesTable::~CJobTitlesTable()
{

}


void CJobTitlesTable::CloseAll(CDataSource& oDataSource, CSession& oSession)
{
    m_oCommand.Close();
    oSession.Close();
    oDataSource.Close();
}

bool CJobTitlesTable::SelectAll(CJobTitlesArray& oJobTitlesArray)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
    {
        return false;
    }

    HRESULT hRes = m_oCommand.Open(oSession, _T("SELECT * FROM JOB_TITLES"));
    if (FAILED(hRes))
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    while (m_oCommand.MoveNext() == S_OK)
        oJobTitlesArray.Add(m_oCommand.m_recJobTitle);

    CloseAll(oDataSource, oSession);
    return true;
}

bool CJobTitlesTable::SelectWhereID(const long lID, JOB_TITLES& recJobTitle)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
    {
        return false;
    }

    //structure name extract
    //iznasqne oshte na abstraction
    //m_oCommand opravi i iznesi ako mojesh
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM JOB_TITLES WHERE ID = %d"), lID);

    HRESULT hRes = m_oCommand.Open(oSession, strSQL);
    if (FAILED(hRes))
    {
        CloseAll(oDataSource, oSession);
        return false;
    }

    if (m_oCommand.MoveFirst() == S_OK)
    {
        recJobTitle = m_oCommand.m_recJobTitle;
        CloseAll(oDataSource, oSession);
        return true;
    }
    else
    {
        CloseAll(oDataSource, oSession);
        return false;
    }
}


bool CJobTitlesTable::UpdateWhereID(const long lID, const JOB_TITLES& recJobTitle)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
    {
        return false;
    }

    CString strSQL;
    strSQL.Format(_T("SELECT * FROM JOB_TITLES WHERE ID = %d"), lID);

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    props.AddProperty(DBPROP_IRowsetScroll, true);
    props.AddProperty(DBPROP_IRowsetChange, true);
    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

    HRESULT hRes = m_oCommand.Open(oSession, strSQL, &props);
    if (FAILED(hRes)) {
        CloseAll(oDataSource, oSession);
        return false;
    }

    if (m_oCommand.MoveFirst() == S_OK) {
        if (m_oCommand.m_recJobTitle.nUpdateCounter != recJobTitle.nUpdateCounter) {
            CloseAll(oDataSource, oSession);
            return false;
        }

        m_oCommand.m_recJobTitle = recJobTitle;
        m_oCommand.m_recJobTitle.nUpdateCounter++;

        hRes = m_oCommand.SetData(JOB_TITLES_DATA_ACCESSOR_INDEX);
        CloseAll(oDataSource, oSession);
        return SUCCEEDED(hRes);
    }

    CloseAll(oDataSource, oSession);
    return false;
}

bool CJobTitlesTable::Insert(JOB_TITLES& recJobTitle)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
    {
        return false;
    }

    CString strSQL = _T("SELECT * FROM JOB_TITLES");

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

    m_oCommand.m_recJobTitle = recJobTitle;
    hRes = m_oCommand.Insert(JOB_TITLES_DATA_ACCESSOR_INDEX);
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
    recJobTitle = m_oCommand.m_recJobTitle;
    CloseAll(oDataSource, oSession);
    return SUCCEEDED(hRes);
}

bool CJobTitlesTable::DeleteWhereID(const long lID)
{
    CDataSource oDataSource;
    CSession oSession;

    if (!OpenConnection(oDataSource, oSession))
        return false;

    CString strSQL;
    strSQL.Format(_T("SELECT * FROM JOB_TITLES WHERE ID = %d"), lID);

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