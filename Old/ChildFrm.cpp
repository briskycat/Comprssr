// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Comprssr.h"

#include "SQLReqVw.h"
#include "DataView.h"
#include "Analysis.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//{{AFX_MSG_MAP(CChildFrame)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame() : m_TabViewContainer(*new CTabViewContainer())
{
	m_TabViewContainer.Initialize(this);
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIChildWnd::PreCreateWindow(cs))
		return FALSE;
	
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// Создание контейнера закладок >>
    if (!m_TabViewContainer.Create(this, CRect(0, 0, 0, 0), TCS_MULTILINE | TCS_BOTTOM | TCS_SCROLLOPPOSITE | TCS_RIGHTJUSTIFY | TCS_FOCUSNEVER | WS_VISIBLE | WS_CHILD))
        return FALSE;
	// << Создание контейнера закладок

	// Создание разделителя >>
	m_Data_SQLReqSplitter.CreateStatic(&m_TabViewContainer, 2, 1);
	// << Создание разделителя
	
	// Инициализация разделителя >>
	m_Data_SQLReqSplitter.CreateView(0, 0, RUNTIME_CLASS(CDataView), CSize(0, 200), pContext);
	m_Data_SQLReqSplitter.CreateView(1, 0, RUNTIME_CLASS(CSQLRequestView), CSize(0, 128), pContext);
	m_Data_SQLReqSplitter.SetRowInfo(1, 128, 64);
	m_Data_SQLReqSplitter.RecalcLayout();
	// << Инициализация разделителя

	// Инициализация закладок >>
	CString captionStr;
	
	captionStr.LoadString(IDS_PAGE_DATA);
	if (!m_TabViewContainer.AddPage(&m_Data_SQLReqSplitter, captionStr.GetBuffer(0)))
	    return FALSE;
	m_Data_SQLReqSplitter.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	captionStr.LoadString(IDS_PAGE_ANALYSIS);
	if (!m_TabViewContainer.AddPage(RUNTIME_CLASS(CAnalysisView), pContext, captionStr.GetBuffer(0)))
        return FALSE;
	
    m_TabViewContainer.SetActivePageIndex(0);
	// << Инициализация закладок
	
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return FALSE;		// fail to create
	}
	if (!m_wndReBar.Create(this) ||	!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	// m_wndDlgBar.ShowWindow(SW_HIDE);
	
	//-------------------------
    if (!m_wndMyBar.Create(_T("My Bar"), this, 123))
    {
        TRACE0("Failed to create mybar\n");
        return -1;      // fail to create
	}
	
    m_wndMyBar.SetBarStyle(m_wndMyBar.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	EnableDocking(CBRS_ALIGN_ANY);
	
	m_wndMyBar.EnableDocking(CBRS_ALIGN_ANY);
	
	DockControlBar(&m_wndMyBar, AFX_IDW_DOCKBAR_BOTTOM);
	//-------------------------
	
	m_wndMyBar.SetSCBStyle(m_wndMyBar.GetSCBStyle() | SCBS_SIZECHILD);
	
	CWnd* pSQLReq = (CWnd*)RUNTIME_CLASS(CSQLRequestView)->CreateObject();
	
	// views are always created with a border!
	pSQLReq->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL, CRect(0, 0, 0, 0), &m_wndMyBar, 0, pContext);
	// pSQLReq->ShowWindow(SW_SHOW);
	pSQLReq->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	
	//	CCreateContext newContext = *pContext;
	//	newContext.m_pNewViewClass = RUNTIME_CLASS(CSQLRequestView);
	//	CWnd* pSQLReq = CreateView(&newContext, 1234);
	//	pSQLReq->ShowWindow(SW_SHOW);
	
	return TRUE;
	
	// return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame::CTabViewContainer

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChildFrame::CTabViewContainer::CTabViewContainer() : m_pFrame(0)
{
}

CChildFrame::CTabViewContainer::~CTabViewContainer()
{
}

BEGIN_MESSAGE_MAP(CChildFrame::CTabViewContainer, COX3DTabViewContainer)
//{{AFX_MSG_MAP(CChildFrame::CTabViewContainer)
ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, CTabViewContainer::OnSelchange)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// Description: Selection change handler
//////////////////////////////////////////////////////////////////////////////
BOOL CChildFrame::CTabViewContainer::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COX3DTabViewContainer::OnSelchange(pNMHDR, pResult);
	
	m_pFrame->ShowControlBar(&m_pFrame->m_wndMyBar, !m_pFrame->m_wndMyBar.IsVisible(), FALSE);
	
    return FALSE;
}


bool CChildFrame::CTabViewContainer::Initialize(CChildFrame *pFrame)
{
	assert(pFrame);

	m_pFrame = pFrame;

	return true;
}
