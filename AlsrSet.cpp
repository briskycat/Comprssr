// AlsrSet.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "AlsrSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalyserSettings dialog


CAnalyserSettings::CAnalyserSettings(double* pInfFactor, CWnd* pParent /*=NULL*/) : CDialog(CAnalyserSettings::IDD, pParent), m_infFactor(*pInfFactor)
{
	//{{AFX_DATA_INIT(CAnalyserSettings)
	//}}AFX_DATA_INIT
}


void CAnalyserSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalyserSettings)
	DDX_Text(pDX, IDC_INFFACTOR, m_infFactor);
	DDV_MinMaxDouble(pDX, m_infFactor, 0., 1.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalyserSettings, CDialog)
	//{{AFX_MSG_MAP(CAnalyserSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalyserSettings message handlers

void CAnalyserSettings::OnOK() 
{
	UpdateData();
	
	CDialog::OnOK();
}
