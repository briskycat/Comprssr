// CprnView.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "CprnView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompressionView

IMPLEMENT_DYNCREATE(CCompressionView, CView)

CCompressionView::CCompressionView()
{
}

CCompressionView::~CCompressionView()
{
}


BEGIN_MESSAGE_MAP(CCompressionView, CView)
	//{{AFX_MSG_MAP(CCompressionView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressionView drawing

void CCompressionView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCompressionView diagnostics

#ifdef _DEBUG
void CCompressionView::AssertValid() const
{
	CView::AssertValid();
}

void CCompressionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCompressionView message handlers

int CCompressionView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Grid.Create(CRect(0, 0, 0, 0), this, NULL, WS_CHILD);
	m_Grid.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	m_Grid.SetFixedRowCount();
	m_Grid.SetFixedColumnCount();

	m_Grid.ShowWindow(SW_SHOW);
	m_Grid.UpdateWindow();
	
	m_Grid.SetEditable(false);
	
	return 0;
}

void CCompressionView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_Grid.MoveWindow(0, 0, cx, cy);
}

BOOL CCompressionView::OnEraseBkgnd(CDC* pDC) 
{
	return false;	
	//return CView::OnEraseBkgnd(pDC);
}

void CCompressionView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(lHint !=0 && lHint != CCompressorDoc::OutputDataChanged) return;

	BeginWaitCursor();

	m_Grid.DeleteAllItems();

	CCompressorDoc&	rDoc = *GetDocument();

	size_t i;
	if(!rDoc.m_outputDataSet.size()) 
	{
		EndWaitCursor();
		return;
	}

	m_Grid.SetFixedRowCount();
	m_Grid.SetFixedColumnCount();
	
	for(i = 0; i < rDoc.m_outputDataSet.begin()->Nrows(); i++)
	{
		CString	str;
		str.Format("%d", i + 1);
		m_Grid.InsertColumn(str);
	}
	DataSet::const_iterator iDS;
	for(iDS = rDoc.m_outputDataSet.begin(), i = 0; iDS != rDoc.m_outputDataSet.end(); iDS++, i++)
	{
		CString	str;
		str.Format("%d", i + 1);
		m_Grid.InsertRow(str);

		size_t j;
		for(j = 0; j < (*iDS).Nrows(); j++)
		{
			str.Format("%f", (*iDS)[j]);
			m_Grid.SetItemText(i + 1, j + 1, str);
			m_Grid.SetItemBkColour(i + 1, j + 1, RGB(0x7f, 0xbf, 0x7f));
		}
	}
	m_Grid.AutoSize();

	EndWaitCursor();

	rDoc.UpdateAllViews(this, CCompressorDoc::OutputDataChanged);
}
