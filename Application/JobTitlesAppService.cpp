#pragma once
#include "pch.h"
#include "JobTitleAppService.h"
#include <ArrayManager.h>


CJobTitlesAppService::CJobTitlesAppService()
{
	
}
CJobTitlesAppService::~CJobTitlesAppService()
{

}
bool CJobTitlesAppService::GetAllJobs(CJobTitlesArray& oJobTitlesArray)
{
	CJobTitlesArray* pNewJobTitlesArray = new CJobTitlesArray();
	if (!m_oJobTitlesTable.SelectAll(*pNewJobTitlesArray)) {
		delete pNewJobTitlesArray;
		return false;
	}
	CArrayManager::getInstance().AddCollection(COLLECTION_JOB_TITLES, pNewJobTitlesArray);
	return true;
}
bool CJobTitlesAppService::GetJobByID(const long lID, JOB_TITLES& recJobTitle)
{
	if (!m_oJobTitlesTable.SelectWhereID(lID, recJobTitle)) {
		return false;
	}
	return true;
}