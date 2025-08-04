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
	if (!m_oJobTitlesTable.SelectAll(oJobTitlesArray)) {
		return false;
	}
	return true;
}
bool CJobTitlesAppService::GetJobByID(const long lID, JOB_TITLES& recJobTitle)
{
	if (!m_oJobTitlesTable.SelectWhereID(lID, recJobTitle)) {
		return false;
	}
	return true;
}