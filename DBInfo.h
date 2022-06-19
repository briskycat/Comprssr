#if !defined(AFX_DBINFO_H__CB9191C0_BE55_41A6_A362_5DFEB29988EA__INCLUDED_)
#define AFX_DBINFO_H__CB9191C0_BE55_41A6_A362_5DFEB29988EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBInfo dialog

class CDBInfo : public CDialog
{
	/////////////////////////////////////////////////////////////////////////////
	// CTables - results from SQLTables (borrowed from Catalog2 sample)

	class CTables : public CRecordset
	{
		virtual CString GetDefaultConnect() { return ""; }
		virtual CString GetDefaultSQL() { return ""; }

	public:
		CTables(CDatabase* pDatabase);
		BOOL Open(LPCSTR pszTableQualifier = NULL,
			LPCSTR pszTableOwner = NULL,
			LPCSTR pszTableName = NULL,
			LPCSTR pszTableType = NULL,
			UINT nOpenType = forwardOnly);

		CString m_strTableQualifier;
		CString m_strTableOwner;
		CString m_strTableName;
		CString m_strTableType;
		CString m_strRemarks;

		virtual void DoFieldExchange(CFieldExchange*);
	};

// Construction
public:
	CDBInfo(CDatabase* const pDB, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CDBInfo)
	enum { IDD = IDD_DBINFO };
	CListBox	m_tableList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDatabase*	const m_pDB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBINFO_H__CB9191C0_BE55_41A6_A362_5DFEB29988EA__INCLUDED_)
