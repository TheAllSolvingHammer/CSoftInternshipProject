#include "pch.h"
#include "TestUsersTable.h"
#include "afxwin.h"
#include <afxstr.h>

void CTestUsersTable::RunAllTests()
{
    
    TestSelectAll();
    TestSelectByID(m_lSelectID);
    TestInsert(m_lJobTitleID,m_szNewEmail,m_szNewName);
    TestUpdate(m_lUpdateID,m_szUpdatedEmail);
    TestDelete(m_lDeleteID);
}


bool CTestUsersTable::TestInsert(long lJobTitleID,const CString szNewEmail,const CString szNewName)
{
    CUsersTable oUsersTable;
    USERS recNewUser;
    recNewUser.lJobTitleID = lJobTitleID;
    wcscpy_s(recNewUser.szEmail, szNewEmail.GetString());
    wcscpy_s(recNewUser.szName, szNewName.GetString());
    recNewUser.nUpdateCounter = 0;

    if (!oUsersTable.Insert(recNewUser)) {
        AfxMessageBox(_T("Insert failed!"));
        return false;
    }

    m_lUpdateID = recNewUser.lID;
    m_lDeleteID = recNewUser.lID;

    CString oMessage;
    oMessage.Format(
        _T("Insert successful!\n")
        _T("Name: %s\n")
        _T("Email: %s\n")
        _T("JobTitleID: %ld\n")
        _T("UpdateCounter: %d\n")
        _T("ID: %ld"),
        recNewUser.szName,
        recNewUser.szEmail,
        recNewUser.lJobTitleID,
        recNewUser.nUpdateCounter,
        recNewUser.lID
    );

    AfxMessageBox(oMessage);
    return true;
}

bool CTestUsersTable::TestSelectAll()
{
    CUsersTable oUsersTable;
    CUsersArray oUsersArray;

    if (!oUsersTable.SelectAll(oUsersArray))
    {
        AfxMessageBox(_T("SelectAll test failed."));
        return false;
    }

    CString oSuccessMessage;
    oSuccessMessage.Format(_T("SelectAll test passed. Found %lld users."),static_cast<LONGLONG>(oUsersArray.GetSize()));
    AfxMessageBox(oSuccessMessage);
    return true;
    
}

bool CTestUsersTable::TestSelectByID(long lID)
{
    CUsersTable oUsersTable;
    USERS recInsertedUser;

    if (!oUsersTable.SelectWhereID(lID, recInsertedUser)) {
        AfxMessageBox(_T("SelectByID test failed."));
        return false;
    }

    CString oSuccessMessage;
    oSuccessMessage.Format(
        _T("User Found:\n")
        _T("ID: %ld\n")
        _T("Name: %s\n")
        _T("Email: %s\n")
        _T("JobTitleID: %ld\n")
        _T("UpdateCounter: %d"),
        recInsertedUser.lID,
        recInsertedUser.szName,
        recInsertedUser.szEmail,
        recInsertedUser.lJobTitleID,
        recInsertedUser.nUpdateCounter
    );
    AfxMessageBox(oSuccessMessage);
    return true;    
}

bool CTestUsersTable::TestUpdate(long lID, const CString szUpdatedEmail)
{
    CUsersTable oUsersTable;
    USERS recUser;

    if (!oUsersTable.SelectWhereID(lID, recUser)) {
        CString oMessage;
        oMessage.Format(_T("User with ID %ld not found."), lID);
        AfxMessageBox(oMessage);
        return false;
    }

    int oldCounter = recUser.nUpdateCounter;
    CString oldEmail = recUser.szEmail;

    wcscpy_s(recUser.szEmail, szUpdatedEmail);

    if (!oUsersTable.UpdateWhereID(lID, recUser)) {
        AfxMessageBox(_T("Update test failed!"));
        return false;
    }

    CString oSuccessMessage;
    oSuccessMessage.Format(
        _T("Update test successful!\n")
        _T("User ID: %ld\n")
        _T("Old Email: %s\n")
        _T("New Email: %s\n")
        _T("Old Counter: %d\n")
        _T("New Counter: %d"),
        lID,
        oldEmail.GetString(),
        szUpdatedEmail.GetString(),
        oldCounter,
        recUser.nUpdateCounter
    );

    AfxMessageBox(oSuccessMessage);
    return true;
}

bool CTestUsersTable::TestDelete(long lID)
{
    CUsersTable oUsersTable;

    if (!oUsersTable.DeleteWhereID(lID)) {
        CString oMessage;
        oMessage.Format(_T("Delete test failed! User ID: %ld not found"), lID);
        AfxMessageBox(oMessage);
        return false;
    }

    CString oSuccessMessage;
    oSuccessMessage.Format(_T("Delete test successful. User ID: %ld was deleted."), lID);
    AfxMessageBox(oSuccessMessage);
    return true;
}