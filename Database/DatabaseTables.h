#pragma once
#include <afxtempl.h>
#include "DatabaseContext.h"

#include "ArrayUtils.h"

#define TABLE_DATA_ACCESSOR_INDEX      1

#define ERR_SESSION_CREATION            "Failed to create session."
#define ERR_SESSION_INIT                "Session init error!"

#define QUERY_SELECT_UPDATE             "SELECT * FROM %s WITH (UPDLOCK) WHERE ID = %d"
#define QUERY_SELECT_SINGLE             "SELECT * FROM %s WHERE ID = %d"

#define QUERY_SELECT_ALL                "SELECT * FROM %s"

#define ERR_TRANSACTION_START           "Failed to start transaction."
#define ERR_CONCURENCY_CONFLICT         "Update failed: concurrency conflict."
#define ERR_TRANSACTION_COMMIT          "Failed to commit transaction."


template<typename TRecord,typename TAccessor>
class CBaseTable
{
public:
    CString m_strTableName;
    CSession m_oSession;
    TRecord& m_recRecord;
    CCommand<CAccessor<TAccessor>> m_oCommand;
    CBaseTable(TRecord& recRecord,const CString strTableName)
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
    }
    ~CBaseTable()
    {
        m_oCommand.Close();
        m_oSession.Close();
    }
private:
    bool OpenRowByID(long lID, CSession& oSession, bool bUpdatable)
    {
        if (!m_oSession.m_spOpenRowset) 
        {
            AfxMessageBox(_T(ERR_SESSION_INIT));
            return false;
        }
        CString strSQL;
        if (bUpdatable)
        {
            strSQL.Format(_T(QUERY_SELECT_UPDATE), m_strTableName.GetString(), lID);
        }
        else
        {
            strSQL.Format(_T(QUERY_SELECT_SINGLE), m_strTableName.GetString(), lID);
        }

        HRESULT hRes;
        if (bUpdatable)
        {
            CDBPropSet props(DBPROPSET_ROWSET);
            props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
            props.AddProperty(DBPROP_IRowsetScroll, true);
            props.AddProperty(DBPROP_IRowsetChange, true);
            props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

            hRes = m_oCommand.Open(oSession, strSQL, &props);
        }
        else
        {
            hRes = m_oCommand.Open(oSession, strSQL);
        }

        if (FAILED(hRes)) {
            return false;
        }

        if (m_oCommand.MoveFirst() != S_OK) {
            return false;
        }
        return true;

    }
public:

    bool SelectAll(CArrayAutoManager_2<TRecord> & oArray)
    {
        HRESULT hRes = m_oSession.StartTransaction();
        if (FAILED(hRes))
        {
            AfxMessageBox(_T(ERR_TRANSACTION_START), MB_ICONERROR);
            return false;
        }

        CString strSQL;
        strSQL.Format(_T(QUERY_SELECT_ALL), m_strTableName.GetString());

        CDBPropSet props(DBPROPSET_ROWSET);
        props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
        props.AddProperty(DBPROP_IRowsetScroll, true);
        props.AddProperty(DBPROP_IRowsetChange, true);
        props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

        hRes = m_oCommand.Open(m_oSession, strSQL, &props);
        if (FAILED(hRes))
        {
            m_oSession.Abort();
            return false;
        }

        while (m_oCommand.MoveNext() == S_OK)
        {
            TRecord* pRecord = new TRecord();
            *pRecord = m_recRecord;
            oArray.Add(pRecord);
        }

        m_oCommand.Close();
        m_oSession.Commit();
        return true;
    }

    bool SelectWhereID(const long lID, TRecord& rec)
    {
        HRESULT hRes = m_oSession.StartTransaction();
        if (FAILED(hRes))
        {
            AfxMessageBox(_T(ERR_TRANSACTION_START), MB_ICONERROR);
            return false;
        }

        if (!OpenRowByID(lID, m_oSession, false))
        {
            m_oSession.Abort();
            return false;
        }

        rec = m_recRecord;
        m_oCommand.Close();
        m_oSession.Commit();
        return true;
        
    }
    bool UpdateWhereID(const long lID, TRecord& rec)
    {
        if (!OpenRowByID(lID, m_oSession, true))
        {
            return false;
        }

        if (m_recRecord.nUpdateCounter != rec.nUpdateCounter)
        {
            AfxMessageBox(_T(ERR_CONCURENCY_CONFLICT));
            return false;
        }

        m_recRecord = rec;
        m_recRecord.nUpdateCounter++;
        rec = m_recRecord;

        HRESULT hRes = m_oCommand.SetData(TABLE_DATA_ACCESSOR_INDEX);
        m_oCommand.Close();

        return SUCCEEDED(hRes);
    }

    bool Insert(TRecord& rec)
    {
        CString strSQL;
        strSQL.Format(_T(QUERY_SELECT_ALL), m_strTableName.GetString());

        CDBPropSet props(DBPROPSET_ROWSET);
        props.AddProperty(DBPROP_IRowsetChange, true);
        props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
        props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
        props.AddProperty(DBPROP_QUICKRESTART, true);

        HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
        if (FAILED(hRes))
        {
            return false;
        }

        m_recRecord = rec;
        hRes = m_oCommand.Insert(TABLE_DATA_ACCESSOR_INDEX);
        if (FAILED(hRes))
        {
            return false;
        }

        if (m_oCommand.MoveLast() != S_OK)
        {
            return false;
        }

        rec = m_recRecord;
        m_oCommand.Close();
        return true;
    }
    
    bool DeleteWhereID(const long lID)
    {
        CString strSQL;
        strSQL.Format(_T(QUERY_SELECT_SINGLE), m_strTableName.GetString(), lID);

        CDBPropSet props(DBPROPSET_ROWSET);
        props.AddProperty(DBPROP_IRowsetChange, true);
        props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);

        HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
        if (FAILED(hRes))
        {
            return false;
        }

        if (m_oCommand.MoveFirst() != S_OK)
        {
            return false;
        }

        hRes = m_oCommand.Delete();
        if (FAILED(hRes))
        {
            return false;
        }

        m_oCommand.Close();
        return true;
    }
};

