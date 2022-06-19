// GraphLegend.cpp : implementation file
//

#include "stdafx.h"
#include "GraphLegend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphLegend

CGraphLegend::CGraphLegend()
{
	legendLength = 0;
	for(int i = 0; i < 10; i++)
		SetLegendText(i, "");

}

CGraphLegend::~CGraphLegend()
{
}


BEGIN_MESSAGE_MAP(CGraphLegend, CStatic)
	//{{AFX_MSG_MAP(CGraphLegend)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphLegend message handlers

void CGraphLegend::SetLegendText(int datagroup, CString label)
{
	legendLabels[datagroup] = label;
	if(label.GetLength() > legendLength)
		legendLength = label.GetLength();
}

CString CGraphLegend::GetLegendText(int datagroup)
{
	return legendLabels[datagroup];
}

int CGraphLegend::GetLegendLength()
{
	return legendLength;
}

