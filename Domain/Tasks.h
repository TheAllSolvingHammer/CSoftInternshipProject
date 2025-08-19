#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define TASKS_MAX_NAME_SIZE         128
#define TASKS_MAX_DESCRIPTION_SIZE  256

/// <summary>
/// Структура задачи
/// </summary>
struct TASKS {
    /// <summary>
    /// Идентификатор на задача
    /// </summary>
    long lID;
    /// <summary>
    /// Брояч на актуализации
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// Наименование на задача
    /// </summary>
    TCHAR szName[TASKS_MAX_NAME_SIZE];
    /// <summary>
    /// Описание на задача
    /// </summary>
    TCHAR szDescription[TASKS_MAX_DESCRIPTION_SIZE];
    /// <summary>
    /// Проект, към който задачата принадлежи
    /// </summary>
    long lProjectID;
    /// <summary>
    /// Отговорник на задачата
    /// </summary>
    long lUserInChargeID;
    /// <summary>
    /// състояние на задачата
    /// </summary>
    short sTaskStatus;
    /// <summary>
    /// Времетраене на задачата
    /// </summary>
    int nTotalEffort;

    /// <summary>
    /// Конструктор за създаване на празна структура от задача
    /// </summary>
    TASKS() {
        ZeroMemory(this, sizeof(*this));
    }
};

typedef CArrayAutoManager<TASKS> CTasksArray;

