#pragma once
#include <atldbcli.h>
#include "DllExport.h"

#define DB_LOCATION            "(LocalDB)\\MSSQLLocalDB"
#define DB_NAME                "ProjectmanagementSQL"
#define MESSAGE_BOX_BODY       "Failed to get connecttion"
#define MESSAGE_BOX_TITLE      "DB connection error"

/// <summary>
/// Клас за осъществяване на връзка с база данни
/// </summary>
class DatabaseDLL_EXP CDatabaseContext {
private:
    /// <summary>
    /// Конструктор за класа връзка към база данни
    /// </summary>
    CDatabaseContext();

    /// <summary>
    /// Деструктор за класа връзка към база данни
    /// </summary>
    ~CDatabaseContext();
public:
    /// <summary>
    /// Гетър на инстанцията към класа за връзката с базата данни
    /// </summary>
    /// <returns></returns>
    static CDatabaseContext& getInstance();

    /// <summary>
    /// Свързва се към базата данни
    /// </summary>
    /// <returns>Истина при успех,неистина при неуспех</returns>
    bool Connect();

    /// <summary>
    /// Прекратява връзката към базата
    /// </summary>
    void Disconnect();

    /// <summary>
    /// Създава сесия 
    /// </summary>
    /// <param name="oSession">Сесията която ще се създаде</param>
    /// <returns></returns>
    HRESULT CreateSession(CSession& oSession);
public:
    CDataSource m_oDataSource;
    bool m_bConnected = false;
private:
    static CDatabaseContext* instance;
};
