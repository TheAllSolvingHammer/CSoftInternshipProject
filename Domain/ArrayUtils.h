#pragma once
#include <afxtempl.h>
#include "DllExport.h"


/// <summary>
/// Клас за управлението на масиви с указатели
/// </summary>
/// <typeparam name="T">Тип указател който ще се подаде</typeparam>
template<class T>
class CArrayAutoManager : public CTypedPtrArray<CPtrArray, T*>
{
public:
    CArrayAutoManager()
    {
    }

    virtual ~CArrayAutoManager()
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


