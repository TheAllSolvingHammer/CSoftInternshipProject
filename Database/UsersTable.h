#pragma once

#include "UsersAccessor.h"
#include "Users.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include "DllExport.h"


class DatabaseDLL_EXP CUsersTable: public CBaseTable<USERS,CUsersAccessor>
{
public:
    CUsersTable();
    ~CUsersTable();  
};