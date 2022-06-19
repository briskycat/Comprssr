// CprsView.h : interface of the CCompressorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPRSVIEW_H__BB9B2C97_F372_4CBB_BF34_371A3CA7B86D__INCLUDED_)
#define AFX_CPRSVIEW_H__BB9B2C97_F372_4CBB_BF34_371A3CA7B86D__INCLUDED_

#include ".\GridCtrl\GridCtrl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCompressorView : public CView
{
protected: // create from serialization only
	CCompressorView();
	DECLARE_DYNCREATE(CCompressorView)

// Attributes
public:
	CCompressorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCompressorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCompressorView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGridCtrl m_Grid;
};

#ifndef _DEBUG  // debug version in CprsView.cpp
inline CCompressorDoc* CCompressorView::GetDocument()
   { return (CCompressorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPRSVIEW_H__BB9B2C97_F372_4CBB_BF34_371A3CA7B86D__INCLUDED_)
