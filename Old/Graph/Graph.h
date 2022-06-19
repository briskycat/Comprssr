#if !defined(AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_)
#define AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Graph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraph window

#include "GraphSeries.h"
#include "GraphLegend.h"

class CGraph : public CStatic
{
// Construction
public:
	CGraph();
	CGraph(int type);

// Attributes
public:


private:
	int tickSpace;	//number of pixels between "y" axis ticks
	CObList* graphSeries;
	int graphType;	//0 - bar graph, 1 - line graph, 2 - pie
	int graphAlignment;	//0 - horizontal, 1 - vertical
	int maxHeight;
	int maxWidth;
	CString axisYLabel;
	CString axisXLabel;
	int yApexPoint;
	int xApexPoint;
	int yAxisHeight;
	int xAxisWidth;
	int yTickFontSize;
	int xTickFontSize;
	int legendFontSize;
	int tickRange;
	int seriesSize;	//number of data elements to map per series
	CGraphLegend graphLegend;
	BOOL graphHasLegend;
	int legendWidth;
	COLORREF dataColor[10];
	int xAxisAlign;	//0 - horizontal, # - degree rotation
	int xAxisLabelLength;
	CString graphTitle;

	//print settings
	int topMargin;
	int bottomMargin;
	int leftMargin;
	int rightMargin;
	int pGraphL, pGraphT, pGraphB, pGraphR;


// Operations
public:
	void SetTickSpace(int yDist);
	void SetTickRange(int maxTick);
	void SetXTickFontSize(int size);
	void SetYTickFontSize(int size);
	void SetLegendFontSize(int size);
	void DrawGraph(CDC* pDC);
	void AddSeries(CGraphSeries* dataSet);
	void SetXAxisLabel(CString label);
	void SetYAxisLabel(CString label);
	void SetLegend(int datagroup, CString label);
	void SetColor(int group, COLORREF groupColor);
	void SetXAxisAlignment(int alignValue);
	void SetGraphType(int gType);
	void SetGraphTitle(CString title);
	int PrintGraph(CDC *pDC, CPrintInfo* pInfo);
	void SetMargins(int top, int bottom, int left, int right, int graphTop);


private:
	void DrawAxis(CDC* pDC);
	void DrawSeries(CDC* pDC);
	void DrawLegend(CDC* pDC);
	COLORREF GetColor(int group);
	int GetXAxisAlignment();
	void PrintLegend(CDC *pDC);
	void PrintAxis(CDC *pDC);
	void PrintSeries(CDC *pDC);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraph)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraph();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraph)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__9DB68B4D_3C7C_47E2_9F72_EEDA5D2CDBB0__INCLUDED_)
