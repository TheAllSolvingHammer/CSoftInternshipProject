#pragma once
#include <afxtempl.h>
#include "DllExport.h"


/// <summary>
/// ���� �� ������������ �� ������ � ���������
/// </summary>
/// <typeparam name="T">��� �������� ����� �� �� ������</typeparam>
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


