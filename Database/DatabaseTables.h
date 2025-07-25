#pragma once
#include "BaseAccessor.h"
#include <afxtempl.h>

#define DB_LOCATION     "(LocalDB)\\MSSQLLocalDB"
#define DB_NAME         "ProjectmanagementSQL"

template<typename TRecord, typename TTypeArray>
class IDatabaseTable
{
public:
    virtual ~IDatabaseTable() {
    }
    virtual bool SelectAll(TTypeArray& oArray) = 0;
    virtual bool SelectWhereID(const long lID, TRecord& rec) = 0;
    virtual bool UpdateWhereID(const long lID, TRecord& rec) = 0;
    virtual bool Insert(TRecord& rec) = 0;
    virtual bool DeleteWhereID(const long lID) = 0;
    
};

class CDatabaseTableConnection
{
protected:
    bool OpenConnection(CDataSource& oDataSource, CSession& oSession)
    {
        CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
        oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T(DB_LOCATION));
        oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
        oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T(DB_NAME));
        oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
        oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
        oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
        //MSOLEDBSQL
        //SQLOLEDB.1
        HRESULT hRes = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);
        if (FAILED(hRes))
        {
            MessageBox(NULL, _T("Failed to get connecttion"), _T("DB connection error"), MB_ICONWARNING);
            return false;
        }

        hRes = oSession.Open(oDataSource);
        if (FAILED(hRes))
        {
            oDataSource.Close();
            return false;
        }

        return true;
    }

};
template<typename TRecord,typename TAccessor>
class CDatabaseTableConnection2
{
public:
    CString m_oTableName;
    CDataSource m_oDataSource;
    CSession m_oSession;
    TRecord& m_recRecord;
    CCommand<CAccessor<TAccessor>> m_oCommand;
    CDatabaseTableConnection2(TRecord& recRecord,const CString oTableName) 
        : m_recRecord(recRecord)
    {
        this->m_oTableName = oTableName;
    }
    ~CDatabaseTableConnection2()
    {
        m_oCommand.Close();
        m_oSession.Close();
        m_oDataSource.Close();
    }
protected:
    bool OpenConnection(CDataSource& oDataSource, CSession& oSession)
    {
        
        CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
        oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T(DB_LOCATION));
        oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
        oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T(DB_NAME));
        oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
        oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
        oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
        //MSOLEDBSQL
        //SQLOLEDB.1
        HRESULT hRes = oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);
        if (FAILED(hRes))
        {
            MessageBox(NULL, _T("Failed to get connecttion"), _T("DB connection error"), MB_ICONWARNING);
            return false;
        }

        hRes = oSession.Open(oDataSource);
        if (FAILED(hRes))
        {
            oDataSource.Close();
            return false;
        }

        return true;
    }

public:

    bool SelectAll(CTypedPtrArray<CPtrArray, TRecord*>& oArray)
    {
        CString strSQL;
        strSQL.Format(_T("SELECT * FROM %s"), m_oTableName.GetString());

        CDBPropSet props(DBPROPSET_ROWSET);
        props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
        props.AddProperty(DBPROP_IRowsetScroll, true);
        props.AddProperty(DBPROP_IRowsetChange, true);
        props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

        HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
        if (FAILED(hRes))
            return false;

        while (m_oCommand.MoveNext() == S_OK)
        {
            TRecord* pRecord = new TRecord();
            *pRecord = m_recRecord;
            oArray.Add(pRecord);
        }

        return true;
    }

    bool SelectWhereID(const long lID, TRecord& rec)
    {
        CString strSQL;
        strSQL.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_oTableName.GetString(), lID);

        HRESULT hRes = m_oCommand.Open(m_oSession, strSQL);
        if (FAILED(hRes))
        {
            return false;
        }

        if (m_oCommand.MoveFirst() == S_OK)
        {
            rec = m_recRecord;
            return true;
        }
        else
        {
            return false;
        }
    }
    //fix naming
    bool UpdateWhereID(const long lID, TRecord& rec)
    {
        /*CString strSQL;
        strSQL.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_oTableName.GetString(), lID);

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

        if (m_oCommand.m_recRecord.nUpdateCounter != rec.nUpdateCounter) {
            return false;
        }

        m_oCommand.m_recRecord = rec;
        m_oCommand.m_recRecord.nUpdateCounter++;
        rec = m_oCommand.m_recRecord;

        hRes = m_oCommand.SetData(JOB_TITLES_DATA_ACCESSOR_INDEX);
        return SUCCEEDED(hRes);*/
        return true;


    }
    

};

