#pragma once
#include <afxstr.h>
#include "pch.h"
#include "ArrayUtils.h"

#define JOB_TITLES_MAX_TITLE_NAME_SIZE      256

/// <summary>
/// ��������� �� ��������
/// </summary>
struct JOB_TITLES {
    /// <summary>
    /// ID �� ���������
    /// </summary>
    long lID;
    /// <summary>
    /// ������������ �� ���������
    /// </summary>
    TCHAR szTitleName[JOB_TITLES_MAX_TITLE_NAME_SIZE];
    /// <summary>
    /// ����� �� ��������������
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// ����������� �� ��������� �� ���������
    /// </summary>
    JOB_TITLES() {
        ZeroMemory(this, sizeof(*this));
    }
};


typedef CArrayAutoManager<JOB_TITLES> CJobTitlesArray;