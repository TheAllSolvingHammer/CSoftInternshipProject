#pragma once
#include "afxdialogex.h"
#include <Tasks.h>
#include <Users.h>

/// <summary>
/// ���������� �� ����������� �� ������
/// </summary>
enum TaskStatus
{
	TASK_DIALOG_STATE_PENDING = 0,
	TASK_DIALOG_STATE_IN_PROGRESS,
	TASK_DIALOG_STATE_ENDED,
	TASK_DIALOG_STATE_COUNT
};

/// <summary>
/// ���������� �� ������ �� ������ �� ������ 0 - > �������� �� ������, 1 - �������������
/// </summary>
enum TaskDlgMode { 
	TASK_ADD=0, 
	TASK_UPDATE 
};


// CTaskDlg dialog

/// <summary>
/// ���� ��������� �� �������� �� ������� �� ��������
/// </summary>
class UIDialogDLL_EXP CTaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskDlg)

public:
	/// <summary>
	/// ���������� �� ������� �� ��������
	/// </summary>
	/// <param name="pParent">CWnd �� ��������</param>
	/// <param name="recTask">�������� �� ����� �� ������ ���������</param>
	/// <param name="oUsersArray">����� �� �����������, �� �� ���� �� �� ������ �����������</param>
	/// <param name="eTaskDlgMode">����� �� �������� �� �������</param>
	CTaskDlg(CWnd* pParent = nullptr, 
		TASKS& recTask=TASKS(),
		CUsersArray& oUsersArray=CUsersArray(),
		TaskDlgMode eTaskDlgMode=TASK_ADD);  
	/// <summary>
	/// ���������� �� ������� �� ��������
	/// </summary>
	virtual ~CTaskDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
private:
	/// <summary>
	/// ������� �������� ����� �� ��������� �� ������ �������
	/// </summary>
	/// <returns>������ ��� � ������� ����������, �������� ��� �� �������</returns>
	bool FetchTableData();
	/// <summary>
	/// ������ ������� �� ���������� � ���������� ���� �������� ID
	/// </summary>
	/// <param name="lUserID">ID-�� �� �����������</param>
	/// <returns>������ �� ���������</returns>
	int FindUserIndex(const long lUserID);
	/// <summary>
	/// ������ ������� �� ����������� � ���������� ���� ������� ������ (�����)
	/// </summary>
	/// <param name="status">����� �������������� �������</param>
	/// <returns>������ �� ���������</returns>
	int FindStatusIndex(const short sStatus);
private:
	CEdit m_edbName;
	CEdit m_edbDescription;
	CComboBox m_cmbAssignee;
	CComboBox m_cmbStatus;
	CEdit m_edbEffort;

	CStatic m_sttName;
	CStatic m_sttDescription;
	CStatic m_sttAssignee;
	CStatic m_sttStatus;
	CStatic m_sttEffortLabel;
	TaskDlgMode m_eTaskDlgMode;
public:
	TASKS& m_recTask;
	CUsersArray& m_oUsersArray;
};
