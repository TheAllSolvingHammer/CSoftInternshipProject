#include "pch.h"
#include "ProjectsTable.h"


CProjectsTable::CProjectsTable() : CBaseTable(m_oCommand.m_recProject, _T(PROJECTS_TABLE_NAME))
{

}

CProjectsTable::CProjectsTable(CSession* pSession) : CBaseTable(m_oCommand.m_recProject, _T(PROJECTS_TABLE_NAME), *pSession)
{

}

CProjectsTable::~CProjectsTable()
{

}

bool CProjectsTable::SelectTasksByProjectId(const long lID, CTasksArray& oTasksArray)
{
 
    if (!CTasksTable().SelectByProjectId(lID, oTasksArray))
    {
        return false;
    }
    return true;
}
