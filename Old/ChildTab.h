// ChildTab.h: interface for the CChildTab class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDTAB_H__E59CC3AB_B2FD_4D6C_A277_F9CD94B899FB__INCLUDED_)
#define AFX_CHILDTAB_H__E59CC3AB_B2FD_4D6C_A277_F9CD94B899FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3DTABVWS\OX3DTabView.h"

class CChildTab : public COX3DTabViewContainer  
{
public:
	CChildTab();
	virtual ~CChildTab();
protected:
    //{{AFX_MSG(CChildTab)
	afx_msg BOOL OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CHILDTAB_H__E59CC3AB_B2FD_4D6C_A277_F9CD94B899FB__INCLUDED_)
