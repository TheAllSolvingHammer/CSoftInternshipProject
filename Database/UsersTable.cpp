#include "pch.h"
#include "UsersTable.h"

CUsersTable::CUsersTable() : CBaseTable(m_oCommand.m_recUser, _T(USERS_TABLE_NAME))
{

}

CUsersTable::~CUsersTable()
{

}


