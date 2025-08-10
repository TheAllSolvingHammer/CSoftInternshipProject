#pragma once
#include "DllExport.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include <Tasks.h>
#include "TasksAccessor.h"

#define TASKS_TABLE_NAME "TASKS"


class DatabaseDLL_EXP CTasksTable : public CBaseTable<TASKS,CTasksAccessor>
{
public:
    CTasksTable();
    ~CTasksTable();
    
};