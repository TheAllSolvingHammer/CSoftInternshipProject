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
class DomainDLL_EXP CArrayAutoManager_2
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

    T* GetAt(INT_PTR nIndex)
    {

        return NULL;
    }

    int GetCount()
    {
        return 0;
    }

    int GetSize()
    {
        return 0;
    }

    void RemoveAll()
    {

    }

    void Add(T* pRecord)
    {

    }
};


