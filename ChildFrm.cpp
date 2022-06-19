// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Comprssr.h"

#include "SQLReqVw.h"
#include "DataView.h"
#include "Analysis.h"
#include "CprnView.h"

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
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame() : m_TabViewContainer(*new CTabViewContainer()), m_bFirstTimeShow(true)
{
	m_TabViewContainer.Initialize(this);
}

CChildFrame::~CChildFrame()
{
	delete &m_TabViewContainer;
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
	m_Data_SQLReqSplitter.CreateView(0, 0, RUNTIME_CLASS(CDataView), CSize(0, 150), pContext);
	m_Data_SQLReqSplitter.CreateView(1, 0, RUNTIME_CLASS(CSQLRequestView), CSize(0, 40), pContext);
	m_Data_SQLReqSplitter.SetRowInfo(1, 40, 0);
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
	
	captionStr.LoadString(IDS_PAGE_COMPRESSION);
	if (!m_TabViewContainer.AddPage(RUNTIME_CLASS(CCompressionView), pContext, captionStr.GetBuffer(0)))
        return FALSE;
	// << Инициализация закладок
	
	m_wndDBToolBar.CreateEx(this);
	m_wndDBToolBar.LoadToolBar(IDR_TBDBASE);
	m_wndDBToolBar.SetBarStyle(m_wndDBToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndAnalysisToolBar.CreateEx(this);
	m_wndAnalysisToolBar.LoadToolBar(IDR_TBANALYSIS);
	m_wndAnalysisToolBar.SetBarStyle(m_wndAnalysisToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndComressionToolBar.CreateEx(this);
	m_wndComressionToolBar.LoadToolBar(IDR_TBCOMPRESSION);
	m_wndComressionToolBar.SetBarStyle(m_wndComressionToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndDBToolBar);
	m_wndReBar.AddBar(&m_wndAnalysisToolBar);
	m_wndReBar.AddBar(&m_wndComressionToolBar);

    m_TabViewContainer.SetActivePageIndex(0);
	
	return TRUE;
}

BOOL CChildFrame::OnEraseBkgnd(CDC* pDC) 
{
	return false;//CMDIChildWnd::OnEraseBkgnd(pDC);
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	m_TabViewContainer.Update();

	CMDIChildWnd::ActivateFrame(nCmdShow);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame::CTabViewContainer

BEGIN_MESSAGE_MAP(CChildFrame::CTabViewContainer, COX3DTabViewContainer)
//{{AFX_MSG_MAP(CChildFrame::CTabViewContainer)
ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, CTabViewContainer::OnSelchange)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChildFrame::CTabViewContainer::CTabViewContainer() : m_pFrame(0)
{
}

CChildFrame::CTabViewContainer::~CTabViewContainer()
{
}

//////////////////////////////////////////////////////////////////////////////
// Description: Selection change handler
//////////////////////////////////////////////////////////////////////////////
BOOL CChildFrame::CTabViewContainer::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BOOL result = COX3DTabViewContainer::OnSelchange(pNMHDR, pResult);

	Update();
	
    return result;
}

BOOL CChildFrame::CTabViewContainer::SetActivePageIndex(const int nIndex)
{
	BOOL result = COX3DTabViewContainer::SetActivePageIndex(nIndex);

    return result;
}

bool CChildFrame::CTabViewContainer::Initialize(CChildFrame *pFrame)
{
	ASSERT(pFrame);

	m_pFrame = pFrame;

	return true;
}

void CChildFrame::CTabViewContainer::Update()
{
	int	nActivePage = GetActivePageIndex();
	
	m_pFrame->ShowControlBar(&m_pFrame->m_wndDBToolBar, nActivePage == 0, FALSE);
	m_pFrame->ShowControlBar(&m_pFrame->m_wndAnalysisToolBar, nActivePage == 1, FALSE);
	m_pFrame->ShowControlBar(&m_pFrame->m_wndComressionToolBar, nActivePage == 2, FALSE);

	switch(nActivePage)
	{
	case 0:
		m_pFrame->m_Data_SQLReqSplitter.SetActivePane(0, 0, NULL);
		break;
	}
}

BOOL CChildFrame::DestroyWindow() 
{
	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);

	AfxGetApp()->WriteProfileBinary("ChildFrame", "Placement", reinterpret_cast<BYTE*>(&wp), sizeof(wp));
	
	return CMDIChildWnd::DestroyWindow();
}

void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);
	
	// >>
	if(m_bFirstTimeShow && bShow)
	{
		m_bFirstTimeShow = false;
		unsigned int	nBytes;
		WINDOWPLACEMENT *pWP;
		
		AfxGetApp()->GetProfileBinary("ChildFrame", "Placement", reinterpret_cast<BYTE**>(&pWP), &nBytes);
		
		if(nBytes == sizeof(WINDOWPLACEMENT))
			SetWindowPlacement(pWP);
		
		delete pWP;
	}
	// <<
	
}