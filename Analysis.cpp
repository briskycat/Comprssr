// Analysis.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "Analysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView

IMPLEMENT_DYNCREATE(CAnalysisView, CView)

CAnalysisView::CAnalysisView()
{
	m_graph.EnableMemoryDraw(true);
	m_graph.EnableLegend(false);
	m_graph.SetRange(0, 0, 100, 100);

	m_strGraphTitle.LoadString(IDS_GRAPH_TITLE);
	m_strXAxisTitle.LoadString(IDS_GRAPH_XAXIS);
	m_strYAxisTitle.LoadString(IDS_GRAPH_YAXIS);
}

CAnalysisView::~CAnalysisView()
{
}


BEGIN_MESSAGE_MAP(CAnalysisView, CView)
	//{{AFX_MSG_MAP(CAnalysisView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView drawing

void CAnalysisView::OnDraw(CDC* pDC)
{
	if (pDC->IsPrinting())
	{
		CRect rect;
		rect.left = rect.top = 0;
		rect.right  = pDC->GetDeviceCaps(HORZRES);
		rect.bottom = pDC->GetDeviceCaps(VERTRES);
		m_graph.SetPrintScale(pDC->m_hDC, rect);
	}
	else
	{
		CRect	rcClient;
		GetClientRect(rcClient);
		m_graph.RecalcRects(rcClient);
	}

	m_graph.BeginDraw(pDC->m_hDC);

	m_graph.SetRatio(0, 0, 1, 1);

	m_graph.XAxisTitle(m_strXAxisTitle);
	m_graph.YAxisTitle(m_strYAxisTitle);
	//m_graph.Title(m_strGraphTitle);
	
	if(m_pt.size()) m_graph.Markers(&m_pt.front(), m_pt.size(), RGB(255, 0, 255), CGraphics::CROSS);

	m_graph.Axes();
	m_graph.Grid();

	if(m_pt.size())	m_graph.Lines(&m_pt.front(), m_pt.size(), RGB(0, 128, 255));//, 3, "Line 3");

	m_graph.EndDraw(pDC->m_hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView diagnostics

#ifdef _DEBUG
void CAnalysisView::AssertValid() const
{
	CView::AssertValid();
}

void CAnalysisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnalysisView message handlers

void CAnalysisView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(lHint !=0 && lHint != CCompressorDoc::ResultsChanged) return;

	CCompressorDoc&	rDoc = *GetDocument();

	if(rDoc.m_inputDataSet.empty()) return;

	m_pt.clear();
	Chain::const_iterator iChain;
	for(iChain = rDoc.m_chain.begin(); iChain != rDoc.m_chain.end(); iChain++)
		m_pt.push_back(CTPoint<double>(iChain->first, iChain->second));

	int min_x = 0;
	int min_y = 0;
	int max_x = rDoc.m_chain.size() % 50 ? (rDoc.m_chain.size() / 50 + 1) * 50 : rDoc.m_chain.size();
	int max_y = rDoc.m_inputDataSet.begin()->Nrows() % 50 ? (rDoc.m_inputDataSet.begin()->Nrows() / 50 + 1) * 50 : rDoc.m_inputDataSet.begin()->Nrows();
	if(max_x == 0) min_x = 0, max_x = 100;
	if(max_y == 0) min_y = 0, max_y = 100;
	m_graph.SetRange(min_x, min_y, max_x, max_y);

	Invalidate();
}


BOOL CAnalysisView::OnEraseBkgnd(CDC* pDC) 
{
	return false;//CView::OnEraseBkgnd(pDC);
}

BOOL CAnalysisView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}
