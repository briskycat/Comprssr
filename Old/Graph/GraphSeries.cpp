// GraphSeries.cpp : implementation file
//

#include "stdafx.h"
#include "GraphSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries

CGraphSeries::CGraphSeries()
{
	dataValue.resize(10);
	for(int i = 0; i < 10; i++)
		dataValue[i] = 0;
}

CGraphSeries::~CGraphSeries()
{
}


BEGIN_MESSAGE_MAP(CGraphSeries, CStatic)
	//{{AFX_MSG_MAP(CGraphSeries)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries message handlers

void CGraphSeries::SetLabel(CString label)
{
	seriesLabel = label;
}

void CGraphSeries::SetData(int group, int dValue)
{
	if(group >= dataValue.size()) dataValue.resize(group + 1);
	dataValue[group] = dValue;
}

CString CGraphSeries::GetLabel()
{
	return seriesLabel;
}

int CGraphSeries::GetData(int group)
{
	return dataValue[group];
}


int CGraphSeries::Size()
{
	return dataValue.size();
}
