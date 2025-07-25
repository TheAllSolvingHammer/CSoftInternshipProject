#pragma once
#include "JobTitlesAccessor.h"
#include "JobTitles.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include "DllExport.h"


class DatabaseDLL_EXP CJobTitlesTable : public CDatabaseTableConnection2<JOB_TITLES, CJobTitlesAccessor>
{
public:
    CJobTitlesTable();
    ~CJobTitlesTable();
};