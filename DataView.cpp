// DataView.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "DataView.h"

#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataView

IMPLEMENT_DYNCREATE(CDataView, CView)

CDataView::CDataView()
{
}

CDataView::~CDataView()
{
}


BEGIN_MESSAGE_MAP(CDataView, CView)
	//{{AFX_MSG_MAP(CDataView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataView drawing

void CDataView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDataView diagnostics

#ifdef _DEBUG
void CDataView::AssertValid() const
{
	CView::AssertValid();
}

void CDataView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDataView message handlers

int CDataView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CDataView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
	
	//return CView::OnEraseBkgnd(pDC);
}

void CDataView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_Grid.MoveWindow(0, 0, cx, cy);
}

void CDataView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(lHint !=0 && lHint != CCompressorDoc::InputDataChanged) return;
	
	BeginWaitCursor();

	m_Grid.DeleteAllItems();
	
	CCompressorDoc&	rDoc = *GetDocument();
	
	switch(rDoc.m_presentation)
	{
	case CCompressorDoc::ViewDB:
		if(rDoc.m_db.IsOpen() && rDoc.IsQuerySQLStatement(rDoc.m_strSQLStatement))
			FillFromDB();
		else
			rDoc.m_presentation = CCompressorDoc::ViewDoc, FillFromDoc();
		break;
	
	case CCompressorDoc::ViewDoc:
		FillFromDoc();
		break;
	
	default:
		ASSERT(false);
	}

	EndWaitCursor();
	
	rDoc.UpdateAllViews(this, CCompressorDoc::InputDataChanged);
}

void CDataView::FillFromDB()
{
	m_Grid.DeleteAllItems();

	CCompressorDoc&	rDoc = *GetDocument();
	
	if(!rDoc.m_db.IsOpen() || !rDoc.IsQuerySQLStatement(rDoc.m_strSQLStatement)) return;
	
	BeginWaitCursor();
	
	CODBCRecordset rs(&rDoc.m_db);
	
	if(!rs.Open(rDoc.m_strSQLStatement))
	{
		EndWaitCursor();
		return;
	}
	
	RestoreWaitCursor();

	m_Grid.SetFixedRowCount();
	m_Grid.SetFixedColumnCount();

	std::vector<size_t> numericalFields(0);
	
	size_t rsFieldCount = rs.GetODBCFieldCount();
	
	size_t i;
	for(i = 0; i < rsFieldCount; i++)
	{
		m_Grid.InsertColumn(rs.Field(i).GetName());
		
		if(rs.Field(i).IsNumber())
			numericalFields.insert(numericalFields.end(), i);
	}
	
	for(i = 0, rDoc.m_inputDataSet.clear(); !rs.IsEOF(); rs.MoveNext(), i++)
	{
		CString	str;
		str.Format("%d", i + 1);
		m_Grid.InsertRow(str);
		
		size_t j, numericalFieldCount;
		bool bNullCellPresent;
		
		for(j = 0, numericalFieldCount = numericalFields.size(); j < numericalFieldCount && !(bNullCellPresent = rs(numericalFields[j]).IsNull()); j++);
		
		if(bNullCellPresent)
		{
			for(j = 0; j < rsFieldCount; j++)
			{
				m_Grid.SetItemBkColour(i + 1, j + 1, RGB(0xbf, 0x7f, 0x7f));
			}
		}
		else
		{
			DataSet::iterator curVector =
				rDoc.m_inputDataSet.insert(rDoc.m_inputDataSet.end(), ColumnVector(numericalFields.size()));
			for(j = 0, numericalFieldCount = numericalFields.size(); j < numericalFieldCount; j++)
			{
				(*curVector)[j] = rs(numericalFields[j]).AsDouble();
				
				m_Grid.SetItemBkColour(i + 1, numericalFields[j] + 1, RGB(0x7f, 0xbf, 0x7f));
			}
		}
		for(j = 0; j < rsFieldCount; j++)
		{
			if(rs(j).IsNull())
			{
				m_Grid.SetItemText(i + 1, j + 1, "<NULL>");
				m_Grid.SetItemBkColour(i + 1, j + 1, RGB(0xff, 0x7f, 0x7f));
			}
			else
			{
				m_Grid.SetItemText(i + 1, j + 1, rs(j).AsString());
			}
		}
		
	}
	m_Grid.AutoSize();
	
	rs.Close();
	
	EndWaitCursor();

	rDoc.SetModifiedFlag();
}

void CDataView::FillFromDoc()
{
	BeginWaitCursor();

	m_Grid.DeleteAllItems();

	CCompressorDoc&	rDoc = *GetDocument();

	size_t i;
	if(!rDoc.m_inputDataSet.size()) 
	{
		EndWaitCursor();
		return;
	}

	m_Grid.SetFixedRowCount();
	m_Grid.SetFixedColumnCount();
	
	for(i = 0; i < rDoc.m_inputDataSet.begin()->Nrows(); i++)
	{
		CString	str;
		str.Format("%d", i + 1);
		m_Grid.InsertColumn(str);
	}
	DataSet::const_iterator iDS;
	for(iDS = rDoc.m_inputDataSet.begin(), i = 0; iDS != rDoc.m_inputDataSet.end(); iDS++, i++)
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
}
