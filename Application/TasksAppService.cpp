#include "pch.h"
#include "TasksAppService.h"
#include <TasksTable.h>

CTasksAppService::CTasksAppService() 
{

}
CTasksAppService::~CTasksAppService()
{

}
bool CTasksAppService::AddTask(TASKS& recTask)
{
	if (!CTasksTable().Insert(recTask)) {
		return false;
	}
	return true;
}
bool CTasksAppService::UpdateTask(const long lID, TASKS& recTask)
{
	if (!CTasksTable().UpdateWhereID(lID,recTask)) {
		return false;
	}
	return true;
}
bool CTasksAppService::DeleteTask(const long lID)
{
	if (!CTasksTable().DeleteWhereID(lID)) {
		return false;
	}
	return true;
}
bool CTasksAppService::UpdateProjectAndTasksDuration(PROJECTS& recProject, CTasksArray& oTasksArray)
{
	if(!CTasksTable().UpdateProjectAndTasksDuration(recProject, oTasksArray)) {
		return false;
	}
	return true;
}
