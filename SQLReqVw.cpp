// SQLReqVw.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "SQLReqVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLRequestView

IMPLEMENT_DYNCREATE(CSQLRequestView, CEditView)

CSQLRequestView::CSQLRequestView()
{
}

CSQLRequestView::~CSQLRequestView()
{
}


BEGIN_MESSAGE_MAP(CSQLRequestView, CEditView)
	//{{AFX_MSG_MAP(CSQLRequestView)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLRequestView drawing

void CSQLRequestView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSQLRequestView diagnostics

#ifdef _DEBUG
void CSQLRequestView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSQLRequestView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSQLRequestView message handlers


void CSQLRequestView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(lHint !=0 && lHint != CCompressorDoc::SQLStatementChanged) return;
	GetEditCtrl().SetWindowText(GetDocument()->m_strSQLStatement);	
}

void CSQLRequestView::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEditView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	GetDocument()->m_strSQLStatement = LockBuffer();
	UnlockBuffer();
	GetDocument()->UpdateAllViews(this, CCompressorDoc::SQLStatementChanged);
	
	GetDocument()->SetModifiedFlag();
}

void CSQLRequestView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	GetEditCtrl().SetLimitText(0x10000);
	
	m_font.CreatePointFont(100, "Courier");
	SetFont(&m_font);
}
