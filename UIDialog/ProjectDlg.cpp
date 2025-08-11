// ProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "ProjectDlg.h"
#include "resource.h"


// CProjectDlg dialog

IMPLEMENT_DYNAMIC(CProjectDlg, CDialogEx)

CProjectDlg::CProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_DIALOG, pParent)
{

}

CProjectDlg::~CProjectDlg()
{
}

void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProjectDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjectDlg message handlers

BOOL CProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}
