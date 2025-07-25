#pragma once
#include <afxstr.h>
#include "pch.h"

#define JOB_TITLES_MAX_TITLE_NAME_SIZE      256

struct JOB_TITLES {
    long lID;
    TCHAR szTitleName[JOB_TITLES_MAX_TITLE_NAME_SIZE];
    int nUpdateCounter;
    JOB_TITLES() {
        ZeroMemory(this, sizeof(*this));
    }
};

typedef CTypedPtrArray<CPtrArray, JOB_TITLES*>CJobTitlesArray;