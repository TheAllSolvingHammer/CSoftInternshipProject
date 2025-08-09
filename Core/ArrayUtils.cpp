#include "pch.h"

#include "ArrayUtils.h"

CArrayAutoManager::CArrayAutoManager() 
{

}

CArrayAutoManager::~CArrayAutoManager()
{
    for (INT_PTR i = 0; i < this->CPtrArray::GetCount(); i++)
    {
        delete this->CPtrArray::GetAt(i);
    }
    this->CPtrArray::RemoveAll();
}