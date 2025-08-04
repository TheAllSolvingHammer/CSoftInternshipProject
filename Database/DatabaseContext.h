#pragma once
#include <atldbcli.h>
#define DB_LOCATION                    "(LocalDB)\\MSSQLLocalDB"
#define DB_NAME                        "ProjectmanagementSQL"


class CDatabaseContext {
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
