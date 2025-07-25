#pragma once
#include "JobTitlesAccessor.h"
#include "JobTitles.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include "DllExport.h"


class DatabaseDLL_EXP CJobTitlesTable : protected CDatabaseTableConnection2<JOB_TITLES, CJobTitlesArray,CJobTitlesAccessor>
{
public:
    CJobTitlesTable();
    ~CJobTitlesTable();
//private:
//    /*CCommand<CAccessor<CJobTitlesAccessor>> m_oCommand;*/
//    CDataSource m_oDataSource;
//    CSession m_oSession;
public:
    bool SelectAllUsers(CJobTitlesArray& oArray);
    bool SelectSingle(const long lID, JOB_TITLES& rec);
    bool UpdateWhereID(const long lID, JOB_TITLES& recJobTitle);
    bool Insert(JOB_TITLES& recJobTitle);
    bool DeleteWhereID(const long lID);
};