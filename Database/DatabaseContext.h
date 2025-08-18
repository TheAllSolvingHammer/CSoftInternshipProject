#pragma once
#include <atldbcli.h>
#include "DllExport.h"

#define DB_LOCATION            "(LocalDB)\\MSSQLLocalDB"
#define DB_NAME                "ProjectmanagementSQL"
#define MESSAGE_BOX_BODY       "Failed to get connecttion"
#define MESSAGE_BOX_TITLE      "DB connection error"

class DatabaseDLL_EXP CDatabaseContext {
public:
    CDataSource m_oDataSource;
    bool m_bConnected = false;
private:
    static CDatabaseContext* instance;
private:
    CDatabaseContext();
    ~CDatabaseContext();
public:
    static CDatabaseContext& getInstance();
    bool Connect();
    void Disconnect();
    HRESULT CreateSession(CSession& oSession);
};
