#if !defined(AFX_SQLREQVW_H__630DF542_4FBE_4FE7_9E3B_D9B4155028A2__INCLUDED_)
#define AFX_SQLREQVW_H__630DF542_4FBE_4FE7_9E3B_D9B4155028A2__INCLUDED_

#include "CprsDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SQLReqVw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQLRequestView view

class CSQLRequestView : public CEditView
{
protected:
	CSQLRequestView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSQLRequestView)

// Attributes
public:
	CCompressorDoc* GetDocument(){return reinterpret_cast<CCompressorDoc*>(m_pDocument);}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLRequestView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSQLRequestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSQLRequestView)
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLREQVW_H__630DF542_4FBE_4FE7_9E3B_D9B4155028A2__INCLUDED_)
