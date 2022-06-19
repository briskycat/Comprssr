#if !defined(AFX_CPRNVIEW_H__73FCC3AA_2435_4CF6_AA4B_025F4D8309FB__INCLUDED_)
#define AFX_CPRNVIEW_H__73FCC3AA_2435_4CF6_AA4B_025F4D8309FB__INCLUDED_

#include "CprsDoc.h"
#include "GRIDCTRL\GridCtrl.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CprnView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompressionView view

class CCompressionView : public CView
{
protected:
	CCompressionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCompressionView)

// Attributes
public:
	CCompressorDoc* GetDocument(){return reinterpret_cast<CCompressorDoc*>(m_pDocument);}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressionView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCompressionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCompressionView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGridCtrl m_Grid;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPRNVIEW_H__73FCC3AA_2435_4CF6_AA4B_025F4D8309FB__INCLUDED_)
