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
template<typename TRecord,typename TArray,typename TAccessor>
class CDatabaseTableConnection2
{
public:
    CString m_oTableName;
    CDataSource m_oDataSource;
    CSession m_oSession;
    CCommand<CAccessor<TAccessor>> m_oCommand;

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

    bool SelectAll(TArray& oArray)
    {
        CString strSQL;
        strSQL.Format(_T("SELECT * FROM %s"), m_oTableName);

        HRESULT hRes = m_oCommand.Open(m_oSession, strSQL);
        if (FAILED(hRes))
            return false;

        while (m_oCommand.MoveNext() == S_OK)
        {
            TRecord* pRecord = new TRecord();
            *pRecord = m_oCommand.m_recRecord;
            oArray.Add(pRecord);
        }

        return true;
    }

    bool SelectWhereID(const long lID, TRecord& rec)
    {
        CString strSQL;
        strSQL.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_oTableName, lID);

        HRESULT hRes = m_oCommand.Open(m_oSession, strSQL);
        if (FAILED(hRes))
        {
            return false;
        }

        if (m_oCommand.MoveFirst() == S_OK)
        {
            rec = m_oCommand.m_recRecord;
            return true;
        }
        else
        {
            return false;
        }
    }
    

};

