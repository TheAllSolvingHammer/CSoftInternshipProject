#include "pch.h"
#include "ArrayUtils.h"

CArrayAutoManager::CArrayAutoManager() 
{

}

CArrayAutoManager::~CArrayAutoManager()
{
    ClearAll();
}

void CArrayAutoManager::ClearAll() {
    for (INT_PTR i = 0; i < GetCount(); i++)
    {
        delete GetAt(i);
    }
    RemoveAll();
}