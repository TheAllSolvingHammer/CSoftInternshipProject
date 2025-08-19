#pragma once
#include <afxtempl.h>
#include "DllExport.h"



class DomainDLL_EXP CArrayAutoManager : public CPtrArray
{
public:
    CArrayAutoManager();
    ~CArrayAutoManager();

    void ClearAll();
};


template<class T>
class CArrayAutoManager_2 : public CTypedPtrArray<CPtrArray, T*>
{
public:
    CArrayAutoManager_2()
    {
    }

    virtual ~CArrayAutoManager_2()
    {
        ClearAll();
    }


    void ClearAll() {
        for (INT_PTR i = 0; i < GetCount(); i++)
        {
            delete GetAt(i);
        }
        RemoveAll();
    }
};


