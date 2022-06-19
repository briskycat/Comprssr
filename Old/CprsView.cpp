// CprsView.cpp : implementation of the CCompressorView class
//

#include "stdafx.h"
#include "Comprssr.h"

#include "CprsDoc.h"
#include "CprsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompressorView

IMPLEMENT_DYNCREATE(CCompressorView, CView)

BEGIN_MESSAGE_MAP(CCompressorView, CView)
	//{{AFX_MSG_MAP(CCompressorView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressorView construction/destruction

CCompressorView::CCompressorView()
{
}

CCompressorView::~CCompressorView()
{
}

BOOL CCompressorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCompressorView printing

BOOL CCompressorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCompressorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCompressorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCompressorView diagnostics

#ifdef _DEBUG
void CCompressorView::AssertValid() const
{
	CView::AssertValid();
}

void CCompressorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCompressorDoc* CCompressorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCompressorDoc)));
	return (CCompressorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCompressorView message handlers

int CCompressorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CCompressorView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}


void CCompressorView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_Grid.MoveWindow(0, 0, cx, cy);
	
}

BOOL CCompressorView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
	
	//return CView::OnEraseBkgnd(pDC);
}
