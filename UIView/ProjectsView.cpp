#include "pch.h"
#include "framework.h"
#include "ProjectsView.h"

#include "ProjectDlg.h"

#include "CUsersDlg.h"
#include <Users.h>
#include "Resource.h"
#include "../Application/UsersAppService.h"
#include "../Application/ProjectsAppService.h"

#define ERR_MESSAGE_SAFE_HWND               "Error in getting the safe HWND"
#define ERR_MESSAGE_LST_CTRL                "Error in getting the header of the list control"
#define ERR_UNKNOWN                         "Unknown"
#define ERR_NOT_SELECTED_USER_EDIT          "Please select a project to edit."
#define SCS_PROJECT_UPDATE                  "Project updated successfully!"
#define ERR_PROJECT_UPDATE                  "Failed to update project."
#define ERR_PROJECT_NOT_FOUND               "Selected project not found in document data."


#define SCS_PROJECT_ADD                     "Project added successfully!"
#define ERR_PROJECT_ADD                     "Failed to add project."

#define ERR_NOT_SELECTED_PROJECT_DELETE     "Please select a project to delete."
#define CONF_PROJECT_DELETE                   "Are you sure to delete the selected project?"

#define SCS_PROJECT_DELETE                  "project deleted successfully!"
#define ERR_PROJECT_DELETE                  "Failed to delete project."

/////////////////////////////////////////////////////////////////////////////
//CUsersView

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CProjectsView, CListView)


BEGIN_MESSAGE_MAP(CProjectsView, CListView)
    ON_COMMAND(ID_MENU_INSERT, &CProjectsView::OnProjectAdd)
    ON_COMMAND(ID_MENU_UPDATE, &CProjectsView::OnProjectEdit)
    ON_COMMAND(ID_MENU_DELETE, &CProjectsView::OnProjectDelete)
    ON_WM_CONTEXTMENU()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CProjectsView::CProjectsView() noexcept
{
}

CProjectsView::~CProjectsView()
{
}

// Methods
// ----------------
CProjectsDocument* CProjectsView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectsDocument)));
    return (CProjectsDocument*)m_pDocument;
}


// MFC Message Handlers
// ----------------


//Methods
// ----------------
void CProjectsView::PopulateProjectsList()
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
        for (int i = 0; i < PROJECT_COLUMN_COUNT; ++i) {
            oListCtrl.InsertColumn(i, gl_szColumnHeadersProject[i], LVCFMT_LEFT, gl_nColumnWidthsProject[i]);
        }
    }

    CProjectsDocument* pProjectsDocument = GetDocument();
    if (pProjectsDocument == NULL) {
        return;
    }

    CProjectsArray& oProjectsArray = pProjectsDocument->GetProjectsArray();

    for (int i = 0; i < oProjectsArray.GetSize(); ++i) {
        PROJECTS* pRecProject = oProjectsArray.GetAt(i);
        if (pRecProject) {
            CString strID;
            strID.Format(_T("%ld"), pRecProject->lID);
            int index = oListCtrl.InsertItem(i, strID);
            oListCtrl.SetItemText(index, PROJECT_COLUMN_NAME, pRecProject->szName);
            oListCtrl.SetItemText(index, PROJECT_COLUMN_DESCRIPTION, pRecProject->szDescription);

            USERS recUser;
            if (pProjectsDocument->GetUser(pRecProject->lProjectManagerID, recUser)) {
                oListCtrl.SetItemText(index, PROJECT_COLUMN_PROJECT_MANAGER, recUser.szName);
            }
            else {

                oListCtrl.SetItemText(index, PROJECT_COLUMN_PROJECT_MANAGER, _T(ERR_UNKNOWN));
            }

            oListCtrl.SetItemText(index, PROJECT_COLUMN_STATUS, _T(ERR_UNKNOWN));
            for (int i = 0;i < PROJECT_STATE_COUNT;i++) {
                if (pRecProject->sProjectStatus = i + 1) {
                    oListCtrl.SetItemText(index, PROJECT_COLUMN_STATUS, gl_szProjectStateDescription[i]);
                    break;
                }
            }
            CString strEffort;
            strEffort.Format(_T("%d"), pRecProject->nTotalEffort);
            oListCtrl.SetItemText(index, PROJECT_COLUMN_EFFORT, strEffort.GetString());
        }
    }
}

void CProjectsView::OnProjectEdit()
{
    CListCtrl& oListCtrl = GetListCtrl();
    int nSelectedItem = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

    if (nSelectedItem == -1)
    {
        AfxMessageBox(_T(ERR_NOT_SELECTED_USER_EDIT), MB_ICONINFORMATION);
        return;
    }

    CProjectsDocument* pProjectsDocument = GetDocument();
    if (pProjectsDocument == NULL)
    {
        return;
    }

    CString strID = oListCtrl.GetItemText(nSelectedItem, PROJECT_COLUMN_ID);
    long lID = _ttol(strID);

    PROJECTS* pProjectToEdit = nullptr;
    CProjectsArray& oProjectsArray = pProjectsDocument->GetProjectsArray();
    for (INT_PTR i = 0; i < oProjectsArray.GetCount(); i++) {
        PROJECTS* pRecProject = oProjectsArray.GetAt(i);
        if (pRecProject && pRecProject->lID == lID) {
            pProjectToEdit = pRecProject;
            break;
        }
    }

    if (pProjectToEdit) {
        CUsersArray oUsersArray;
        CTasksArray oTasksArray;
        if (!(pProjectsDocument->GetAllUsers(oUsersArray)))
        {
            AfxMessageBox(_T("Failed to load users"));
            return;
        }
        if (!(pProjectsDocument->GetTasksByProject(pProjectToEdit->lID, oTasksArray)))
        {
	        AfxMessageBox(_T("Failed to load Tasks"));
            return;
        }

        CProjectDlg oProjectDlg(NULL, *pProjectToEdit, oUsersArray, oTasksArray);
        
        if (oProjectDlg.DoModal() == IDOK) {

            if (pProjectsDocument->UpdateProject(lID, oProjectDlg.m_recProject)) {
                AfxMessageBox(_T(SCS_PROJECT_UPDATE));
            }
            else {
                AfxMessageBox(_T(ERR_PROJECT_UPDATE), MB_ICONERROR);
            }
        }
    }
    else {
        AfxMessageBox(_T(ERR_PROJECT_NOT_FOUND), MB_ICONERROR);
    }
}

void CProjectsView::OnProjectAdd()
{
    CProjectDlg oProjectDlg;
    if (oProjectDlg.DoModal() == IDOK) {
        CProjectsDocument* pDoc = GetDocument();
        if (pDoc == NULL)
        {
            return;
        }
        if (pDoc) {
            if (pDoc->AddProject(oProjectDlg.m_recProject)) {
                AfxMessageBox(_T(SCS_PROJECT_ADD));
            }
            else {
                AfxMessageBox(_T(ERR_PROJECT_ADD), MB_ICONERROR);
            }
        }
    }
}

void CProjectsView::OnProjectDelete()
{
    CListCtrl& oListCtrl = GetListCtrl();
    int nSelectedItem = oListCtrl.GetNextItem(-1, LVNI_SELECTED);

    if (nSelectedItem == -1) {
        AfxMessageBox(_T(ERR_NOT_SELECTED_PROJECT_DELETE), MB_ICONINFORMATION);
        return;
    }

    if (AfxMessageBox(_T(CONF_PROJECT_DELETE), MB_YESNO | MB_ICONQUESTION) == IDNO) {
        return;
    }

    CProjectsDocument* pProjectsDocument = GetDocument();
    if (pProjectsDocument == NULL)
    {
        return;
    }

    CString strID = oListCtrl.GetItemText(nSelectedItem, PROJECT_COLUMN_ID);
    long lID = _ttol(strID);

    if (pProjectsDocument->DeleteProject(lID)) {
        AfxMessageBox(_T(SCS_PROJECT_DELETE));
    }
    else {
        AfxMessageBox(_T(ERR_PROJECT_DELETE), MB_ICONERROR);
    }
}

// Overrides
// ----------------
BOOL CProjectsView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
    return CListView::PreCreateWindow(cs);
}

void CProjectsView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();
    GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
    PopulateProjectsList();
}

void CProjectsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CListView::OnUpdate(pSender, lHint, pHint);
    PopulateProjectsList();
}

#ifdef _DEBUG
void CProjectsView::AssertValid() const
{
    CListView::AssertValid();
}

void CProjectsView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}

void CProjectsView::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CMenu menu;
    if (!menu.LoadMenu(IDR_MENU_CONTEXT))
        return;

    CMenu* pContextMenu = menu.GetSubMenu(0);
    if (!pContextMenu)
        return;

    pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CProjectsView::OnLButtonDblClk(UINT nFlags, CPoint point) {
    CListCtrl& listCtrl = GetListCtrl();

    int nItem = listCtrl.HitTest(point);
    if (nItem != -1)
    {
        listCtrl.SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        OnProjectEdit();
    }

    CListView::OnLButtonDblClk(nFlags, point);
}

#endif 