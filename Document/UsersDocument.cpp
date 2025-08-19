#include "pch.h"
#include "UsersDocument.h"
#include <UsersAppService.h>
#include <JobTitleAppService.h>



/////////////////////////////////////////////////////////////////////////////


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
CUsersArray& CUsersDocument::GetUsers() {

    return this->m_oUsersArray;
}


bool CUsersDocument::AddNewUser(USERS& newUser)
{

    if (!CUsersAppService().AddUser(newUser)) {
        return false;
    }
    LoadUsers();
    return true;
}

bool CUsersDocument::EditUser(const long lID,USERS& updatedUser)
{
    if (!CUsersAppService().UpdateUser(lID,updatedUser)) {
        return false;
    }
    LoadUsers();
    return true;
}

bool CUsersDocument::DeleteUser(const long lID)
{
    if (!CUsersAppService().DeleteUser(lID)) {
        return false;
    }
    LoadUsers();
    return true;
}

bool CUsersDocument::GetJobTitle(const long lID, JOB_TITLES& recJobTitle)
{
    if (!CJobTitlesAppService().GetJobByID(lID, recJobTitle)) {
        return false;
    }
    return true;
}

void CUsersDocument::LoadUsers()
{
    m_oUsersArray.ClearAll();
    if (CUsersAppService().GetAllUsers(m_oUsersArray)) {
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
	CDocument::OnCloseDocument();
}