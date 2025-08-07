#pragma once
#include "Tasks.h"
#include <atldbcli.h>

#define TASKS_ACCESSORS_COUNT           2
#define TASKS_IDENTITY_ACCESSOR_INDEX   0
#define TASKS_DATA_ACCESSOR_INDEX       1

#define TASKS_COLUMN_ID                 1
#define TASKS_COLUMN_UPDATE_COUNTER     2
#define TASKS_COLUMN_NAME               3
#define TASKS_COLUMN_DESCRIPTION        4
#define TASKS_COLUMN_PROJECT_ID         5
#define TASKS_COLUMN_USER_IN_CHARGE_ID  6
#define TASKS_COLUMN_TASK_STATUS        7
#define TASKS_COLUMN_TOTAL_EFFORT       8

class CTasksAccessor {
protected:
    BEGIN_ACCESSOR_MAP(CTasksAccessor, TASKS_ACCESSORS_COUNT)
        BEGIN_ACCESSOR(TASKS_IDENTITY_ACCESSOR_INDEX, true)
            COLUMN_ENTRY(TASKS_COLUMN_ID, m_recTask.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(TASKS_DATA_ACCESSOR_INDEX, true)
            COLUMN_ENTRY(TASKS_COLUMN_UPDATE_COUNTER, m_recTask.nUpdateCounter)
            COLUMN_ENTRY(TASKS_COLUMN_NAME, m_recTask.szName)
            COLUMN_ENTRY(TASKS_COLUMN_DESCRIPTION, m_recTask.szDescription)
            COLUMN_ENTRY(TASKS_COLUMN_PROJECT_ID, m_recTask.lProjectID)
            COLUMN_ENTRY(TASKS_COLUMN_USER_IN_CHARGE_ID, m_recTask.lUserInChargeID)
            COLUMN_ENTRY(TASKS_COLUMN_TASK_STATUS, m_recTask.sTaskStatus)
            COLUMN_ENTRY(TASKS_COLUMN_TOTAL_EFFORT, m_recTask.nTotalEffort)
        END_ACCESSOR()
    END_ACCESSOR_MAP()

public:
    TASKS m_recTask;
};
