#pragma once
#include "UsersTable.h"
#include "DatabaseTables.h"

class CDatabaseContext {
public:
    CDataSource oDataSource;
    CSession oSession;

    bool Connect() {
      //  return OpenConnection(oDataSource, oSession); 
    }

    void Disconnect() {
       // CloseAll(oDataSource, oSession); 
    }
};