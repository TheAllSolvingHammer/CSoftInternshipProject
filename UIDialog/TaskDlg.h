#pragma once
#include "afxdialogex.h"
#include <Tasks.h>
#include <Users.h>

/// <summary>
/// Енумерация за състоянията на задача
/// </summary>
enum TaskStatus
{
	TASK_DIALOG_STATE_PENDING = 0,
	TASK_DIALOG_STATE_IN_PROGRESS,
	TASK_DIALOG_STATE_ENDED,
	TASK_DIALOG_STATE_COUNT
};

/// <summary>
/// Енумерация за режима на работа на диалог 0 - > добавяне на задача, 1 - актуализиране
/// </summary>
enum TaskDlgMode { 
	TASK_ADD=0, 
	TASK_UPDATE 
};


// CTaskDlg dialog

/// <summary>
/// Клас отговарящ за работата на диалога на задачите
/// </summary>
class UIDialogDLL_EXP CTaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskDlg)

public:
	/// <summary>
	/// Контруктор за диалога на задачите
	/// </summary>
	/// <param name="pParent">CWnd на родителя</param>
	/// <param name="recTask">Задачата по която ще работи прозореца</param>
	/// <param name="oUsersArray">Масив от потребители, за да може да се избере отговорника</param>
	/// <param name="eTaskDlgMode">Режим на работата на диалога</param>
	CTaskDlg(CWnd* pParent = nullptr, 
		TASKS& recTask=TASKS(),
		CUsersArray& oUsersArray=CUsersArray(),
		TaskDlgMode eTaskDlgMode=TASK_ADD);  
	/// <summary>
	/// Деструктор на диалога на задачите
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
	/// Извлича всичките данни от таблиците за дадена таблица
	/// </summary>
	/// <returns>Истина ако е успешна операцията, Неистина ако се провали</returns>
	bool FetchTableData();
	/// <summary>
	/// Намира индекса на потребител в комбобокса чрез подадено ID
	/// </summary>
	/// <param name="lUserID">ID-то на потребителя</param>
	/// <returns>Индекс за комбобокс</returns>
	int FindUserIndex(const long lUserID);
	/// <summary>
	/// Намира индекса на състоянието в комбобокса чрез подаден статус (число)
	/// </summary>
	/// <param name="status">Число представляващо статуса</param>
	/// <returns>Индекс за комбобокс</returns>
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
