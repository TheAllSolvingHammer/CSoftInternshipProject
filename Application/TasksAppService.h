#pragma once
#include "Tasks.h"
#include "DllExport.h"
#include <Projects.h>

class ApplicationDLL_EXP CTasksAppService {
public:
	CTasksAppService();
	~CTasksAppService();
	bool AddTask(TASKS& recTask);
	bool UpdateTask(const long lID, TASKS& recTask);
	bool DeleteTask(const long lID);
	bool UpdateProjectAndTasksDuration(PROJECTS& recProject, CTasksArray& oTasksArray);

};