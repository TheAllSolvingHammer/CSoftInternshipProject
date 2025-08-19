#include "pch.h"
#include "JobTitlesTable.h"

CJobTitlesTable::CJobTitlesTable() : CBaseTable (m_oCommand.m_recJobTitle, _T(JOB_TITLES_TABLE_NAME))
{

}

CJobTitlesTable::CJobTitlesTable(CSession* pSession) : CBaseTable(m_oCommand.m_recJobTitle, _T(JOB_TITLES_TABLE_NAME), *pSession)
{

}

CJobTitlesTable::~CJobTitlesTable()
{
  
}






