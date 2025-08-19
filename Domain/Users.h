#pragma once
#include <afxstr.h>
#include "pch.h"

#include "ArrayUtils.h"

#define USERS_MAX_NAME_SIZE         128
#define USERS_MAX_EMAIL_SIZE        256
#define USERS_MAX_PASSWORD_SIZE     256

struct USERS {
    long lID;
    int nUpdateCounter;
    TCHAR szName[USERS_MAX_NAME_SIZE];
    TCHAR szEmail[USERS_MAX_EMAIL_SIZE];
    long lJobTitleID;
    TCHAR szHashedPassword[USERS_MAX_PASSWORD_SIZE];

    USERS() {
        ZeroMemory(this, sizeof(*this));
    }

};

//typedef CTypedPtrArray<CArrayAutoManager, USERS*> CUsersArray;
typedef CArrayAutoManager_2<USERS> CUsersArray;