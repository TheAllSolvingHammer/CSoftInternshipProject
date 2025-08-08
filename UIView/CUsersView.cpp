#include "pch.h"
#include "framework.h"
#include "CUsersView.h"
#include "resource.h"
#include <CUsersDlg.h>

#define ERR_MESSAGE_SAFE_HWND "Error in getting the safe HWND"
#define ERR_MESSAGE_LST_CTRL "Error in getting the header of the list control"
#define ERR_UNKNOWN "Unknown"
#define ERR_NOT_SELECTED_USER_EDIT "Please select a user to edit."
#define SCS_USER_UPDATE "User updated successfully!"
#define ERR_USER_UPDATE "Failed to update user."
#define ERR_USER_NOT_FOUND "Selected user not found in document data."


#define SCS_USER_ADD "User added successfully!"
#define ERR_USER_ADD "Failed to add user."

#define ERR_NOT_SELECTED_USER_DELETE "Please select a user to delete."
#define CONF_DELETE_USER "Are you sure to delete the selected user?"

#define SCS_USER_DELETE "User deleted successfully!"
#define ERR_USER_DELETE "Failed to delete user."

/////////////////////////////////////////////////////////////////////////////
//CUsersView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CUsersView, CListView)

BEGIN_MESSAGE_MAP(CUsersView, CListView)
    ON_COMMAND(ID_MENU_INSERT_USER, &CUsersView::OnUserAdd)

    ON_COMMAND(ID_MENU_DELETE_USER, &CUsersView::OnUserDelete)
    ON_WM_CONTEXTMENU()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CUsersView::CUsersView() noexcept
{
}

CUsersView::~CUsersView()
{
}

// Methods
// ----------------
CUsersDocument* CUsersView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUsersDocument)));
	return (CUsersDocument*)m_pDocument;
}


// MFC Message Handlers
// ----------------


//Methods
// ----------------
void CUsersView::PopulateUsersList()
{
    CListCtrl& oListCtrl = GetListCtrl();
    if (!oListCtrl.GetSafeHwnd())
    {
        AfxMessageBox(_T(ERR_MESSAGE_SAFE_HWND));
        return;
    }
    oListCtrl.DeleteAllItems();

    CHeaderCtrl* pHeaderCtrl = oListCtrl.GetHeaderCtrl();
    if (pHeaderCtrl == NULL)
    {
        AfxMessageBox(_T(ERR_MESSAGE_LST_CTRL));
        return;
    }

    if (oListCtrl.GetHeaderCtrl()->GetItemCount() == 0) {
        for (int i = 0; i < EUSER_COLUMN_COUNT; ++i) {
            oListCtrl.InsertColumn(i, gl_szColumnHeaders[i], LVCFMT_LEFT, gl_nColumnWidths[i]);
        }
    }

    CUsersDocument* pUsersDocument = GetDocument();
    if (pUsersDocument == NULL) {
        return;
    }

    CUsersArray& oUsersArray = pUsersDocument->GetUsers();

    for (int i = 0; i < oUsersArray.GetSize(); ++i) {
        USERS* pRecUser = oUsersArray.GetAt(i);
        if (pRecUser) {
            CString strID;
            strID.Format(_T("%ld"), pRecUser->lID);
            int index = oListCtrl.InsertItem(i, strID);
            oListCtrl.SetItemText(index, EUSER_COLUMN_NAME, pRecUser->szName);
            oListCtrl.SetItemText(index, EUSER_COLUMN_EMAIL, pRecUser->szEmail);

            JOB_TITLES recJobTitle;
            if (pUsersDocument->GetJobTitle(pRecUser->lJobTitleID, recJobTitle)) {
                oListCtrl.SetItemText(index, EUSER_COLUMN_JOB_TITLE, recJobTitle.szTitleName);
            }
            else {
               
                oListCtrl.SetItemText(index, EUSER_COLUMN_JOB_TITLE, _T(ERR_UNKNOWN));
            }
        }
    }
}

void CUsersView::OnUserEdit()
{
    CListCtrl& oListCtrl = GetListCtrl();
    int nSelectedItem = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

    if (nSelectedItem == -1)
    {
        AfxMessageBox(_T(ERR_NOT_SELECTED_USER_EDIT), MB_ICONINFORMATION);
        return;
    }

    CUsersDocument* pUsersDocument = GetDocument();
    if (pUsersDocument == NULL)
    {
        return;
    }

    CString strID = oListCtrl.GetItemText(nSelectedItem, EUSER_COLUMN_ID); 
    //!!!
    long lID = _ttol(strID);


    USERS* pUserToEdit = nullptr;
    CUsersArray& oUsersArray = pUsersDocument->GetUsers();
    for (INT_PTR i = 0; i < oUsersArray.GetSize(); ++i) {
        USERS* pUser = oUsersArray.GetAt(i);
        if (pUser && pUser->lID == lID) {
            pUserToEdit = pUser;
            break;
        }
    }

    if (pUserToEdit) {
        CUsersDlg oUsersDlg;
        oUsersDlg.m_recUser = *pUserToEdit;
        if (oUsersDlg.DoModal() == IDOK) {

            if (pUsersDocument->EditUser(lID, oUsersDlg.m_recUser)) {
                AfxMessageBox(_T(SCS_USER_UPDATE));
            }
            else {
                AfxMessageBox(_T(ERR_USER_UPDATE), MB_ICONERROR);
            }
        }
    }
    else {
        AfxMessageBox(_T(ERR_USER_NOT_FOUND), MB_ICONERROR);
    }
}

void CUsersView::OnUserAdd() 
{
    CUsersDlg oUsersDlg; 
    if (oUsersDlg.DoModal() == IDOK) {
        CUsersDocument* pDoc = GetDocument();
        if (pDoc == NULL)
        {
            return;
        }
        if (pDoc) {
            if (pDoc->AddNewUser(oUsersDlg.m_recUser)) {
                AfxMessageBox(_T(SCS_USER_ADD));
            }
            else {
                AfxMessageBox(_T(ERR_USER_ADD), MB_ICONERROR);
            }
        }
    }
}

void CUsersView::OnUserDelete()
{
    CListCtrl& oListCtrl = GetListCtrl();
    int nSelectedItem = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

    if (nSelectedItem == -1) {
        AfxMessageBox(_T(ERR_NOT_SELECTED_USER_DELETE), MB_ICONINFORMATION);
        return;
    }

    if (AfxMessageBox(_T(CONF_DELETE_USER), MB_YESNO | MB_ICONQUESTION) == IDNO) {
        return;
    }

    CUsersDocument* pUsersDocument = GetDocument();
    if (pUsersDocument == NULL)
    {
        return;
    }

    CString strID = oListCtrl.GetItemText(nSelectedItem, EUSER_COLUMN_ID);
    long lID = _ttol(strID);

    if (pUsersDocument->DeleteUser(lID)) {
        AfxMessageBox(_T(SCS_USER_DELETE));
    }
    else {
        AfxMessageBox(_T(ERR_USER_DELETE), MB_ICONERROR);
    }
}

// Overrides
// ----------------
BOOL CUsersView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
    return CListView::PreCreateWindow(cs);
}

void CUsersView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
    PopulateUsersList();
}

void CUsersView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CListView::OnUpdate(pSender, lHint, pHint);
    PopulateUsersList();
}

#ifdef _DEBUG
void CUsersView::AssertValid() const
{
	CListView::AssertValid();
}

void CUsersView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

void CUsersView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CMenu menu;
    if (!menu.LoadMenu(IDR_USERS_CONTEXT)) 
        return;

    CMenu* pContextMenu = menu.GetSubMenu(0);
    if (!pContextMenu)
        return;

    pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CUsersView::OnLButtonDblClk(UINT nFlags, CPoint point) {
    CListCtrl& listCtrl = GetListCtrl();

    int nItem = listCtrl.HitTest(point);
    if (nItem != -1)
    {
        listCtrl.SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        OnUserEdit();
    }

    CListView::OnLButtonDblClk(nFlags, point);
}

#endif 