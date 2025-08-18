#pragma once
#include "DllExport.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include <Tasks.h>
#include "TasksAccessor.h"

#include "Projects.h"

#define TASKS_TABLE_NAME "TASKS"
#define QUERY_SELECT_TASKS_BY_PROJECT_ID _T("SELECT * FROM [TASKS] WHERE PROJECT_ID = %d")


class DatabaseDLL_EXP CTasksTable : public CBaseTable<TASKS,CTasksAccessor>
{
public:
    CTasksTable();
    ~CTasksTable();
    bool SelectByProjectId(const long lID, CTasksArray& oTasksArray);
};