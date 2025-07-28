#pragma once
#include "afxdialogex.h"
#include "Users.h"
#include "DllExport.h"



// CUsersTableDialog dialog

class UIDialogDLL_EXP CUsersTableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CUsersTableDialog)

public:
	CUsersTableDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUsersTableDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BOOL FetchTableData();
	void FreeUsersArray();
public:
	CListCtrl m_lscUsers;
	CStatic m_sttEmail;
	CStatic m_sttName;
	CEdit m_edbName;
	CEdit m_edbEmail;
	CUsersArray m_oUsersArray;
	virtual BOOL OnInitDialog();
};
