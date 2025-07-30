#pragma once
#include "pch.h"
#include "JobTitleAppService.h"

CJobTitlesAppService::CJobTitlesAppService()
{

}
CJobTitlesAppService::~CJobTitlesAppService()
{

}
bool CJobTitlesAppService::GetAllJobs(CJobTitlesArray& oJobTitlesArray)
{
	return m_oJobTitlesTable.SelectAll(oJobTitlesArray);
}
bool CJobTitlesAppService::GetJobByID(const long lID, JOB_TITLES& recJobTitle)
{
	return m_oJobTitlesTable.SelectWhereID(lID, recJobTitle);
}