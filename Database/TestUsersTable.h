#pragma once
#include "UsersTable.h"
#include "DllExport.h"
#include <afxstr.h>

class DatabaseDLL_EXP CTestUsersTable 
{
public:
    void RunAllTests();

private:
    bool TestInsert(long lJobTitleID, const CString szNewEmail, const CString szNewName);
    bool TestSelectAll();
    bool TestSelectByID(long lID);
    bool TestUpdate(long lID, const CString szUpdatedEmail);
    bool TestDelete(long lID);
private:
    const long m_lJobTitleID=5L;
    const CString m_szNewEmail = _T("emai2332glfff2@gmail.com");
    const CString m_szNewName = _T("Name");
    const long m_lSelectID = 3L;
    const long m_lUpdateID = 23L;
    const CString m_szUpdatedEmail = _T("mynewemail@notgmail.com");
    const long m_lDeleteID = 29L;
};