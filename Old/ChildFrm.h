// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__4BC03EF6_FF17_47D0_B9B0_0A8A5C5FCD10__INCLUDED_)
#define AFX_CHILDFRM_H__4BC03EF6_FF17_47D0_B9B0_0A8A5C5FCD10__INCLUDED_

#include "SizeCtrlBar\SCBarCF.h"
#include "3DTABVWS\OX3DTabView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrame : public CMDIChildWnd
{
	class CTabViewContainer : public COX3DTabViewContainer  
	{
	public:
		virtual bool Initialize(CChildFrame* pFrame);
		CTabViewContainer();
		virtual ~CTabViewContainer();
	protected:
		//{{AFX_MSG(CChildFrame::CTabViewContainer)
		afx_msg BOOL OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	private:
		CChildFrame* m_pFrame;
	};
	
DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CSplitterWnd m_Data_SQLReqSplitter;
	
	CReBar				m_wndReBar;
	CTabViewContainer&	m_TabViewContainer;
	
	CSizingControlBarCF	m_wndMyBar;
	
	CDialogBar			m_wndDlgBar;

	friend class CTabViewContainer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__4BC03EF6_FF17_47D0_B9B0_0A8A5C5FCD10__INCLUDED_)
