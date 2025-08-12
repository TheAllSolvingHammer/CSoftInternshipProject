#pragma once
#include "DLLExport.h"
#include <Projects.h>
#include <Users.h>


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
    CProjectsArray& GetProjectsArray();
public:
    virtual BOOL OnNewDocument() override;
    virtual void OnCloseDocument();
private:
    void LoadProjects();
private:
    CProjectsArray m_oProjectsArray;
};