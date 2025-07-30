#include "pch.h"
#include "CSoftInternshipProjectDoc.h"

/////////////////////////////////////////////////////////////////////////////
//CCSoftInternshipProjectDocument

// Macros
// ----------------
IMPLEMENT_DYNCREATE(CCSoftInternshipProjectDocument, CDocument)

// Constructor / Destructor
// ----------------
CCSoftInternshipProjectDocument::CCSoftInternshipProjectDocument() noexcept
{
}

CCSoftInternshipProjectDocument::~CCSoftInternshipProjectDocument()
{
}

// Methods
// ----------------
void CCSoftInternshipProjectDocument::FreeUsersMemory() {
	for (INT_PTR i = 0; i < m_oUsersArray.GetCount(); ++i) {
		delete m_oUsersArray.GetAt(i);
	}
	m_oUsersArray.RemoveAll();
}
bool CCSoftInternshipProjectDocument::AddNewUser(USERS& newUser)
{

    if (m_oUserAppService.AddUser(newUser)) {
        LoadUsers();
        return true;
    }
    return false;

}
bool CCSoftInternshipProjectDocument::EditUser(long lID,USERS& updatedUser)
{
    if (m_oUserAppService.UpdateUser(lID,updatedUser)) {
        LoadUsers();
        return true;
    }
    return false;
}
bool CCSoftInternshipProjectDocument::DeleteUser(long lID)
{
    if (m_oUserAppService.DeleteUser(lID)) {
        LoadUsers();
        return true;
    }
    return false;
}

void CCSoftInternshipProjectDocument::GetJobTitle(long lID, JOB_TITLES& recJobTitle)
{
    m_oJobTitlesAppService.GetJobByID(lID, recJobTitle);
}

CUsersAppService& CCSoftInternshipProjectDocument::GetService() {
    return this->m_oUserAppService;
}

void CCSoftInternshipProjectDocument::LoadUsers()
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


BOOL CCSoftInternshipProjectDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	LoadUsers();
	return TRUE;
}

void CCSoftInternshipProjectDocument::OnCloseDocument() 
{
	FreeUsersMemory();
	CDocument::OnCloseDocument();
}