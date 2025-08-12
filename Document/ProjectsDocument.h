#pragma once
#include "DLLExport.h"
#include <Projects.h>
#include <Users.h>
#include "Tasks.h"

#define MSG_ERR_LOAD_USERS _T("Failed to load users.")

class DocumentDLL_EXP CProjectsDocument : public CDocument
{
protected:
    DECLARE_DYNCREATE(CProjectsDocument)

public:
    CProjectsDocument();
    virtual ~CProjectsDocument();
    bool AddProject(PROJECTS& recProject);
    bool UpdateProject(const long lID,PROJECTS& recProject);
    bool DeleteProject(const long lID);
    bool GetUser(const long lID, USERS& recUser);
    bool GetAllUsers(CUsersArray& oUsersArray);
    bool GetTasksByProject(const long lID, CTasksArray& oTasksArray);
    CProjectsArray& GetProjectsArray();
public:
    virtual BOOL OnNewDocument() override;
    virtual void OnCloseDocument();
private:
    void LoadProjects();
private:
    CProjectsArray m_oProjectsArray;
    
};