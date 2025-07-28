#include "pch.h"
#include "DatabaseContext.h"


CDatabaseContext::CDatabaseContext() {

}

CDatabaseContext::~CDatabaseContext()
{
    Disconnect();
}

CDatabaseContext& CDatabaseContext::getInstance() {
    if (instance == nullptr) {
        instance = new CDatabaseContext();
    }
    return *instance;
}

bool CDatabaseContext::Connect() {
    if (m_bConnected)
        return true;

    CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
    oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T(DB_LOCATION));
    oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
    oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T(DB_NAME));
    oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
    oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
    oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
    //MSOLEDBSQL
    //SQLOLEDB.1
    HRESULT hRes = m_oDataSource.Open(_T("MSOLEDBSQL"), &oDBPropSet);
    if (FAILED(hRes))
    {
        MessageBox(NULL, _T("Failed to get connecttion"), _T("DB connection error"), MB_ICONWARNING);
        return false;
    }
    hRes = m_oSession.Open(m_oDataSource);
    if (FAILED(hRes))
    {
        m_oDataSource.Close();
        return false;
    }
    m_bConnected = true;
    return true;
}

void CDatabaseContext::Disconnect() {
    m_oSession.Close();
    m_oDataSource.Close();
    m_bConnected = false;
}
CDatabaseContext* CDatabaseContext::instance = nullptr;