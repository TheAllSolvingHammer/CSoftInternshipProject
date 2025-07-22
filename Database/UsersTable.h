#pragma once

#include "UsersAccessor.h"
#include "Users.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include "DllExport.h"


class DatabaseDLL_EXP CUsersTable: public IDatabaseTable<USERS,CUsersArray>, protected CDatabaseTableConnection
{
public:
    CUsersTable();
    ~CUsersTable();
private:
    void CloseAll(CDataSource& oDataSource, CSession& oSession);

private:
    CCommand<CAccessor<CUsersAccessor>> m_oCommand;
public:
   bool SelectAll(CUsersArray& oUsersArray) override;
   bool SelectWhereID(const long lID, USERS& recUser) override;
   bool UpdateWhereID(const long lID, USERS& recUser) override;
   bool Insert(USERS& recUser) override;
   bool DeleteWhereID(const long lID) override;
};