#pragma once
#include "DLLExport.h"
#include <Projects.h>
#include <Users.h>
#include "Tasks.h"

#define MSG_ERR_LOAD_USERS _T("Failed to load users.")

enum UpdateHint
{
    HINT_NONE = 0,
    HINT_PROJECT_ADDED,
    HINT_PROJECT_UPDATED,
    HINT_PROJECT_DELETED,
    HINT_TASK_ADDED,
    HINT_TASK_UPDATED,
    HINT_TASK_DELETED
};

class DocumentDLL_EXP CProjectsDocument : public CDocument
{
protected:
    DECLARE_DYNCREATE(CProjectsDocument)

public:
    CProjectsDocument();
    virtual ~CProjectsDocument();
    bool AddProject(PROJECTS& recProject);
    bool UpdateProject(PROJECTS& recProject, CTasksArray& oTasksArray, CTasksArray& oUpdatedTasksArray, CTasksArray& oDeletedTasksArray);
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
    void LoadSingleProject(PROJECTS& recProject);
    void DeleteSingleProject(const long lID);
private:
    CProjectsArray m_oProjectsArray;
    
};