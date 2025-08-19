#include "pch.h"
#include "TasksTable.h"
#include "ProjectsTable.h"

CTasksTable::CTasksTable() : CBaseTable(m_oCommand.m_recTask, _T(TASKS_TABLE_NAME))
{

}

CTasksTable::CTasksTable(CSession* pSession) : CBaseTable(m_oCommand.m_recTask, _T(TASKS_TABLE_NAME), *pSession)
{

}

CTasksTable::~CTasksTable()
{

}

bool CTasksTable::SelectByProjectId(const long lID, CTasksArray& oTasksArray)
{
	if (FAILED(StartOrContinueTransaction()))
	{
		return false;
	}

	CString strSQL;
	strSQL.Format((QUERY_SELECT_TASKS_BY_PROJECT_ID), lID);

	CDBPropSet props(DBPROPSET_ROWSET);
	props.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	props.AddProperty(DBPROP_IRowsetScroll, true);

	HRESULT hRes = m_oCommand.Open(m_oSession, strSQL, &props);
	if (FAILED(hRes))
	{
		CommitOrAbortTransaction(false);
		return false;
	}

	oTasksArray.ClearAll();

	while (m_oCommand.MoveNext() == S_OK)
	{
		TASKS* pRecTask = new TASKS();
		*pRecTask = m_recRecord;
		oTasksArray.Add(pRecTask);
	}

	m_oCommand.Close();
	return SUCCEEDED(CommitOrAbortTransaction(true));
}

