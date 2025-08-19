#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define USERS_MAX_NAME_SIZE         128
#define USERS_MAX_EMAIL_SIZE        256
#define USERS_MAX_PASSWORD_SIZE     256

/// <summary>
/// Структура потребители
/// </summary>
struct USERS {
    /// <summary>
    /// Идентификатор на потребител
    /// </summary>
    long lID;
    /// <summary>
    /// Брояч на актуализациите
    /// </summary>
    int nUpdateCounter;
    /// <summary>
    /// Име на потребителя
    /// </summary>
    TCHAR szName[USERS_MAX_NAME_SIZE];
    /// <summary>
    /// Имейл на потребителя
    /// </summary>
    TCHAR szEmail[USERS_MAX_EMAIL_SIZE];
    /// <summary>
    /// Работна позиция на потребителя
    /// </summary>
    long lJobTitleID;
    /// <summary>
    /// Парола на потребителя
    /// </summary>
    TCHAR szHashedPassword[USERS_MAX_PASSWORD_SIZE];

    /// <summary>
    /// Конструктор за празна структура на потребител
    /// </summary>
    USERS() {
        ZeroMemory(this, sizeof(*this));
    }

};

typedef CArrayAutoManager<USERS> CUsersArray;