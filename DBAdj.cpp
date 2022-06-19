// DBAdj.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "DBAdj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBAdjustment dialog


CDBAdjustment::CDBAdjustment(CString* pstrTableName, CWnd* pParent /*=NULL*/) : CDialog(CDBAdjustment::IDD, pParent), m_strTableName(*pstrTableName)
{
	//{{AFX_DATA_INIT(CDBAdjustment)
	//}}AFX_DATA_INIT
}


void CDBAdjustment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBAdjustment)
	DDX_Text(pDX, IDC_TABLENAME, m_strTableName);
	DDV_MaxChars(pDX, m_strTableName, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBAdjustment, CDialog)
	//{{AFX_MSG_MAP(CDBAdjustment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBAdjustment message handlers

void CDBAdjustment::OnOK() 
{
	UpdateData();
	
	CDialog::OnOK();
}
