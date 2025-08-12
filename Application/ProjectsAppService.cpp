
#include "pch.h"
#include "ProjectsAppservice.h"
#include <ProjectsTable.h>


CProjectsAppService::CProjectsAppService()
{

}

CProjectsAppService::~CProjectsAppService()
{

}

bool CProjectsAppService::GetAllProjects(CProjectsArray& oProjectsArray)
{

	if (!CProjectsTable().SelectAll(oProjectsArray)) {
		return false;
	}

	return true;
}

bool CProjectsAppService::AddProject(PROJECTS& recProject)
{
	if (!CProjectsTable().Insert(recProject)) {
		return false;
	}
	return true;
}

bool CProjectsAppService::UpdateProject(const long lID, PROJECTS& recProject)
{
	if (!CProjectsTable().UpdateWhereID(lID, recProject)) {
		return false;
	}
	return true;
}

bool CProjectsAppService::DeleteProject(const long lID)
{
	if (!CProjectsTable().DeleteWhereID(lID)) {
		return false;
	}
	return true;
}

bool CProjectsAppService::SelectTasksByProject(const long lID, CTasksArray& oTasksArray)
{
	if (!CProjectsTable().SelectTasksByProjectId(lID,oTasksArray)) {
		return false;
	}
	return true;
}


