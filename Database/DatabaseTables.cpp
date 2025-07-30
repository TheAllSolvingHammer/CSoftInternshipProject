#pragma once
#include "pch.h"
//#include "DatabaseTables.h"
//
//template<typename TRecord, typename TAccessor>
//CBaseTable<TRecord, TAccessor>::CBaseTable(TRecord& recRecord, const CString strTableName)
//    : m_recRecord(recRecord)
//{
//    this->m_strTableName = strTableName;
//    CDatabaseContext::getInstance().Connect();
//    m_oSession = CDatabaseContext::getInstance().m_oSession;
//}
//template<typename TRecord, typename TAccessor>
//CBaseTable<TRecord, TAccessor>::~CBaseTable()
//{
//    m_oCommand.Close();
//    m_oSession.Close();
//}
//template<typename TRecord, typename TAccessor>
//bool CBaseTable<TRecord, TAccessor>::OpenRowByID(long lID, CSession& oSession, bool bUpdatable)
//{
//    if (!m_oSession.m_spOpenRowset) {
//        AfxMessageBox(_T("Session init error!"));
//        return false;
//    }
//    CString strSQL;
//    strSQL.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName.GetString(), lID);
//
//    HRESULT hRes;
//    if (bUpdatable)
//    {
//        CDBPropSet props(DBPROPSET_ROWSET);
//        props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
//        props.AddProperty(DBPROP_IRowsetScroll, true);
//        props.AddProperty(DBPROP_IRowsetChange, true);
//        props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);
//        hRes = m_oCommand.Open(oSession, strSQL, &props);
//    }
//    else
//    {
//        hRes = m_oCommand.Open(oSession, strSQL);
//    }
//
//    if (FAILED(hRes)) {
//        return false;
//    }
//
//    if (m_oCommand.MoveFirst() != S_OK) {
//        return false;
//    }
//    return true;
//}
//
//template<typename TRecord, typename TAccessor>
//bool CBaseTable<TRecord, TAccessor>::SelectAll(CTypedPtrArray<CPtrArray, TRecord*>& oArray)
//{
//    if (!m_oSession.m_spOpenRowset) {
//        AfxMessageBox(_T("Session init error!"));
//        return false;
//    }
//
//    CString strSQL;
//    strSQL.Format(_T("SELECT * FROM %s"), m_strTableName.GetString());
//
//    CDBPropSet props(DBPROPSET_ROWSET);
//    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
//    props.AddProperty(DBPROP_IRowsetScroll, true);
//    props.AddProperty(DBPROP_IRowsetChange, true);
//    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);
//
//    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
//    if (FAILED(hRes))
//        return false;
//
//    while (m_oCommand.MoveNext() == S_OK)
//    {
//        TRecord* pRecord = new TRecord();
//        *pRecord = m_recRecord;
//        oArray.Add(pRecord);
//    }
//
//    return true;
//}
//
//template<typename TRecord, typename TAccessor>
//bool CBaseTable<TRecord, TAccessor>::SelectWhereID(const long lID, TRecord& rec)
//{
//    if (!OpenRowByID(lID, m_oSession, false))
//    {
//        return false;
//    }
//    rec = m_recRecord;
//    m_oCommand.Close();
//    return true;
//
//}
//template<typename TRecord, typename TAccessor>
//bool CBaseTable<TRecord, TAccessor>::UpdateWhereID(const long lID, TRecord& rec)
//{
//    if (!OpenRowByID(lID, m_oSession, true))
//    {
//        return false;
//    }
//
//    if (m_recRecord.nUpdateCounter != rec.nUpdateCounter) {
//        return false;
//    }
//
//    m_recRecord = rec;
//    m_recRecord.nUpdateCounter++;
//    rec = m_recRecord;
//
//    HRESULT hRes = m_oCommand.SetData(TABLE_DATA_ACCESSOR_INDEX);
//    return SUCCEEDED(hRes);
//    return true;
//}
//
//template<typename TRecord, typename TAccessor>
//bool CBaseTable<TRecord, TAccessor>::Insert(TRecord& rec)
//{
//    if (!m_oSession.m_spOpenRowset) {
//        AfxMessageBox(_T("Session init error!"));
//        return false;
//    }
//
//    CString strSQL;
//    strSQL.Format(_T("SELECT * FROM %s"), m_strTableName.GetString());
//
//    CDBPropSet props(DBPROPSET_ROWSET);
//    props.AddProperty(DBPROP_IRowsetChange, true);
//    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
//    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
//    props.AddProperty(DBPROP_QUICKRESTART, true);
//
//    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
//    if (FAILED(hRes)) {
//        return false;
//    }
//
//    m_recRecord = rec;
//    hRes = m_oCommand.Insert(TABLE_DATA_ACCESSOR_INDEX);
//    if (FAILED(hRes))
//    {
//        return false;
//    }
//
//    hRes = m_oCommand.MoveLast();
//    if (FAILED(hRes))
//    {
//        return false;
//    }
//    rec = m_recRecord;
//    m_oCommand.Close();
//    return SUCCEEDED(hRes);
//}
//
//template<typename TRecord, typename TAccessor>
//bool CBaseTable<TRecord, TAccessor>::DeleteWhereID(const long lID)
//{
//    if (!m_oSession.m_spOpenRowset) {
//        AfxMessageBox(_T("Session init error!"));
//        return false;
//    }
//
//    CString strSQL;
//    strSQL.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName.GetString(), lID);
//
//    CDBPropSet props(DBPROPSET_ROWSET);
//    props.AddProperty(DBPROP_IRowsetChange, true);
//    props.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_DELETE);
//
//    HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
//    if (FAILED(hRes)) {
//        return false;
//    }
//
//    if (m_oCommand.MoveFirst() != S_OK) {
//        return false;
//    }
//
//    hRes = m_oCommand.Delete();
//    if (FAILED(hRes)) {
//        return false;
//    }
//    return true;
//}