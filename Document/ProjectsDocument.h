#pragma once
#include "DLLExport.h"
#include "ProjectsAppService.h"

class CProjectsDocument : public CDocument
{
protected:
    DECLARE_DYNCREATE(CProjectsDocument)
public:
    CProjectsDocument();
    virtual ~CProjectsDocument();


    virtual BOOL OnNewDocument() override;
    virtual void OnCloseDocument();

    bool AddProject(PROJECTS& project);
    bool UpdateProject(const long lID,PROJECTS& project);
    bool DeleteProject(const long lID);
    CProjectsArray& GetProjectsArray();
private:
    void LoadProjects();
private:
    CProjectsArray m_oProjectsArray;
};