#pragma once
#include "JobTitlesAccessor.h"
#include "JobTitles.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include "DllExport.h"

#define JOB_TITLES_TABLE_NAME "JOB_TITLES"

class DatabaseDLL_EXP CJobTitlesTable : public CBaseTable<JOB_TITLES, CJobTitlesAccessor>
{
public:
    CJobTitlesTable();
    ~CJobTitlesTable();
};