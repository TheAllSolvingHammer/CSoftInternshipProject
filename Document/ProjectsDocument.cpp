#include "pch.h"
#include "ProjectsDocument.h"
#include <ProjectsAppService.h>
#include <UsersAppService.h>


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
        UpdateAllViews(NULL);
    }    
}

bool CProjectsDocument::AddProject(PROJECTS& recProject)
{
    if (!CProjectsAppService().AddProject(recProject))
    {
        return false;
    }
    LoadProjects();
}

bool CProjectsDocument::UpdateProject(const long lID,PROJECTS& recProject)
{
    if (!CProjectsAppService().UpdateProject(lID, recProject))
    {
        return false;
    }
    LoadProjects();
}



bool CProjectsDocument::DeleteProject(long lID)
{
    if (!CProjectsAppService().DeleteProject(lID))
    {
        return false;
    }
    LoadProjects();
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