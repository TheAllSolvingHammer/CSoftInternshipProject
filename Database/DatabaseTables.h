#pragma once
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

