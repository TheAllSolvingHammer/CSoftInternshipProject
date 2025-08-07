#pragma once
#include "Projects.h"
#include <atldbcli.h>

#define PROJECTS_ACCESSORS_COUNT            2
#define PROJECTS_IDENTITY_ACCESSOR_INDEX    0
#define PROJECTS_DATA_ACCESSOR_INDEX        1

#define PROJECTS_COLUMN_ID                  1
#define PROJECTS_COLUMN_UPDATE_COUNTER      2
#define PROJECTS_COLUMN_NAME                3
#define PROJECTS_COLUMN_DESCRIPTION         4
#define PROJECTS_PROJECT_MANAGER_ID         5
#define PROJECTS_PROJECT_STATUS             6
#define PROJECTS_TOTAL_EFFORT               7

class CProjectsAccessor {
protected:
    BEGIN_ACCESSOR_MAP(CProjectsAccessor, PROJECTS_ACCESSORS_COUNT)
        BEGIN_ACCESSOR(PROJECTS_IDENTITY_ACCESSOR_INDEX, true)
            COLUMN_ENTRY(PROJECTS_COLUMN_ID, m_recProject.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(PROJECTS_DATA_ACCESSOR_INDEX, true)
            COLUMN_ENTRY(PROJECTS_COLUMN_UPDATE_COUNTER, m_recProject.nUpdateCounter)
            COLUMN_ENTRY(PROJECTS_COLUMN_NAME, m_recProject.szName)
            COLUMN_ENTRY(PROJECTS_COLUMN_DESCRIPTION, m_recProject.szDescription)
            COLUMN_ENTRY(PROJECTS_PROJECT_MANAGER_ID, m_recProject.lProjectManagerID)
            COLUMN_ENTRY(PROJECTS_PROJECT_STATUS, m_recProject.sProjectStatus)
            COLUMN_ENTRY(PROJECTS_TOTAL_EFFORT, m_recProject.nTotalEffort)
        END_ACCESSOR()
    END_ACCESSOR_MAP()

public:
    PROJECTS m_recProject;
};