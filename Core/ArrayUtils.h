#pragma once
#include <afxtempl.h>
#include "DllExport.h"



class CoreDLL_EXP CArrayAutoManager : public CPtrArray
{
public:
    CArrayAutoManager();
    virtual ~CArrayAutoManager();
};

//template<class T>
//class CoreDLL_EXP CArrayAutoManager : public CTypedPtrArray<CPtrArray, T*>
//{
//public:
//    CArrayAutoManager()
//    {
//
//    }
//    virtual ~CArrayAutoManager()
//    {
//        for (INT_PTR i = 0; i < this->CPtrArray::GetCount(); ++i)
//        {
//            delete this->CPtrArray::GetAt(i);
//        }
//        this->CPtrArray::RemoveAll();
//    }
//};


