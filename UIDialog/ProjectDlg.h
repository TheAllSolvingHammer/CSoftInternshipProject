#pragma once
#include "afxdialogex.h"
#include <Projects.h>

#include <Users.h>
#include <Tasks.h>


// CProjectDlg dialog

/// <summary>
/// Енумерация за работа на диалога
/// </summary>
enum ProjectDialogMode {
	PROEJCT_DIALOG_MODE_READ_ONLY=0,
	PROEJCT_DIALOG_MODE_EDITABLE,
	PROEJCT_DIALOG_MODE_CREATE

};

/// <summary>
/// Енумерация за състоянието на пректа( Активен и Приключил )
/// </summary>
enum ProjectStateDialog
{
	PROJECT_DIALOG_STATE_ACTIVE = 0,
	PROJECT_DIALOG_STATE_FINISHED,
	PROJECT_DIALOG_STATE_COUNT
};

/// <summary>
/// Описателен масив за състоянията на проекта
/// </summary>
const TCHAR* gl_szProjectStateDescriptionDialog[] = {
	_T("Active"),
	_T("Finished")
};

/// <summary>
/// Енумерация за колоните в лист контролата на задачите
/// </summary>
enum TasksColumns
{
	TASK_COLUMN_ID = 0,
	TASK_COLUMN_NAME,
	TASK_COLUMN_DESCRIPTION,
	TASK_COLUMN_ASSIGNEE,
	TASK_COLUMN_STATUS,
	TASK_COLUMN_EFFORT,
	TASK_COLUMN_COUNT
};

/// <summary>
/// Описателен хедърен текст за колоните в лист контролата на задачите
/// </summary>
const TCHAR* gl_szColumnHeadersTasks[] = {
	_T("ID"),
	_T("Name"),
	_T("Description"),
	_T("User in Charge"),
	_T("Status"),
	_T("Effort"),
};

/// <summary>
/// Ширина на колоните за лист контролата на задачите
/// </summary>
const int gl_nColumnWidthsTasks[] = {
	50,
	150,
	200,
	150,
	100,
	150
};

/// <summary>
/// Енумерация представляваща състоянието на задача ( Pending/In-Progress/Ended )
/// </summary>
enum TaskState
{
	TASK_STATE_PENDING = 0,
	TASK_STATE_IN_PROGRESS,
	TASK_STATE_ENDED,
	TASK_STATE_COUNT
};

/// <summary>
/// Описателен текстови маси за състоянието на задача
/// </summary>
const TCHAR* gl_szTaskStateDescription[] = {
	_T("Pending"),
	_T("In Progress"),
	_T("Ended")
};

/// <summary>
/// Клас отговарящ за поведението на Диалога за Проекти
/// </summary>
class UIDialogDLL_EXP CProjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectDlg)

public:
	/// <summary>
	/// Контруктор на диалога за проекти, приема следните параметри
	/// </summary>
	/// <param name="pParent">CWnd на родителя</param>
	/// <param name="recProject">проекта по който ще се работи</param>
	/// <param name="oUsersArray">Потребителите които ще бъдат заредени като опция за ибзор за мениджър</param>
	/// <param name="oTasksArray">Задачите отговарящи на проекта</param>
	/// <param name="oUpdatedTasksArray">Задачите които са били актуализирани от диалога</param>
	/// <param name="oDeletedtasksArray">Задачите които са били изтрити от диалога</param>
	CProjectDlg(CWnd* pParent = nullptr, 
		PROJECTS& recProject=PROJECTS(),
		CUsersArray& oUsersArray=CUsersArray(), 
		CTasksArray& oTasksArray=CTasksArray(), 
		CTasksArray& oUpdatedTasksArray = CTasksArray(),
		CTasksArray& oDeletedtasksArray = CTasksArray(),
		ProjectDialogMode eProjectDialogMode=PROEJCT_DIALOG_MODE_EDITABLE);
	/// <summary>
	/// Деструктор на диалога за проекти
	/// </summary>
	virtual ~CProjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	/// <summary>
	/// Добавя задача към проекта
	/// </summary>
	afx_msg void OnBnClickedBtnProjectAddTask();
	/// <summary>
	/// Актуализира задача към проекта
	/// </summary>
	afx_msg void OnBnClickedBtnProjectTaskDelete();
	/// <summary>
	/// Изтрива задача към проекта
	/// </summary>
	afx_msg void OnBnClickedBtnProjectTaskUpdate();
private:
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
	int FindStatusIndex(const short status);
	/// <summary>
	/// Извлича всичките данни от таблиците за даден проект
	/// </summary>
	/// <returns>Истина ако е успешна операцията, Неистина ако се провали</returns>
	bool FetchTableData();
	/// <summary>
	/// Актуализира визуално цялото време за изпълнение на всички задачи ( визуално )
	/// </summary>
	void UpdateEffortTotal();
	/// <summary>
	/// Проверява състоянието на проекта дали се е променило от добавяне/актуализиране/изтриване на задача
	/// </summary>
	void CheckProjectStatus();
	//void CheckUpdateArrayExistance(long lID);
private:
	//Елементи
	CEdit m_edbName;
	CRichEditCtrl m_recDescription;
	CComboBox m_cmbManager;
	CComboBox m_cmbStatus;
	CEdit m_edbEffort;
	CListCtrl m_lscTasks;
	CButton m_btnAddTask;
	CButton m_btnEditTask;
	CButton m_btnDeleteTask;
	
	//Описания
	CStatic m_sttName;
	CStatic m_sttDescription;
	CStatic m_sttManager;
	CStatic m_sttStatus;
	CStatic m_sttEffortLabel;
	CStatic m_sttTasks;
	
	//Режим
	ProjectDialogMode m_eProjectDialogMode;

	//Помощни променливи
public:
	PROJECTS& m_recProject;
	CUsersArray& m_oUsersArray;
	CTasksArray& m_oTasksArray;
	CTasksArray& m_oUpdatedTasks;
	CTasksArray& m_oDeletedTasks;
};
