#pragma once
#include "DllExport.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include <Tasks.h>
#include "TasksAccessor.h"

class DatabaseDLL_EXP CTasksTable : public CBaseTable<TASKS,CTasksAccessor>
{
public:
    CTasksTable();
    ~CTasksTable();
    
};