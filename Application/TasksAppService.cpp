#include "pch.h"
#include "TasksAppService.h"
#include <TasksTable.h>
#include <ProjectsTable.h>

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

bool CTasksAppService::UpdateProjectAndTasksDuration(PROJECTS& recProject, CTasksArray& oTasksArray, CTasksArray& oUpdatedTasksArray, CTasksArray& oDeletedTasksArray)
{
    HRESULT hRes;
    CSession oSession;
    CDatabaseContext::getInstance().CreateSession(oSession);
    hRes = oSession.StartTransaction();
    if (FAILED(hRes))
    {
        AfxMessageBox(_T(ERR_TRANSACTION_START), MB_ICONERROR);
        return false;
    }

    for (INT_PTR i = 0; i < oUpdatedTasksArray.GetSize(); i++)
    {
        TASKS* pTask = oUpdatedTasksArray.GetAt(i);
        if (!pTask)
            continue;

        if (pTask->lID == 0)
        {
            if (!CTasksTable().Insert(*pTask))
            {
                oSession.Abort();
                return false;
            }
        }
        else
        {
            if (!CTasksTable().UpdateWhereID(pTask->lID, *pTask))
            {
                oSession.Abort();
                return false;
            }
        }

    }

    for (INT_PTR i = 0; i < oDeletedTasksArray.GetCount(); i++)
    {
        TASKS* pTask = oDeletedTasksArray.GetAt(i);
        if (!pTask)
            continue;

        if (pTask->lID != 0)
        {
            if (!CTasksTable().DeleteWhereID(pTask->lID))
            {
                oSession.Abort();
                return false;
            }
        }
    }

    int nDuration = 0;
    for (INT_PTR i = 0;i < oTasksArray.GetCount();i++) 
    {
        TASKS* pRecTask = oTasksArray.GetAt(i);
        if (pRecTask) {
            nDuration += pRecTask->nTotalEffort;
        }
    }

    recProject.nTotalEffort = nDuration;

    if (!CProjectsTable().UpdateWhereID(recProject.lID, recProject))
    {
        oSession.Abort();
        return false;
    }

    hRes = oSession.Commit();
    if (FAILED(hRes))
    {
        AfxMessageBox(_T(ERR_TRANSACTION_COMMIT), MB_ICONERROR);
        return false;
    }

    return true;
}
