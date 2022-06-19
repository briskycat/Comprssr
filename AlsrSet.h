#if !defined(AFX_ALSRSET_H__1A859C3F_C77E_4970_A592_BCC92B4B2CDE__INCLUDED_)
#define AFX_ALSRSET_H__1A859C3F_C77E_4970_A592_BCC92B4B2CDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlsrSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnalyserSettings dialog

class CAnalyserSettings : public CDialog
{
// Construction
public:
	CAnalyserSettings(double* pInfFactor, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnalyserSettings)
	enum { IDD = IDD_ANALYSERSETTINGS };
	//}}AFX_DATA
	double&	m_infFactor;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalyserSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnalyserSettings)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALSRSET_H__1A859C3F_C77E_4970_A592_BCC92B4B2CDE__INCLUDED_)
