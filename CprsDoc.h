// CprsDoc.h : interface of the CCompressorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPRSDOC_H__E6FF026C_1A3B_4032_BCC4_F925650E5E98__INCLUDED_)
#define AFX_CPRSDOC_H__E6FF026C_1A3B_4032_BCC4_F925650E5E98__INCLUDED_

#include "types.h"
#include "Analyser.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataSet : public DataSet, public CObject
{
public:
	virtual void Serialize(CArchive& ar);
	virtual ~CDataSet(){}
};

class CChain : public Chain, public CObject
{
public:
	virtual void Serialize(CArchive& ar);
	virtual ~CChain(){}
};

class CCompressorDoc : public CDocument
{
public:
	enum DockChangeType{SQLStatementChanged = 1, InputDataChanged, ResultsChanged, OutputDataChanged};
	enum Presentation{ViewDoc = 1, ViewDB};

protected: // create from serialization only
	CCompressorDoc();
	DECLARE_DYNCREATE(CCompressorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool IsQuerySQLStatement(const CString& rStr) const;
	virtual ~CCompressorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:

	CChain				m_chain;
	CDataSet			m_inputDataSet;
	CDataSet			m_outputDataSet;

	CString				m_strSQLStatement;
	CDatabase			m_db;

	CDatabase			m_outputDB;
	CString				m_strOutputTable;

	Presentation		m_presentation;

	static const short	m_version;
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCompressorDoc)
	afx_msg void OnOpendbase();
	afx_msg void OnUpdateExecrequest(CCmdUI* pCmdUI);
	afx_msg void OnDbaseinfo();
	afx_msg void OnUpdateDbaseinfo(CCmdUI* pCmdUI);
	afx_msg void OnExecrequest();
	afx_msg void OnUpdateViewdb(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewdoc(CCmdUI* pCmdUI);
	afx_msg void OnViewdb();
	afx_msg void OnViewdoc();
	afx_msg void OnAnalyze();
	afx_msg void OnAnalyserSettings();
	afx_msg void OnUpdateAnalyze(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInitCompressor(CCmdUI* pCmdUI);
	afx_msg void OnInitCompressor();
	afx_msg void OnUpdateCompress(CCmdUI* pCmdUI);
	afx_msg void OnCompress();
	afx_msg void OnUpdateDecompress(CCmdUI* pCmdUI);
	afx_msg void OnDecompress();
	afx_msg void OnOpenOutputDB();
	afx_msg void OnOutputDBInfo();
	afx_msg void OnOutputDBAdjustment();
	afx_msg void OnUpdateSaveProcessedData(CCmdUI* pCmdUI);
	afx_msg void OnSaveProcessedData();
	afx_msg void OnUpdateOutputDBAdjustment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutputDBInfo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillFromDB();
private:
	Analyser*	m_pAnalyser;
	Compressor*	m_pCompressor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPRSDOC_H__E6FF026C_1A3B_4032_BCC4_F925650E5E98__INCLUDED_)
