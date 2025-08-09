#pragma once
#include "pch.h"
#include "JobTitleAppService.h"
#include "ArrayManager.h"
#include <JobTitlesTable.h>


CJobTitlesAppService::CJobTitlesAppService()
{
	
}
CJobTitlesAppService::~CJobTitlesAppService()
{

}
bool CJobTitlesAppService::GetAllJobs(CJobTitlesArray& oJobTitlesArray)
{
	if (!CJobTitlesTable().SelectAll(oJobTitlesArray)) {
		return false;
	}
	return true;
}
bool CJobTitlesAppService::GetJobByID(const long lID, JOB_TITLES& recJobTitle)
{
	if (!CJobTitlesTable().SelectWhereID(lID, recJobTitle)) {
		return false;
	}
	return true;
}