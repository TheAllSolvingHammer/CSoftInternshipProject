#pragma once
#include "JobTitles.h"
#include "DllExport.h"

class ApplicationDLL_EXP CJobTitlesAppService {
public:
	CJobTitlesAppService();
	~CJobTitlesAppService();
	bool GetAllJobs(CJobTitlesArray& oJobTitlesArray);
	bool GetJobByID(const long lID,JOB_TITLES& recJobTitle);
};