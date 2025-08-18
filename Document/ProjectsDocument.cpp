#include "pch.h"
#include "ProjectsDocument.h"
#include <ProjectsAppService.h>
#include <UsersAppService.h>
#include <TasksAppService.h>


IMPLEMENT_DYNCREATE(CProjectsDocument, CDocument)


CProjectsDocument::CProjectsDocument()
{
}

CProjectsDocument::~CProjectsDocument()
{
    
}

BOOL CProjectsDocument::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    LoadProjects();
    return TRUE;
}

void CProjectsDocument::OnCloseDocument()
{
    CDocument::OnCloseDocument();
}

void CProjectsDocument::LoadProjects()
{
    m_oProjectsArray.ClearAll();

    if (!CProjectsAppService().GetAllProjects(m_oProjectsArray)) {
        AfxMessageBox(MSG_ERR_LOAD_USERS);
    }
    else
    {
        UpdateAllViews(NULL, HINT_NONE);
    }    
}

bool CProjectsDocument::AddProject(PROJECTS& recProject)
{
    if (!CProjectsAppService().AddProject(recProject))
    {
        return false;
    }
    PROJECTS* pNewProject = new PROJECTS;
    *pNewProject = recProject;
    m_oProjectsArray.Add(pNewProject);
    UpdateAllViews(nullptr, HINT_PROJECT_ADDED);
    return true;
}

bool CProjectsDocument::UpdateProject(PROJECTS& recProject, CTasksArray& oTasksArray, CTasksArray& oUpdatedTasksArray, CTasksArray& oDeletedTasksArray)
{
    if (!CTasksAppService().UpdateProjectAndTasksDuration(recProject, oTasksArray, oUpdatedTasksArray, oDeletedTasksArray))
    {
        return false;
    }
    LoadSingleProject(recProject);
    UpdateAllViews(NULL,HINT_PROJECT_UPDATED);
    return true;
}


bool CProjectsDocument::DeleteProject(long lID)
{
    if (!CProjectsAppService().DeleteProject(lID))
    {
        return false;
    }
    DeleteSingleProject(lID);
    UpdateAllViews(NULL, HINT_PROJECT_DELETED);
    return true;
}

CProjectsArray& CProjectsDocument::GetProjectsArray()
{
    return this->m_oProjectsArray;
}

bool CProjectsDocument::GetUser(const long lID, USERS& recUser)
{
    if (!CUsersAppService().FindUserByID(lID, recUser)) 
    {
        return false;
    }

    return true;
}

bool CProjectsDocument::GetAllUsers(CUsersArray& oUsersArray)
{
    if (!CUsersAppService().GetAllUsers(oUsersArray)) 
    {
        return false;
    }
    return true;
}

bool CProjectsDocument::GetTasksByProject(const long lID, CTasksArray& oTasksArray)
{   
    if (!CProjectsAppService().SelectTasksByProject(lID, oTasksArray))
    {
        return false;
    }
    return true;
}

void CProjectsDocument::LoadSingleProject(PROJECTS& recProject) {
    for (INT_PTR i = 0;i < m_oProjectsArray.GetCount();i++) {
        PROJECTS* pRecProject = m_oProjectsArray.GetAt(i);
        if (pRecProject && pRecProject->lID == recProject.lID) {
            *pRecProject = recProject;
            break;
        }
    }
}

void CProjectsDocument::DeleteSingleProject(const long lID) {
    for (INT_PTR i = 0;i < m_oProjectsArray.GetCount();i++) {
        PROJECTS* pRecProject = m_oProjectsArray.GetAt(i);
        if (pRecProject && pRecProject->lID == lID) {
            delete pRecProject;
            m_oProjectsArray.RemoveAt(i);
            break;
        }
    }
}