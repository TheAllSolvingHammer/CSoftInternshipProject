#pragma once
#include <atldbcli.h>
#include "DllExport.h"

#define DB_LOCATION            "(LocalDB)\\MSSQLLocalDB"
#define DB_NAME                "ProjectmanagementSQL"
#define MESSAGE_BOX_BODY       "Failed to get connecttion"
#define MESSAGE_BOX_TITLE      "DB connection error"

/// <summary>
/// ���� �� ������������� �� ������ � ���� �����
/// </summary>
class DatabaseDLL_EXP CDatabaseContext {
private:
    /// <summary>
    /// ����������� �� ����� ������ ��� ���� �����
    /// </summary>
    CDatabaseContext();

    /// <summary>
    /// ���������� �� ����� ������ ��� ���� �����
    /// </summary>
    ~CDatabaseContext();
public:
    /// <summary>
    /// ����� �� ����������� ��� ����� �� �������� � ������ �����
    /// </summary>
    /// <returns></returns>
    static CDatabaseContext& getInstance();

    /// <summary>
    /// ������� �� ��� ������ �����
    /// </summary>
    /// <returns>������ ��� �����,�������� ��� �������</returns>
    bool Connect();

    /// <summary>
    /// ���������� �������� ��� ������
    /// </summary>
    void Disconnect();

    /// <summary>
    /// ������� ����� 
    /// </summary>
    /// <param name="oSession">������� ����� �� �� �������</param>
    /// <returns></returns>
    HRESULT CreateSession(CSession& oSession);
public:
    CDataSource m_oDataSource;
    bool m_bConnected = false;
private:
    static CDatabaseContext* instance;
};
