#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define TASKS_MAX_NAME_SIZE         128
#define TASKS_MAX_DESCRIPTION_SIZE  256

/// <summary>
/// ��������� ������
/// </summary>
struct TASKS {
    /// <summary>
    /// ������������� �� ������
    /// </summary>
    long lID;
    /// <summary>
    /// ����� �� ������������
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// ������������ �� ������
    /// </summary>
    TCHAR szName[TASKS_MAX_NAME_SIZE];
    /// <summary>
    /// �������� �� ������
    /// </summary>
    TCHAR szDescription[TASKS_MAX_DESCRIPTION_SIZE];
    /// <summary>
    /// ������, ��� ����� �������� ����������
    /// </summary>
    long lProjectID;
    /// <summary>
    /// ���������� �� ��������
    /// </summary>
    long lUserInChargeID;
    /// <summary>
    /// ��������� �� ��������
    /// </summary>
    short sTaskStatus;
    /// <summary>
    /// ����������� �� ��������
    /// </summary>
    int nTotalEffort;

    /// <summary>
    /// ����������� �� ��������� �� ������ ��������� �� ������
    /// </summary>
    TASKS() {
        ZeroMemory(this, sizeof(*this));
    }
};

typedef CArrayAutoManager<TASKS> CTasksArray;

