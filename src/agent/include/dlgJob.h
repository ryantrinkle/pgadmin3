//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// Copyright (C) 2002 - 2003, The pgAdmin Development Team
// This software is released under the Artistic Licence
//
// dlgJob.h - Job property
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_JOBPROP
#define __DLG_JOBPROP

#include "dlgProperty.h"

class pgaJob;

class dlgJob : public dlgOidProperty
{
public:
    dlgJob(frmMain *frame, pgaJob *j);
    int Go(bool modal);

    wxString GetUpdateSql();
    wxString GetInsertSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();

private:
    pgaJob *job;
    void OnChange(wxNotifyEvent &ev);
    void OnChangeStep(wxNotifyEvent &ev);
    void OnAddStep(wxNotifyEvent &ev);
    void OnRemoveStep(wxNotifyEvent &ev);
    void OnChangeSchedule(wxNotifyEvent &ev);
    void OnAddSchedule(wxNotifyEvent &ev);
    void OnRemoveSchedule(wxNotifyEvent &ev);
       

    DECLARE_EVENT_TABLE();
};


#endif
