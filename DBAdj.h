#if !defined(AFX_DBADJ_H__80D19D16_29CF_4264_B920_C005DC34E8A5__INCLUDED_)
#define AFX_DBADJ_H__80D19D16_29CF_4264_B920_C005DC34E8A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBAdj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBAdjustment dialog

class CDBAdjustment : public CDialog
{
// Construction
public:
	CDBAdjustment(CString* pstrTableName, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBAdjustment)
	enum { IDD = IDD_DBADJUSTMENT };
	//}}AFX_DATA
	CString&	m_strTableName;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBAdjustment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBAdjustment)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBADJ_H__80D19D16_29CF_4264_B920_C005DC34E8A5__INCLUDED_)
