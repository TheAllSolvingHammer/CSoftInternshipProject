#include "pch.h"
#include "framework.h"
#include "CSoftInternshipProjectView.h"
#include "resource.h"
#include <CUsersTableDialog.h>



/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCSoftInternshipProjectView, CListView)

BEGIN_MESSAGE_MAP(CCSoftInternshipProjectView, CListView)
    ON_COMMAND(ID_MENU_INSERT_USER, &CCSoftInternshipProjectView::OnUserAdd)

    ON_COMMAND(ID_MENU_DELETE_USER, &CCSoftInternshipProjectView::OnUserDelete)
    ON_WM_CONTEXTMENU()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCSoftInternshipProjectView::CCSoftInternshipProjectView() noexcept
{
}

CCSoftInternshipProjectView::~CCSoftInternshipProjectView()
{
}

// Methods
// ----------------
CCSoftInternshipProjectDocument* CCSoftInternshipProjectView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSoftInternshipProjectDocument)));
	return (CCSoftInternshipProjectDocument*)m_pDocument;
}


// MFC Message Handlers
// ----------------


//Methods
// ----------------
void CCSoftInternshipProjectView::PopulateUsersList()
{
    CListCtrl& pLstCtrl = GetListCtrl(); 
    if (!pLstCtrl.GetSafeHwnd())
    {
        AfxMessageBox(_T("Error in getting the safe HWND"));
        return;
    }
    pLstCtrl.DeleteAllItems();

    CHeaderCtrl* pHeaderCtrl = pLstCtrl.GetHeaderCtrl();
    if (pHeaderCtrl == NULL)
    {
        AfxMessageBox(_T("Error in getting the header of the list control"));
        return;
    }
    if (pLstCtrl.GetHeaderCtrl()->GetItemCount() == 0) {
        pLstCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
        pLstCtrl.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
        pLstCtrl.InsertColumn(2, _T("Email"), LVCFMT_LEFT, 200);
        pLstCtrl.InsertColumn(3, _T("Job Title"), LVCFMT_LEFT, 150);
    }

    CCSoftInternshipProjectDocument* pDoc = GetDocument();
    if (pDoc == NULL) {
        return;
    }

    const CUsersArray& users = pDoc->GetUsers();

    for (int i = 0; i < users.GetSize(); ++i) {
        USERS* pUser = users.GetAt(i);
        if (pUser) {
            CString strID;
            strID.Format(_T("%ld"), pUser->lID);
            int index = pLstCtrl.InsertItem(i, strID);
            pLstCtrl.SetItemText(index, 1, pUser->szName);
            pLstCtrl.SetItemText(index, 2, pUser->szEmail);
            
            JOB_TITLES* pJobTitle = new JOB_TITLES();
            pDoc->GetJobTitle(pUser->lJobTitleID, *pJobTitle);
            pLstCtrl.SetItemText(index, 3, pJobTitle->szTitleName);
            delete pJobTitle;
        }
    }
}

void CCSoftInternshipProjectView::OnUserEdit()
{
    CListCtrl& refListCtrl = GetListCtrl();
    int nSel = refListCtrl.GetNextItem(-1, LVNI_SELECTED); 

    if (nSel == -1) 
    {
        AfxMessageBox(_T("Please select a user to edit."), MB_ICONINFORMATION);
        return;
    }

    CCSoftInternshipProjectDocument* pDoc = GetDocument();
    if (pDoc == NULL) 
    {
        return;
    }

    
    CString strID = refListCtrl.GetItemText(nSel, 0);
    long lID = _ttol(strID); 

   
    USERS* pUserToEdit = nullptr;
    const CUsersArray& users = pDoc->GetUsers();
    for (INT_PTR i = 0; i < users.GetSize(); ++i) {
        USERS* pUser = users.GetAt(i);
        if (pUser && pUser->lID == lID) {
            pUserToEdit = pUser;
            break;
        }
    }

    if (pUserToEdit) {
        CUsersTableDialog dlg;
        dlg.m_recUser = *pUserToEdit; 
        if (dlg.DoModal() == IDOK) {
           
            if (pDoc->EditUser(lID,dlg.m_recUser)) {
                AfxMessageBox(_T("User updated successfully!"));
            }
            else {
                AfxMessageBox(_T("Failed to update user."), MB_ICONERROR);
            }
        }
    }
    else {
        AfxMessageBox(_T("Selected user not found in document data."), MB_ICONERROR);
    }
}

void CCSoftInternshipProjectView::OnUserAdd() 
{
    CUsersTableDialog dlg; 
    if (dlg.DoModal() == IDOK) {
        CCSoftInternshipProjectDocument* pDoc = GetDocument();
        if (pDoc == NULL)
        {
            return;
        }
        if (pDoc) {
            if (pDoc->AddNewUser(dlg.m_recUser)) {
                AfxMessageBox(_T("User added successfully!"));
            }
            else {
                AfxMessageBox(_T("Failed to add user."), MB_ICONERROR);
            }
        }
    }
}

void CCSoftInternshipProjectView::OnUserDelete()
{
    CListCtrl& refListCtrl = GetListCtrl();
    int nSel = refListCtrl.GetNextItem(-1, LVNI_SELECTED);

    if (nSel == -1) {
        AfxMessageBox(_T("Please select a user to delete."), MB_ICONINFORMATION);
        return;
    }

    if (AfxMessageBox(_T("Are you sure you want to delete the selected user?"), MB_YESNO | MB_ICONQUESTION) == IDNO) {
        return;
    }

    CCSoftInternshipProjectDocument* pDoc = GetDocument();
    if (pDoc == NULL)
    {
        return;
    }

    CString strID = refListCtrl.GetItemText(nSel, 0);
    long lID = _ttol(strID);

    if (pDoc->DeleteUser(lID)) {
        AfxMessageBox(_T("User deleted successfully!"));
    }
    else {
        AfxMessageBox(_T("Failed to delete user."), MB_ICONERROR);
    }
}

// Overrides
// ----------------
BOOL CCSoftInternshipProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
    return CListView::PreCreateWindow(cs);
}

void CCSoftInternshipProjectView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
    PopulateUsersList();
}

void CCSoftInternshipProjectView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CListView::OnUpdate(pSender, lHint, pHint);
    PopulateUsersList();
}

#ifdef _DEBUG
void CCSoftInternshipProjectView::AssertValid() const
{
	CListView::AssertValid();
}

void CCSoftInternshipProjectView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

void CCSoftInternshipProjectView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CMenu menu;
    if (!menu.LoadMenu(IDR_USERS_CONTEXT)) 
        return;

    CMenu* pContextMenu = menu.GetSubMenu(0);
    if (!pContextMenu)
        return;

    pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CCSoftInternshipProjectView::OnLButtonDblClk(UINT nFlags, CPoint point) {
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