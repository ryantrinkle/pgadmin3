//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// Copyright (C) 2002, The pgAdmin Development Team
// This software is released under the pgAdmin Public Licence
//
// pgUser.cpp - PostgreSQL User
//
//////////////////////////////////////////////////////////////////////////

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "pgAdmin3.h"
#include "misc.h"
#include "pgObject.h"
#include "pgUser.h"
#include "pgCollection.h"
#include "frmMain.h"


pgUser::pgUser(const wxString& newName)
: pgObject(PG_USER, newName)
{
    wxLogInfo(wxT("Creating a pgUser object"));
}

pgUser::~pgUser()
{
    wxLogInfo(wxT("Destroying a pgUser object"));
}



wxString pgUser::GetSql(wxTreeCtrl *browser)
{
    if (sql.IsNull())
    {
        sql = wxT("CREATE User ") + GetQuotedIdentifier()
            + wxT(" WITH SYSID ") + NumToStr(userId);
        if (!password.IsNull())
            sql += wxT(" PASSWORD ENCRYPTED ") + GetPassword();
        if (GetCreateDatabase())    sql += wxT(" CREATEDB");
        else                        sql += wxT(" NOCREATEDB");
        if (GetUpdateCatalog())     sql += wxT(" CREATEUSER");
        else                        sql += wxT(" NOCREATEUSER");
        if (!accountExpires.IsNull())
            sql += wxT(" VALID UNTIL ") + GetAccountExpires();
        sql +=wxT(";\n");
    }
    return sql;
}


void pgUser::ShowTreeDetail(wxTreeCtrl *browser, frmMain *form, wxListCtrl *properties, wxListCtrl *statistics, ctlSQLBox *sqlPane)
{
    if (properties)
    {
        wxLogInfo(wxT("Displaying properties for User ") + GetIdentifier());

        properties->ClearAll();
        properties->InsertColumn(0, wxT("Property"), wxLIST_FORMAT_LEFT, 150);
        properties->InsertColumn(1, wxT("Value"), wxLIST_FORMAT_LEFT, 200);
  

        int pos=0;

        InsertListItem(properties, pos++, wxT("Name"), GetName());
        InsertListItem(properties, pos++, wxT("Account Expires"), GetAccountExpires());
        InsertListItem(properties, pos++, wxT("Superuser?"), BoolToYesNo(GetSuperuser()));
        InsertListItem(properties, pos++, wxT("Create Database?"), BoolToYesNo(GetCreateDatabase()));
        InsertListItem(properties, pos++, wxT("Update Catalog?"), BoolToYesNo(GetUpdateCatalog()));
        /*
        session default vars here?
        */
    }
}



void pgUser::ShowTreeCollection(pgCollection *collection, frmMain *form, wxTreeCtrl *browser, wxListCtrl *properties, wxListCtrl *statistics, ctlSQLBox *sqlPane)
{
    pgUser *user;

    if (browser->GetChildrenCount(collection->GetId(), FALSE) == 0)
    {

        // Log
        wxLogInfo(wxT("Adding Users to database"));


        // Get the Users
        pgSet *users= collection->GetServer()->ExecuteSet(wxT("SELECT * FROM pg_shadow"));

        if (users)
        {
            while (!users->Eof())
            {

                user = new pgUser(users->GetVal(wxT("usename")));
                user->iSetServer(collection->GetServer());
                user->iSetUserId(StrToLong(users->GetVal(wxT("usesysid"))));
                user->iSetCreateDatabase(StrToBool(users->GetVal(wxT("usecreatedb"))));
                user->iSetSuperuser(StrToBool(users->GetVal(wxT("usesuper"))));
                user->iSetUpdateCatalog(StrToBool(users->GetVal(wxT("usecatupd"))));
                user->iSetAccountExpires(users->GetVal(wxT("valuntil")));
                user->iSetPassword(users->GetVal(wxT("passwd")));

                browser->AppendItem(collection->GetId(), user->GetIdentifier(), PGICON_USER, -1, user);
	    
			    users->MoveNext();
            }

		    delete users;
        }
    }
}

