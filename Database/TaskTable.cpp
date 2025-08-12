#include "pch.h"
#include "TasksTable.h"

CTasksTable::CTasksTable() : CBaseTable(m_oCommand.m_recTask, _T(TASKS_TABLE_NAME))
{

}

CTasksTable::~CTasksTable()
{

}