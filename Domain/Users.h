#pragma once
#include <afxstr.h>
#include "pch.h"

#define USERS_MAX_NAME_SIZE     128
#define USERS_MAX_EMAIL_SIZE    256

struct USERS {
    long lID;
    int nUpdateCounter;
    TCHAR szName[USERS_MAX_NAME_SIZE];
    TCHAR szEmail[USERS_MAX_EMAIL_SIZE];
    long lJobTitleID;

    USERS() {
        ZeroMemory(this, sizeof(*this));
    }
};

typedef CTypedPtrArray<CPtrArray, USERS*> CUsersArray;