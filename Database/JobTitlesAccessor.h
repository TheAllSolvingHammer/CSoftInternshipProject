#pragma once
#include "JobTitles.h"
#include <atldbcli.h>

#define JOB_TITLES_ACCESSORS_COUNT              2
#define JOB_TITLES_IDENTITY_ACCESSOR_INDEX      0
#define JOB_TITLES_DATA_ACCESSOR_INDEX          1

#define JOB_TITLES_COLUMN_ID                    1
#define JOB_TITLES_COLUMN_TITLE_NAME            2
#define JOB_TITLES_COLUMN_UPDATE_COUNTER        3

/// <summary>
/// Аксесор на позициите
/// </summary>
class CJobTitlesAccessor {
protected:
    BEGIN_ACCESSOR_MAP(CJobTitlesAccessor, JOB_TITLES_ACCESSORS_COUNT)
        BEGIN_ACCESSOR(JOB_TITLES_IDENTITY_ACCESSOR_INDEX, true)
            COLUMN_ENTRY(JOB_TITLES_COLUMN_ID, m_recJobTitle.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(JOB_TITLES_DATA_ACCESSOR_INDEX, true)
            COLUMN_ENTRY(JOB_TITLES_COLUMN_TITLE_NAME, m_recJobTitle.szTitleName)
            COLUMN_ENTRY(JOB_TITLES_COLUMN_UPDATE_COUNTER, m_recJobTitle.nUpdateCounter)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
public:
    JOB_TITLES m_recJobTitle;
};