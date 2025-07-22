#pragma once
#include "JobTitlesTable.h"
#include "DllExport.h"
#include <afxstr.h>

class DatabaseDLL_EXP CTestJobTitlesTable
{
public:
    void RunAllTests();

private:
    bool TestInsert(const CString szNewJobTitle);
    bool TestSelectAll();
    bool TestSelectByID(long lID);
    bool TestUpdate(long lID, const CString szUodatedJobTitle);
    bool TestDelete(long lID);
private:
    const CString m_szNewJobTitle = _T("Cloud Infrastructure Engineer");
    const long m_lSelectID = 3L;
    const long m_lUpdateID = 21L;
    const CString m_szUpdatedTitle = _T("Cloud Infrastructure Lead Developer");
    const long m_lDeleteID = 21L;
};