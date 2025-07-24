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
    bool OpenRowByID(const long lID, CDataSource& oDataSource, CSession& oSession, bool bUpdatable);
    void HandleUsersArray(CUsersArray& oUsersArray);   
private:
    CDataSource m_oDataSource;
    CSession m_oSession;
    CCommand<CAccessor<CUsersAccessor>> m_oCommand;
public:
   bool SelectAll(CUsersArray& oUsersArray) override;
   bool SelectWhereID(const long lID, USERS& recUser) override;
   bool UpdateWhereID(const long lID, USERS& recUser) override;
   bool Insert(USERS& recUser) override;
   bool DeleteWhereID(const long lID) override;
};