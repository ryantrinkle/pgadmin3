//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// Copyright (C) 2002 - 2003, The pgAdmin Development Team
// This software is released under the Artistic Licence
//
// dlgSchedule.h - Job property
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_SCHEDULEPROP
#define __DLG_SCHEDULEPROP

#include "dlgProperty.h"

class pgaSchedule;
class pgaJob;

class dlgSchedule : public dlgOidProperty
{
public:
    dlgSchedule(frmMain *frame, pgaSchedule *s, pgaJob *j);
    int Go(bool modal);

    wxString GetUpdateSql();
    wxString GetInsertSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();
    void SetJobOid(OID oid) { jobOid = oid; }

private:
    OID jobOid;
    pgaSchedule *schedule;
    pgaJob *job;
    void OnChange(wxNotifyEvent &ev);

    DECLARE_EVENT_TABLE();
};


#endif
