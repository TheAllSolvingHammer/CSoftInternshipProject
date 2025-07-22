#pragma once
#include "JobTitlesAccessor.h"
#include "JobTitles.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include "DllExport.h"


class DatabaseDLL_EXP CJobTitlesTable : public IDatabaseTable<JOB_TITLES, CJobTitlesArray>,protected CDatabaseTableConnection
{
public:
    CJobTitlesTable();
    ~CJobTitlesTable();
private:
 /*   bool OpenConnection(CDataSource& oDataSource, CSession& oSession);*/
    void CloseAll(CDataSource& oDataSource, CSession& oSession);

private:
    CCommand<CAccessor<CJobTitlesAccessor>> m_oCommand;
public:
    bool SelectAll(CJobTitlesArray& oJobTitlesArray) override;
    bool SelectWhereID(const long lID, JOB_TITLES& recJobTitle) override;
    bool UpdateWhereID(const long lID, JOB_TITLES& recJobTitle) override;
    bool Insert(JOB_TITLES& recJobTitle) override;
    bool DeleteWhereID(const long lID) override;
};