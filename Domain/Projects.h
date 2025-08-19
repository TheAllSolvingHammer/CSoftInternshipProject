#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define PROJECTS_MAX_NAME_SIZE          128
#define PROJECTS_MAX_DESCRIPTION_SIZE   256

/// <summary>
/// ��������� �� ���������
/// </summary>
struct PROJECTS {
    /// <summary>
    /// ������������� �� �������
    /// </summary>
    long lID;
    /// <summary>
    /// ����� �� ��������������
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// ������������ �� �������
    /// </summary>
    TCHAR szName[PROJECTS_MAX_NAME_SIZE];
    /// <summary>
    /// �������� �� �������
    /// </summary>
    TCHAR szDescription[PROJECTS_MAX_DESCRIPTION_SIZE];
    /// <summary>
    /// ���������� �� �������
    /// </summary>
    long lProjectManagerID;
    /// <summary>
    /// ��������� �� �������
    /// </summary>
    short sProjectStatus;
    /// <summary>
    /// ����������� �� �������
    /// </summary>
    int nTotalEffort;

    /// <summary>
    /// ����������� �� ����������� �������
    /// </summary>
    PROJECTS() {
        ZeroMemory(this, sizeof(*this));
    }
};


typedef CArrayAutoManager<PROJECTS> CProjectsArray;