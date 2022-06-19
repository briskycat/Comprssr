#if !defined(AFX_DATAVIEW_H__D9A6862F_5600_40C7_97F3_652BE03BD012__INCLUDED_)
#define AFX_DATAVIEW_H__D9A6862F_5600_40C7_97F3_652BE03BD012__INCLUDED_

#include "CprsDoc.h"
#include "GRIDCTRL\GridCtrl.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataView view

class CDataView : public CView
{
protected:
	CDataView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDataView)

// Attributes
public:
	CCompressorDoc* GetDocument(){return reinterpret_cast<CCompressorDoc*>(m_pDocument);}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDataView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillFromDoc();
	void FillFromDB();
	CGridCtrl m_Grid;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAVIEW_H__D9A6862F_5600_40C7_97F3_652BE03BD012__INCLUDED_)
