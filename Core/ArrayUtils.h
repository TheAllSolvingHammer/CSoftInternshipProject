#pragma once
#include <afxtempl.h>
#include "DllExport.h"



class CoreDLL_EXP CArrayAutoManager : public CPtrArray
{
public:
    CArrayAutoManager();
    virtual ~CArrayAutoManager();
    void ClearAll();
};



