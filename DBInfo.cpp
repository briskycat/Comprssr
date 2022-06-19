// DBInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Comprssr.h"
#include "DBInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBInfo dialog


CDBInfo::CDBInfo(CDatabase* const pDB, CWnd* pParent /*=NULL*/) : CDialog(CDBInfo::IDD, pParent), m_pDB(pDB)
{
	//{{AFX_DATA_INIT(CDBInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDBInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBInfo)
	DDX_Control(pDX, IDC_TABLELIST, m_tableList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBInfo, CDialog)
	//{{AFX_MSG_MAP(CDBInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBInfo message handlers

BOOL CDBInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_pDB->IsOpen());

	BeginWaitCursor();

	CTables rs(m_pDB);
	rs.Open(NULL, NULL, NULL, "TABLE");

	while (!rs.IsEOF())
	{
		m_tableList.AddString(rs.m_strTableName);
		rs.MoveNext();
	}

	rs.Close();

	EndWaitCursor();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CTables - borrowed from Catalog2

CDBInfo::CTables::CTables(CDatabase* pDatabase)	: CRecordset(pDatabase)
{
	m_strTableQualifier = _T("");
	m_strTableOwner     = _T("");
	m_strTableName      = _T("");
	m_strTableType      = _T("");
	m_strRemarks        = _T("");
	m_nFields = 5;
}

BOOL CDBInfo::CTables::Open(LPCSTR pszTableQualifier, LPCSTR pszTableOwner, LPCSTR pszTableName, LPCSTR pszTableType, UINT nOpenType)
{
	ASSERT(m_pDatabase != NULL);
	ASSERT(m_pDatabase->IsOpen());

	RETCODE nRetCode;
	UWORD   bFunctionExists;

	// make sure SQLTables exists
	AFX_SQL_SYNC(::SQLGetFunctions(m_pDatabase->m_hdbc,
		SQL_API_SQLTABLES,&bFunctionExists));
	if (!Check(nRetCode) || !bFunctionExists)
	{
		if (!bFunctionExists)
			TRACE(_T("SQLTables not supported\n"));
		return FALSE;
	}

	m_nOpenType = nOpenType;
	m_bUpdatable = FALSE;

	// make sure hstmt is allocated
	if (m_hstmt == SQL_NULL_HSTMT)
	{
		AFX_SQL_SYNC(::SQLAllocStmt(m_pDatabase->m_hdbc,&m_hstmt));
		if (!Check(nRetCode))
			ThrowDBException(nRetCode,m_hstmt);
	}

	OnSetOptions(m_hstmt);

	TRY
	{
		// call the ODBC function
		AFX_SQL_ASYNC(this,::SQLTables(m_hstmt,
			(UCHAR FAR*)pszTableQualifier,SQL_NTS,
			(UCHAR FAR*)pszTableOwner,SQL_NTS,
			(UCHAR FAR*)pszTableName,SQL_NTS,
			(UCHAR FAR*)pszTableType,SQL_NTS));

		if (!Check(nRetCode))
			ThrowDBException(nRetCode,m_hstmt);

		// Allocate memory and cache info
		AllocAndCacheFieldInfo();
		AllocRowset();

		// Allocate the field info and status arrays if
		// not done already in BuildSelectSQL
		if ((m_nFields != 0 || m_nParams != 0) &&
			m_rgFieldInfos == NULL)
		{
			AllocStatusArrays();
		}

		MoveNext();
	}

	CATCH_ALL(e)
	{
		Close();
		THROW_LAST();
	}
	END_CATCH_ALL

	return TRUE;
}

void CDBInfo::CTables::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX,_T("TABLE_QUALIFIER"),m_strTableQualifier);
	RFX_Text(pFX,_T("TABLE_OWNER"),m_strTableOwner);
	RFX_Text(pFX,_T("TABLE_NAME"),m_strTableName);
	RFX_Text(pFX,_T("TABLE_TYPE"),m_strTableType);
	RFX_Text(pFX,_T("REMARKS"),m_strRemarks);
}
