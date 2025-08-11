#include "pch.h"
#include "ProjectsDocument.h"


IMPLEMENT_DYNCREATE(CProjectsDocument, CDocument)


CProjectsDocument::CProjectsDocument()
{
}

CProjectsDocument::~CProjectsDocument()
{
    m_oProjectsArray.ClearAll();
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
        AfxMessageBox(_T("Failed to load users."));
    }
    else
    {
        UpdateAllViews(NULL);
    }    
}

bool CProjectsDocument::AddProject(PROJECTS& project)
{
    if (!CProjectsAppService().AddProject(project))
    {
        return false;
    }
    LoadProjects();
}

bool CProjectsDocument::UpdateProject(const long lID,PROJECTS& project)
{
    if (!CProjectsAppService().UpdateProject(lID, project))
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