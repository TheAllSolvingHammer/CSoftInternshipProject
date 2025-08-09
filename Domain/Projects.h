#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define PROJECTS_MAX_NAME_SIZE          128
#define PROJECTS_MAX_DESCRIPTION_SIZE   256

struct PROJECTS {
    long lID;
    int nUpdateCounter;
    TCHAR szName[PROJECTS_MAX_NAME_SIZE];
    TCHAR szDescription[PROJECTS_MAX_DESCRIPTION_SIZE];
    long lProjectManagerID;
    short sProjectStatus;
    int nTotalEffort;

    PROJECTS() {
        ZeroMemory(this, sizeof(*this));
    }
};

typedef CTypedPtrArray<CArrayAutoManager, PROJECTS*> CProjectsArray;