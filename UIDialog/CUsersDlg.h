#pragma once
#include "afxdialogex.h"
#include "Users.h"
#include "JobTitles.h"
#include "DllExport.h"



// CUsersTableDialog dialog

class UIDialogDLL_EXP CUsersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUsersDlg)

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="pParent"></param>
	CUsersDlg(CWnd* pParent = nullptr);   // standard constructor

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CUsersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USERS };
#endif
public:
	/// <summary>
	/// ����������� ����� OnOK �� ����� ����������� �� ���� �������/������������ �� ������
	/// </summary>
	virtual void OnOK();
	/// <summary>
	/// ������������� �� �������
	/// </summary>
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	/// <summary>
	/// �� ������� List-� � ������� �� ����������.
	/// </summary>
	/// <returns>TRUE ��� �����/FALSE ��� �������</returns>
	BOOL FetchTableData();
	/// <summary>
	/// ������ ������� �� ��������� �� ����������
	/// </summary>
	/// <param name="lJobTitleID">ID-�� �� ���������</param>
	/// <returns>������� � ����������</returns>
	int FindJobTitleIndex(long lJobTitleID);
public:
	CStatic m_sttEmail;
	CStatic m_sttName;
	CStatic m_sttJobTitle;
	CEdit m_edbName;
	CEdit m_edbEmail;
	USERS m_recUser;
	JOB_TITLES m_recJobTitle;
	CComboBox m_cmbJobTitle;
	CJobTitlesArray m_oJobTitlesArray;
};
