// ChildTab.cpp: implementation of the CChildTab class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comprssr.h"
#include "ChildTab.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChildTab::CChildTab()
{

}

CChildTab::~CChildTab()
{

}

BEGIN_MESSAGE_MAP(CChildTab, COX3DTabViewContainer)
    //{{AFX_MSG_MAP(CChildTab)
    ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, OnSelchange)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// Description: Selection change handler
//////////////////////////////////////////////////////////////////////////////
BOOL CChildTab::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COX3DTabViewContainer::OnSelchange(pNMHDR, pResult);

	MessageBox("Sel.Changed!");

    return FALSE;
}

