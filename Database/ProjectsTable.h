#pragma once

#include "DllExport.h"
#include <afxtempl.h>
#include "DatabaseTables.h"
#include <Projects.h>
#include "ProjectsAccessor.h"

class DatabaseDLL_EXP CProjectsTable : public CBaseTable<PROJECTS, CProjectsAccessor>
{
public:
    CProjectsTable();
    ~CProjectsTable();
};