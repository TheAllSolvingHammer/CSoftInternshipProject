#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define PROJECTS_MAX_NAME_SIZE          128
#define PROJECTS_MAX_DESCRIPTION_SIZE   256

/// <summary>
/// Структура на проектите
/// </summary>
struct PROJECTS {
    /// <summary>
    /// Идентификатор на проекта
    /// </summary>
    long lID;
    /// <summary>
    /// Брояч на актуализациите
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// Наименование на проекта
    /// </summary>
    TCHAR szName[PROJECTS_MAX_NAME_SIZE];
    /// <summary>
    /// Описание на проекта
    /// </summary>
    TCHAR szDescription[PROJECTS_MAX_DESCRIPTION_SIZE];
    /// <summary>
    /// Отговорник на проекта
    /// </summary>
    long lProjectManagerID;
    /// <summary>
    /// Състояние на проекта
    /// </summary>
    short sProjectStatus;
    /// <summary>
    /// Времетраене на проекта
    /// </summary>
    int nTotalEffort;

    /// <summary>
    /// Конструктор за структурата проекти
    /// </summary>
    PROJECTS() {
        ZeroMemory(this, sizeof(*this));
    }
};


typedef CArrayAutoManager<PROJECTS> CProjectsArray;