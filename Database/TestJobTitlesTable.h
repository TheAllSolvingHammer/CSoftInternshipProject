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
    const CString m_szNewJobTitle = _T("Cloud Infrastructure Administrator");
    const long m_lSelectID = 3L;
    long m_lUpdateID = 0L;
    const CString m_szUpdatedTitle = _T("Cloud Infrastructure Lead Developer");
    long m_lDeleteID = 0L;
};