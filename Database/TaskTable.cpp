#include "pch.h"
#include "TasksTable.h"
#include "ProjectsTable.h"

CTasksTable::CTasksTable() : CBaseTable(m_oCommand.m_recTask, _T(TASKS_TABLE_NAME))
{

}

CTasksTable::~CTasksTable()
{

}

bool CTasksTable::SelectByProjectId(const long lID, CTasksArray& oTasksArray)
{
    HRESULT hRes = m_oSession.StartTransaction();
    if (FAILED(hRes))
    {
        AfxMessageBox(_T(ERR_TRANSACTION_START), MB_ICONERROR);
        return false;
    }

    CString strSQL;
    strSQL.Format((QUERY_SELECT_TASKS_BY_PROJECT_ID), lID);

    CDBPropSet props(DBPROPSET_ROWSET);
    props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    props.AddProperty(DBPROP_IRowsetScroll, true);

    hRes = m_oCommand.Open(m_oSession, strSQL, &props);
    if (FAILED(hRes))
    {
        m_oSession.Abort();
        return false;
    }

    oTasksArray.ClearAll();
 
    while (m_oCommand.MoveNext() == S_OK)
    {
        TASKS* pRecTask = new TASKS();
        *pRecTask = m_oCommand.m_recTask;
        oTasksArray.Add(pRecTask);
    }

    m_oCommand.Close();
    m_oSession.Commit();
    return true;
}

