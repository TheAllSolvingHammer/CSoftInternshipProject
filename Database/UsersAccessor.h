#pragma once
#include "Users.h"
#include <atldbcli.h>

#define USERS_ACCESSORS_COUNT 2
#define USERS_IDENTITY_ACCESSOR_INDEX 0
#define USERS_DATA_ACCESSOR_INDEX 1

#define USERS_COLUMN_ID             1
#define USERS_COLUMN_UPDATE_COUNTER 2
#define USERS_COLUMN_NAME           3
#define USERS_COLUMN_EMAIL          4
#define USERS_COLUMN_JOB_TITLE_ID   5

class CUsersAccessor {
protected:
    BEGIN_ACCESSOR_MAP(CUsersAccessor, USERS_ACCESSORS_COUNT)
        BEGIN_ACCESSOR(USERS_IDENTITY_ACCESSOR_INDEX, true)
        COLUMN_ENTRY(USERS_COLUMN_ID, m_recUser.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(USERS_DATA_ACCESSOR_INDEX, true)
        COLUMN_ENTRY(USERS_COLUMN_UPDATE_COUNTER, m_recUser.nUpdateCounter)
        COLUMN_ENTRY(USERS_COLUMN_NAME, m_recUser.szName)
        COLUMN_ENTRY(USERS_COLUMN_EMAIL, m_recUser.szEmail)
        COLUMN_ENTRY(USERS_COLUMN_JOB_TITLE_ID, m_recUser.lJobTitleID)
        END_ACCESSOR()
    END_ACCESSOR_MAP()

public:
    USERS m_recUser;
};