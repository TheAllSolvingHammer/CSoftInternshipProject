// TaskDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "TaskDlg.h"
#include "resource.h"

const TCHAR* gl_szTaskDialogState[] = {
	_T("Pending"),
	_T("In Progress"),
	_T("Ended")
};

// CTaskDlg dialog

IMPLEMENT_DYNAMIC(CTaskDlg, CDialogEx)

CTaskDlg::CTaskDlg(CWnd* pParent /*=nullptr*/, TASKS& recTask, CUsersArray& oUsersArray,TaskDlgMode eTaskDlgMode)
	: CDialogEx(IDD_TASK_DIALOG, pParent),
	m_recTask(recTask),
	m_oUsersArray(oUsersArray),
	m_eTaskDlgMode(eTaskDlgMode)
{

}

CTaskDlg::~CTaskDlg()
{
}

void CTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_TASK_NAME, m_edbName);
	DDX_Control(pDX, IDC_STT_TASK_NAME, m_sttName);
	DDX_Control(pDX, IDC_EDB_TASK_DESCRIPTION, m_edbDescription);
	DDX_Control(pDX, IDC_STT_TASK_DESCRIPTION, m_sttDescription);
	DDX_Control(pDX, IDC_CMB_TASK_ASSIGNEE, m_cmbAssignee);
	DDX_Control(pDX, IDC_STT_TASK_ASSIGNEE, m_sttAssignee);
	DDX_Control(pDX, IDC_CMB_TASK_STATUS, m_cmbStatus);
	DDX_Control(pDX, IDC_STT_TASK_STATUS, m_sttStatus);
	DDX_Control(pDX, IDC_EDB_TASK_EFFORT, m_edbEffort);
	DDX_Control(pDX, IDC_STT_TASK_EFFORT_LABEL, m_sttEffortLabel);
}


BEGIN_MESSAGE_MAP(CTaskDlg, CDialogEx)
END_MESSAGE_MAP()


// CTaskDlg message handlers

BOOL CTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Task"));
	m_sttName.SetWindowText(_T("Name: "));
	m_sttDescription.SetWindowText(_T("Description: "));
	m_sttAssignee.SetWindowText(_T("User in charge: "));
	m_sttStatus.SetWindowText(_T("Status: "));
	m_sttEffortLabel.SetWindowText(_T("Task Effort: "));
	if (!FetchTableData()) {
		AfxMessageBox(_T("Failed to load combo boxes"), MB_ICONERROR);
		return FALSE;
	}

	int nIndex = FindUserIndex(m_recTask.lUserInChargeID);
	if (nIndex != CB_ERR) {
		m_cmbAssignee.SetCurSel(nIndex);
	}
	else {
		m_cmbAssignee.SetCurSel(-1);
	}

	m_edbName.SetWindowText(m_recTask.szName);
	m_edbDescription.SetWindowText(m_recTask.szDescription);
	CString strEffort;
	strEffort.Format(_T("%d"), m_recTask.nTotalEffort);
	m_edbEffort.SetWindowText(strEffort.GetString());
	UpdateData(FALSE);
	return TRUE;  
}

bool CTaskDlg::FetchTableData()
{
	for (INT_PTR i = 0; i < m_oUsersArray.GetCount();i++)
	{
		USERS* pRecUser = m_oUsersArray.GetAt(i);
		if (pRecUser)
		{
			int nIndex = m_cmbAssignee.AddString(pRecUser->szName);
			if (nIndex != CB_ERR)
			{
				m_cmbAssignee.SetItemData(nIndex, pRecUser->lID);
			}
		}
	}

	for (int i = 0; i < TASK_DIALOG_STATE_COUNT; ++i)
	{
		int nIdx = m_cmbStatus.AddString(gl_szTaskDialogState[i]);
		m_cmbStatus.SetItemData(nIdx, i + 1);
	}

	if (m_eTaskDlgMode == TASK_ADD)
	{
		int nIndex = FindStatusIndex(1);
		m_cmbStatus.SetCurSel(nIndex);
		m_cmbStatus.EnableWindow(FALSE);
	}
	else
	{
		int nIndex = FindStatusIndex(m_recTask.sTaskStatus);
		m_cmbStatus.SetCurSel(nIndex != CB_ERR ? nIndex : -1);
		m_cmbStatus.EnableWindow(TRUE);
	}
	
	return true;
}

int CTaskDlg::FindUserIndex(const long lUserID)
{
	for (int i = 0; i < m_cmbAssignee.GetCount(); ++i)
	{
		if (m_cmbAssignee.GetItemData(i) == (DWORD_PTR)lUserID)
		{
			return i;
		}
	}
	return CB_ERR;
}

int CTaskDlg::FindStatusIndex(const short sStatus)
{
	for (int i = 0; i < m_cmbStatus.GetCount(); ++i) {
		if ((short)m_cmbStatus.GetItemData(i) == sStatus) {
			return i;
		}
	}
	return CB_ERR;
}

void CTaskDlg::OnOK()
{
	UpdateData(TRUE);

	CString strName, strDescription, strEffort;
	m_edbName.GetWindowText(strName);
	m_edbDescription.GetWindowText(strDescription);
	m_edbEffort.GetWindowText(strEffort);

	strName.Trim();
	strDescription.Trim();
	strEffort.Trim();

	if (strName.IsEmpty())
	{
		AfxMessageBox(_T("Please enter a task name."), MB_ICONWARNING);
		m_edbName.SetFocus();
		return;
	}

	if (strDescription.IsEmpty())
	{
		AfxMessageBox(_T("Please enter a task description."), MB_ICONWARNING);
		m_edbDescription.SetFocus();
		return;
	}

	int nAssigneeSel = m_cmbAssignee.GetCurSel();
	if (nAssigneeSel == CB_ERR)
	{
		AfxMessageBox(_T("Please select a user in charge."), MB_ICONWARNING);
		m_cmbAssignee.SetFocus();
		return;
	}

	int nStatusSel = m_cmbStatus.GetCurSel();
	if (nStatusSel == CB_ERR)
	{
		AfxMessageBox(_T("Please select a task status."), MB_ICONWARNING);
		m_cmbStatus.SetFocus();
		return;
	}

	if (strEffort.IsEmpty())
	{
		AfxMessageBox(_T("Please enter a task effort value."), MB_ICONWARNING);
		m_edbEffort.SetFocus();
		return;
	}

	for (int i = 0; i < strEffort.GetLength(); ++i)
	{
		if (!_istdigit(strEffort[i]))
		{
			AfxMessageBox(_T("Effort must be a valid positive integer."), MB_ICONERROR);
			m_edbEffort.SetFocus();
			return;
		}
	}

	int nEffort = _ttoi(strEffort);
	if (nEffort <= 0)
	{
		AfxMessageBox(_T("Effort must be greater than zero."), MB_ICONERROR);
		m_edbEffort.SetFocus();
		return;
	}

	_tcscpy_s(m_recTask.szName, strName);
	_tcscpy_s(m_recTask.szDescription, strDescription);

	m_recTask.lUserInChargeID = (long)m_cmbAssignee.GetItemData(nAssigneeSel);
	m_recTask.sTaskStatus = (short)m_cmbStatus.GetItemData(nStatusSel);
	m_recTask.nTotalEffort = nEffort;

	CDialogEx::OnOK();
}
