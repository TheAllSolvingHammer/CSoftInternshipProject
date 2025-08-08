#pragma once
#include <afxtempl.h>


enum Collection
{
	COLLECTION_USERS = 0,
	COLLECTION_JOB_TITLES,
	COLLECTION_PROJECTS,
	COLLECTION_TASKS,
	COLLECTION_COUNT 
};


/// <summary>
/// ѕредставл€ва Garbage Collector клас за управление на вс€какви TypedPtrArrays
/// </summary>
class CArrayManager
{
private:
	CArrayManager();
	
public:
	static CArrayManager& getInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CArrayManager();
		}
		return *m_instance;
	}

	~CArrayManager();

	
	template<typename T>
	void AddCollection(Collection eCollection, CTypedPtrArray<CPtrArray, T*>* pNewCollection)
	{
		ClearCollection(eCollection);

		m_oMap.SetAt(eCollection, (CTypedPtrArray<CPtrArray, CObject*>*)pNewCollection);
	}

	void ClearCollection(Collection eCollection)
	{
		CTypedPtrArray<CPtrArray, CObject*>* pGenericArray = nullptr;
		if (m_oMap.Lookup(eCollection, pGenericArray))
		{
			if (pGenericArray)
			{
				for (INT_PTR i = 0; i < pGenericArray->GetSize(); ++i)
				{
					delete pGenericArray->GetAt(i);
				}
				pGenericArray->RemoveAll();
				delete pGenericArray;
			}
			m_oMap.RemoveKey(eCollection);
		}
	}

	void ClearAllCollections()
	{
		POSITION pos = m_oMap.GetStartPosition();
		while (pos != nullptr)
		{
			Collection eKey;
			CTypedPtrArray<CPtrArray, CObject*>* pGenericArray;
			m_oMap.GetNextAssoc(pos, eKey, pGenericArray);
			if (pGenericArray)
			{
				for (INT_PTR i = 0; i < pGenericArray->GetCount(); i++)
				{
					delete pGenericArray->GetAt(i);
				}
				pGenericArray->RemoveAll();
				delete pGenericArray;
			}
		}
	}

	template<typename T>
	CTypedPtrArray<CPtrArray, T*>* GetCollection(const Collection eCollection) const
	{
		CTypedPtrArray<CPtrArray, CObject*>* pGenericArray = nullptr;
		if (m_oMap.Lookup(eCollection, pGenericArray))
		{
			return reinterpret_cast<CTypedPtrArray<CPtrArray, T*>*>(pGenericArray);
		}
		return nullptr;
	}


	template<typename T>
	CTypedPtrArray<CPtrArray, T*>& GetCollectionRef(const Collection eCollection)
	{
		CTypedPtrArray<CPtrArray, T*> s_emptyArray;
		CTypedPtrArray<CPtrArray, T*>* pCollection = GetCollection<T>(eCollection);
		return (pCollection) ? *pCollection : s_emptyArray;
	}

private:
	static CArrayManager* m_instance;
	CMap<Collection, Collection, CTypedPtrArray<CPtrArray, CObject*>*, CTypedPtrArray<CPtrArray, CObject*>*> m_oMap;
};



