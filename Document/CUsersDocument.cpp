#include "pch.h"
#include "CUsersDocument.h"
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

    return CArrayManager::getInstance().GetCollectionRef<USERS>(COLLECTION_USERS);
}

CJobTitlesArray& CUsersDocument::GetJobTitles() {
    return CArrayManager::getInstance().GetCollectionRef<JOB_TITLES>(COLLECTION_JOB_TITLES);
}

CProjectsArray& CUsersDocument::GetProjects() {
    return CArrayManager::getInstance().GetCollectionRef<PROJECTS>(COLLECTION_PROJECTS);
}

CTasksArray& CUsersDocument::GetTasks() {
    return CArrayManager::getInstance().GetCollectionRef<TASKS>(COLLECTION_TASKS);
}

void CUsersDocument::FreeUsersMemory() {
	//for (INT_PTR i = 0; i < m_oUsersArray.GetCount(); ++i) {
	//	delete m_oUsersArray.GetAt(i);
	//}
	//m_oUsersArray.RemoveAll();
}

//обърни логика
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
    FreeUsersMemory();
    
    if (CUsersAppService().GetAllUsers()) {
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