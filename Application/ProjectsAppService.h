#pragma once
#include "DllExport.h"
#include <Projects.h>

class ApplicationDLL_EXP CProjectsAppService {
public:
	CProjectsAppService();
	~CProjectsAppService();
	bool GetAllProjects(CProjectsArray& oProjectsArray);
	bool AddProject(PROJECTS& recProject);
	bool UpdateProject(const long lID, PROJECTS& recProject);
	bool DeleteProject(const long lID);

};