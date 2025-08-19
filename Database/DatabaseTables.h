#pragma once
#include <afxtempl.h>
#include "DatabaseContext.h"

#include "ArrayUtils.h"

#define TABLE_DATA_ACCESSOR_INDEX		1

#define ERR_SESSION_CREATION            "Failed to create session."
#define ERR_SESSION_INIT                "Session init error!"

#define QUERY_SELECT_UPDATE             "SELECT * FROM %s WITH (UPDLOCK) WHERE ID = %d"
#define QUERY_SELECT_SINGLE             "SELECT * FROM %s WHERE ID = %d"

#define QUERY_SELECT_ALL                "SELECT * FROM %s"
#define QUERY_SELECT_ALL_UPDATABLE		"SELECT * FROM %s WITH (UPDLOCK)"

#define ERR_TRANSACTION_START           "Failed to start transaction."
#define ERR_CONCURENCY_CONFLICT         "Update failed: concurrency conflict."
#define ERR_TRANSACTION_COMMIT          "Failed to commit transaction."

enum EQueryLock
{
	NoLock,
	UpdLock,
	ExclusiveLock,
};

template<typename TRecord,typename TAccessor>
class CBaseTable
{
private:
	bool m_bSessionIsOwned;
protected:
	CString m_strTableName;
	CSession m_oSession;
public:
	CCommand<CAccessor<TAccessor>> m_oCommand;
    TRecord& m_recRecord;
public:

	CBaseTable(TRecord& recRecord, const CString strTableName, CSession& oExternalSession)
		: m_recRecord(recRecord),
		m_oSession(oExternalSession)
	{
		this->m_strTableName = strTableName;
		this->m_bSessionIsOwned = false;
	}

	CBaseTable(TRecord& recRecord, const CString strTableName)
		: m_recRecord(recRecord)
	{
		this->m_strTableName = strTableName;
		CDatabaseContext::getInstance().Connect();
		HRESULT hRes = CDatabaseContext::getInstance().CreateSession(m_oSession);
		if (FAILED(hRes))
		{
			m_oSession.Close();
			AfxMessageBox(_T(ERR_SESSION_CREATION), MB_ICONERROR);
		}
		this->m_bSessionIsOwned = true;
	}

	~CBaseTable()
	{
		m_oCommand.Close();
		if (m_bSessionIsOwned)
		{
			m_oSession.Close();
		}
	}

protected:
	HRESULT StartOrContinueTransaction()
	{
		if (m_bSessionIsOwned)
		{
			HRESULT hRes = m_oSession.StartTransaction();
			if (FAILED(hRes))
			{
				AfxMessageBox(_T(ERR_TRANSACTION_START), MB_ICONERROR);
				return hRes;
			}
		}
		return S_OK;
	}

	HRESULT CommitOrAbortTransaction(bool bCommit)
	{
		if (m_bSessionIsOwned)
		{
			if (bCommit)
			{
				HRESULT hRes = m_oSession.Commit();
				if (FAILED(hRes))
				{
					AfxMessageBox(_T(ERR_TRANSACTION_COMMIT), MB_ICONERROR);
					return hRes;
				}
			}
			else
			{
				m_oSession.Abort();
			}
		}
		return S_OK;
	}

private:
	bool OpenRowsetWithLock(long lID, EQueryLock eLockMode)
	{
		if (!m_oSession.m_spOpenRowset)
		{
			AfxMessageBox(_T(ERR_SESSION_INIT));
			return false;
		}

		CString strSQL;
		CDBPropSet props(DBPROPSET_ROWSET);

		switch (eLockMode)
		{
		case NoLock:
			strSQL.Format(_T(QUERY_SELECT_SINGLE), m_strTableName.GetString(), lID);
			break;
		case UpdLock:
			strSQL.Format(_T(QUERY_SELECT_UPDATE), m_strTableName.GetString(), lID);
			props.AddProperty(DBPROP_IRowsetChange, true);
			props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);
			props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
			props.AddProperty(DBPROP_IRowsetScroll, true);
			break;
		default:
			strSQL.Format(_T(QUERY_SELECT_SINGLE), m_strTableName.GetString(), lID);
			break;
		}

		HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
		if (FAILED(hRes)) {
			return false;
		}

		if (m_oCommand.MoveFirst() != S_OK) {
			return false;
		}
		return true;
	}
public:
	bool SelectAll(CArrayAutoManager_2<TRecord>& oArray)
	{
		if (FAILED(StartOrContinueTransaction()))
			return false;

		CString strSQL;
		strSQL.Format(_T(QUERY_SELECT_ALL), m_strTableName.GetString());

		HRESULT hRes = m_oCommand.Open(m_oSession, strSQL);
		if (FAILED(hRes))
		{
			CommitOrAbortTransaction(false);
			return false;
		}

		while (m_oCommand.MoveNext() == S_OK)
		{
			TRecord* pRecord = new TRecord();
			*pRecord = m_recRecord;
			oArray.Add(pRecord);
		}

		m_oCommand.Close();
		return SUCCEEDED(CommitOrAbortTransaction(true));
	}

	bool SelectWhereID(const long lID, TRecord& rec)
	{
		if (FAILED(StartOrContinueTransaction()))
			return false;

		if (!OpenRowsetWithLock(lID, NoLock))
		{
			CommitOrAbortTransaction(false);
			return false;
		}

		rec = m_recRecord;
		m_oCommand.Close();
		return SUCCEEDED(CommitOrAbortTransaction(true));
	}


	bool UpdateWhereID(const long lID, TRecord& rec)
	{
		if (FAILED(StartOrContinueTransaction()))
			return false;

		if (!OpenRowsetWithLock(lID, UpdLock))
		{
			CommitOrAbortTransaction(false);
			return false;
		}

		if (m_recRecord.nUpdateCounter != rec.nUpdateCounter)
		{
			AfxMessageBox(_T(ERR_CONCURENCY_CONFLICT));
			m_oCommand.Close();
			CommitOrAbortTransaction(false);
			return false;
		}

		m_recRecord = rec;
		m_recRecord.nUpdateCounter++;
		rec = m_recRecord;

		HRESULT hRes = m_oCommand.SetData(1);
		m_oCommand.Close();
		return SUCCEEDED(hRes) && SUCCEEDED(CommitOrAbortTransaction(true));
	}


	bool Insert(TRecord& rec)
	{
		if (FAILED(StartOrContinueTransaction()))
			return false;

		CString strSQL;
		strSQL.Format(_T(QUERY_SELECT_ALL), m_strTableName.GetString());

		CDBPropSet props(DBPROPSET_ROWSET);
		props.AddProperty(DBPROP_IRowsetChange, true);
		props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT);
		props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		props.AddProperty(DBPROP_QUICKRESTART, true);

		HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
		if (FAILED(hRes))
		{
			CommitOrAbortTransaction(false);
			return false;
		}

		m_recRecord = rec;
		hRes = m_oCommand.Insert(1);
		if (FAILED(hRes))
		{
			m_oCommand.Close();
			CommitOrAbortTransaction(false);
			return false;
		}

		if (m_oCommand.MoveLast() != S_OK)
		{
			m_oCommand.Close();
			CommitOrAbortTransaction(false);
			return false;
		}

		rec = m_recRecord;
		m_oCommand.Close();
		return SUCCEEDED(CommitOrAbortTransaction(true));
	}

	bool DeleteWhereID(const long lID)
	{
		if (FAILED(StartOrContinueTransaction()))
			return false;

		CString strSQL;
		strSQL.Format(_T(QUERY_SELECT_SINGLE), m_strTableName.GetString(), lID);

		CDBPropSet props(DBPROPSET_ROWSET);
		props.AddProperty(DBPROP_IRowsetChange, true);
		props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

		HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
		if (FAILED(hRes))
		{
			CommitOrAbortTransaction(false);
			return false;
		}

		if (m_oCommand.MoveFirst() != S_OK)
		{
			m_oCommand.Close();
			CommitOrAbortTransaction(false);
			return false;
		}

		hRes = m_oCommand.Delete();
		if (FAILED(hRes))
		{
			m_oCommand.Close();
			CommitOrAbortTransaction(false);
			return false;
		}

		m_oCommand.Close();
		return SUCCEEDED(CommitOrAbortTransaction(true));
	}
};

