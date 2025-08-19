#pragma once
#include <afxstr.h>
#include "pch.h"
#include "ArrayUtils.h"

#define JOB_TITLES_MAX_TITLE_NAME_SIZE      256

/// <summary>
/// Структура за позциите
/// </summary>
struct JOB_TITLES {
    /// <summary>
    /// ID на позицията
    /// </summary>
    long lID;
    /// <summary>
    /// Наименование на позицията
    /// </summary>
    TCHAR szTitleName[JOB_TITLES_MAX_TITLE_NAME_SIZE];
    /// <summary>
    /// Брояч на актуализациите
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// Конструктор за създаване на структура
    /// </summary>
    JOB_TITLES() {
        ZeroMemory(this, sizeof(*this));
    }
};


typedef CArrayAutoManager<JOB_TITLES> CJobTitlesArray;