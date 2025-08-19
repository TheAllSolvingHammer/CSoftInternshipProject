#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define USERS_MAX_NAME_SIZE         128
#define USERS_MAX_EMAIL_SIZE        256
#define USERS_MAX_PASSWORD_SIZE     256

/// <summary>
/// ��������� �����������
/// </summary>
struct USERS {
    /// <summary>
    /// ������������� �� ����������
    /// </summary>
    long lID;
    /// <summary>
    /// ����� �� ��������������
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// ��� �� �����������
    /// </summary>
    TCHAR szName[USERS_MAX_NAME_SIZE];
    /// <summary>
    /// ����� �� �����������
    /// </summary>
    TCHAR szEmail[USERS_MAX_EMAIL_SIZE];
    /// <summary>
    /// ������� ������� �� �����������
    /// </summary>
    long lJobTitleID;
    /// <summary>
    /// ������ �� �����������
    /// </summary>
    TCHAR szHashedPassword[USERS_MAX_PASSWORD_SIZE];

    /// <summary>
    /// ����������� �� ������ ��������� �� ����������
    /// </summary>
    USERS() {
        ZeroMemory(this, sizeof(*this));
    }

};

typedef CArrayAutoManager<USERS> CUsersArray;