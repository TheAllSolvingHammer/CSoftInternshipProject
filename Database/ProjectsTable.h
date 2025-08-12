#pragma once

#include "DllExport.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include <Projects.h>
#include "ProjectsAccessor.h"
#include "Tasks.h"
#include "TasksTable.h"

#define PROJECTS_TABLE_NAME "PROJECTS"


class DatabaseDLL_EXP CProjectsTable : public CBaseTable<PROJECTS, CProjectsAccessor>
{
public:
    CProjectsTable();
    ~CProjectsTable();
    bool SelectTasksByProjectId(const long lID, CTasksArray& oTasksArray);
};