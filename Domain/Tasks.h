#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define TASKS_MAX_NAME_SIZE         128
#define TASKS_MAX_DESCRIPTION_SIZE  256

struct TASKS {
    long lID;
    int nUpdateCounter;
    TCHAR szName[TASKS_MAX_NAME_SIZE];
    TCHAR szDescription[TASKS_MAX_DESCRIPTION_SIZE];
    long lProjectID;
    long lUserInChargeID;
    short sTaskStatus;
    int nTotalEffort;

    TASKS() {
        ZeroMemory(this, sizeof(*this));
    }
};

//typedef CTypedPtrArray<CArrayAutoManager, TASKS*> CTasksArray;
typedef CArrayAutoManager_2<TASKS> CTasksArray;

