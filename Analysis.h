#if !defined(AFX_ANALYSIS_H__E969F388_C952_4732_BFC5_42C33464F0D5__INCLUDED_)
#define AFX_ANALYSIS_H__E969F388_C952_4732_BFC5_42C33464F0D5__INCLUDED_

#include "CprsDoc.h"
#include "Graphics\Scatter.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Analysis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView view

class CAnalysisView : public CView
{
protected:
	CAnalysisView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAnalysisView)

// Attributes
public:
	CCompressorDoc* GetDocument(){return reinterpret_cast<CCompressorDoc*>(m_pDocument);}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAnalysisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnalysisView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strGraphTitle;
	CString m_strXAxisTitle;
	CString m_strYAxisTitle;
	CLinear<double>					m_graph;
	std::vector<CTPoint<double> >	m_pt;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYSIS_H__E969F388_C952_4732_BFC5_42C33464F0D5__INCLUDED_)
