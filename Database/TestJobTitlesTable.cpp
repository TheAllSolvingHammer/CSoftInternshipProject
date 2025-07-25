#pragma once
#include "pch.h"
#include "TestJobTitlesTable.h"
#include "afxwin.h"
#include <afxstr.h>

void CTestJobTitlesTable::RunAllTests()
{
    TestSelectAll();
    TestSelectByID(m_lSelectID);
    TestInsert(m_szNewJobTitle);
    TestUpdate(m_lUpdateID, m_szUpdatedTitle);
    TestDelete(m_lDeleteID);
}

bool CTestJobTitlesTable::TestInsert(const CString szNewTitle)
{
    CJobTitlesTable oJobTitlesTable;
    JOB_TITLES recNewJobTitle;
    wcscpy_s(recNewJobTitle.szTitleName, szNewTitle);

    if (!oJobTitlesTable.Insert(recNewJobTitle)) {
        AfxMessageBox(_T("Insert failed!"));
        return false;
    }
    m_lUpdateID = recNewJobTitle.lID;
    m_lDeleteID = recNewJobTitle.lID;
    CString oSuccessMessage;
    oSuccessMessage.Format(_T("Insert successful. New Job Title ID: %d"), recNewJobTitle.lID);
    AfxMessageBox(oSuccessMessage);
    return true;
}

bool CTestJobTitlesTable::TestSelectAll()
{
    CJobTitlesTable oJobTitlesTable;
    CJobTitlesArray oJobTitlesArray;

    if (!oJobTitlesTable.SelectAllUsers(oJobTitlesArray)) {
        AfxMessageBox(_T("SelectAll test failed."));
        return false;
    }

    CString oSuccessMessage;
    oSuccessMessage.Format(_T("SelectAll test passed. Found %lld job titles."), static_cast<LONGLONG>(oJobTitlesArray.GetSize()));
    AfxMessageBox(oSuccessMessage);
    return true;
}

bool CTestJobTitlesTable::TestSelectByID(long lID)
{
    CJobTitlesTable oJobTitlesTable;
    JOB_TITLES recJobTitle;

    if (!oJobTitlesTable.SelectSingle(lID, recJobTitle)) {
        AfxMessageBox(_T("SelectByID failed. ID not found."));
        return false;
    }

    CString oSuccessMessage;
    oSuccessMessage.Format(_T("SelectByID passed. ID: %ld, Title: %s"), recJobTitle.lID, recJobTitle.szTitleName);
    AfxMessageBox(oSuccessMessage);
    return true;
}

bool CTestJobTitlesTable::TestUpdate(long lID, const CString szUpdatedJobTitle)
{
    CJobTitlesTable oJobTitlesTable;
    JOB_TITLES recJobTitle;

    if (!oJobTitlesTable.SelectSingle(lID, recJobTitle)) {
        AfxMessageBox(_T("Update failed. Record not found."));
        return false;
    }

    wcscpy_s(recJobTitle.szTitleName, szUpdatedJobTitle);
    int oldCounter = recJobTitle.nUpdateCounter;

    if (!oJobTitlesTable.UpdateWhereID(lID, recJobTitle)) {
        AfxMessageBox(_T("Update failed."));
        return false;
    }

    CString oSucessMessage;
    oSucessMessage.Format(_T("Update successful. New Title: %s"), recJobTitle.szTitleName);
    AfxMessageBox(oSucessMessage);
    return true;
}

bool CTestJobTitlesTable::TestDelete(long lID)
{
    CJobTitlesTable oJobTitlesTable;
    if (!oJobTitlesTable.DeleteWhereID(lID)) {
        AfxMessageBox(_T("Delete failed."));
        return false;
    }
    CString oSucessMessage;
    oSucessMessage.Format(_T("Delete successful for ID: %ld"), lID);
    AfxMessageBox(oSucessMessage);
    return true;
}