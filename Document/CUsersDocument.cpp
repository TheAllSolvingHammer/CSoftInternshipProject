#include "pch.h"
#include "CUsersDocument.h"

/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectDocument

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CUsersDocument, CDocument)

// Constructor / Destructor
// ----------------
CUsersDocument::CUsersDocument() noexcept
{
}

CUsersDocument::~CUsersDocument()
{
}

// Methods
// ----------------
void CUsersDocument::FreeUsersMemory() {
	for (INT_PTR i = 0; i < m_oUsersArray.GetCount(); ++i) {
		delete m_oUsersArray.GetAt(i);
	}
	m_oUsersArray.RemoveAll();
}
bool CUsersDocument::AddNewUser(USERS& newUser)
{

    if (m_oUserAppService.AddUser(newUser)) {
        LoadUsers();
        return true;
    }
    return false;

}
bool CUsersDocument::EditUser(long lID,USERS& updatedUser)
{
    if (m_oUserAppService.UpdateUser(lID,updatedUser)) {
        LoadUsers();
        return true;
    }
    return false;
}
bool CUsersDocument::DeleteUser(long lID)
{
    if (m_oUserAppService.DeleteUser(lID)) {
        LoadUsers();
        return true;
    }
    return false;
}

void CUsersDocument::GetJobTitle(long lID, JOB_TITLES& recJobTitle)
{
    m_oJobTitlesAppService.GetJobByID(lID, recJobTitle);
}

CUsersAppService& CUsersDocument::GetService() {
    return this->m_oUserAppService;
}

void CUsersDocument::LoadUsers()
{
    FreeUsersMemory();
    if (m_oUserAppService.GetAllUsers(m_oUsersArray)) {
        UpdateAllViews(NULL);
    }
    else {
        AfxMessageBox(_T("Failed to load users."));
    }
}
// Overrides
// ----------------


BOOL CUsersDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	LoadUsers();
	return TRUE;
}

void CUsersDocument::OnCloseDocument() 
{
	FreeUsersMemory();
	CDocument::OnCloseDocument();
}