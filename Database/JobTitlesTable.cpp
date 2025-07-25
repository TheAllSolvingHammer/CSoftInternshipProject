#include "pch.h"
#include "JobTitlesTable.h"
#include "afxwin.h"


CJobTitlesTable::CJobTitlesTable() : CDatabaseTableConnection2 (m_oCommand.m_recJobTitle, _T("JOB_TITLES"))
{
    //super(var1,var2)
    if (!OpenConnection(m_oDataSource, m_oSession))
    {
        AfxMessageBox(_T("Error connecting to the database"));
    }
}

CJobTitlesTable::~CJobTitlesTable()
{
    m_oCommand.Close();
    m_oSession.Close();
    m_oDataSource.Close();
}




