// CprsDoc.cpp : implementation of the CCompressorDoc class
//

#include "stdafx.h"
#include "Comprssr.h"

#include "CprsDoc.h"

#include "DBInfo.h"
#include "DBAdj.h"
#include "AlsrSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompressorDoc

IMPLEMENT_DYNCREATE(CCompressorDoc, CDocument)

BEGIN_MESSAGE_MAP(CCompressorDoc, CDocument)
	//{{AFX_MSG_MAP(CCompressorDoc)
	ON_COMMAND(ID_OPENDBASE, OnOpendbase)
	ON_UPDATE_COMMAND_UI(ID_EXECREQUEST, OnUpdateExecrequest)
	ON_COMMAND(ID_DBASEINFO, OnDbaseinfo)
	ON_UPDATE_COMMAND_UI(ID_DBASEINFO, OnUpdateDbaseinfo)
	ON_COMMAND(ID_EXECREQUEST, OnExecrequest)
	ON_UPDATE_COMMAND_UI(ID_VIEWDB, OnUpdateViewdb)
	ON_UPDATE_COMMAND_UI(ID_VIEWDOC, OnUpdateViewdoc)
	ON_COMMAND(ID_VIEWDB, OnViewdb)
	ON_COMMAND(ID_VIEWDOC, OnViewdoc)
	ON_COMMAND(ID_ANALYZE, OnAnalyze)
	ON_COMMAND(ID_ANALYSERSETTINGS, OnAnalyserSettings)
	ON_UPDATE_COMMAND_UI(ID_ANALYZE, OnUpdateAnalyze)
	ON_UPDATE_COMMAND_UI(ID_INITCOMPRESSOR, OnUpdateInitCompressor)
	ON_COMMAND(ID_INITCOMPRESSOR, OnInitCompressor)
	ON_UPDATE_COMMAND_UI(ID_COMPRESS, OnUpdateCompress)
	ON_COMMAND(ID_COMPRESS, OnCompress)
	ON_UPDATE_COMMAND_UI(ID_DECOMPRESS, OnUpdateDecompress)
	ON_COMMAND(ID_DECOMPRESS, OnDecompress)
	ON_COMMAND(ID_OPENOUTPUTDB, OnOpenOutputDB)
	ON_COMMAND(ID_OUTPUTDBINFO, OnOutputDBInfo)
	ON_COMMAND(ID_OUTPUTDBADJUSTMENT, OnOutputDBAdjustment)
	ON_UPDATE_COMMAND_UI(ID_SAVEPROCESSEDDATA, OnUpdateSaveProcessedData)
	ON_COMMAND(ID_SAVEPROCESSEDDATA, OnSaveProcessedData)
	ON_UPDATE_COMMAND_UI(ID_OUTPUTDBADJUSTMENT, OnUpdateOutputDBAdjustment)
	ON_UPDATE_COMMAND_UI(ID_OUTPUTDBINFO, OnUpdateOutputDBInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressorDoc construction/destruction

CCompressorDoc::CCompressorDoc() : m_presentation(ViewDoc), m_strSQLStatement("SELECT * FROM [];"), m_pAnalyser(new Analyser), m_pCompressor(new Compressor(m_pAnalyser))
{
}

CCompressorDoc::~CCompressorDoc()
{
	delete m_pCompressor;
	delete m_pAnalyser;
}

BOOL CCompressorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCompressorDoc serialization

void CCompressorDoc::Serialize(CArchive& ar)
{
	static DWORD signature = 'DWRC';

	if (ar.IsStoring())
	{
		ar << signature;
		ar << m_version;

		ar << m_strSQLStatement;

		ar << m_pAnalyser->m_infFactor;
	}
	else
	{
		DWORD sign;
		short ver;
		ar >> sign;
		if(sign != signature) throw new CArchiveException(CArchiveException::badIndex);
		ar >> ver;
		if(ver != m_version) throw new CArchiveException(CArchiveException::badSchema);

		ar >> m_strSQLStatement;

		ar >> m_pAnalyser->m_infFactor;
	}

	m_inputDataSet.Serialize(ar);
	m_chain.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CCompressorDoc diagnostics

#ifdef _DEBUG
void CCompressorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCompressorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCompressorDoc commands

void CCompressorDoc::OnOpendbase() 
{
	// If already open, close it and reselect
	if (m_db.IsOpen())
		m_db.Close();

	if (!m_db.OpenEx(NULL, NULL))
	{
		CString errorStr;
		
		errorStr.LoadString(IDS_MSG_ERROR_DBOPENFAIL);
		AfxMessageBox(errorStr, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

}

void CCompressorDoc::OnDbaseinfo() 
{
	CDBInfo(&m_db).DoModal();
}

void CCompressorDoc::OnUpdateDbaseinfo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_db.IsOpen());
}

void CCompressorDoc::OnUpdateExecrequest(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_db.IsOpen() && m_strSQLStatement.GetLength());
}

void CCompressorDoc::OnExecrequest() 
{
	ASSERT(m_db.IsOpen() && m_strSQLStatement.GetLength());

	if(IsQuerySQLStatement(m_strSQLStatement))
	{
		if(m_presentation == ViewDoc)
			FillFromDB();
		UpdateAllViews(NULL, InputDataChanged);
	}
	else
	{
		try
		{
			m_db.ExecuteSQL(m_strSQLStatement);
		}
		catch(CDBException* e)
		{
			AfxMessageBox(e->m_strError, MB_OK | MB_ICONERROR);
			return;
		}
	}

	if(m_inputDataSet.size())
		m_pCompressor->SetInputDimension(m_inputDataSet.begin()->Nrows());
}

bool CCompressorDoc::IsQuerySQLStatement(const CString &rStr) const
{
/*
	// Работает не правильно
	CString tmpString = rStr;
	tmpString.MakeUpper();
	return tmpString.Find("SELECT") == 0 || tmpString.Find("CALL") == 0;
*/
	CString tmpString = rStr;
	int index = tmpString.FindOneOf(" \t");
	if(index == -1) return false;
	tmpString.SetAt(index, 0);
	return !tmpString.CompareNoCase("SELECT") || !tmpString.CompareNoCase("CALL");
}

void CCompressorDoc::OnUpdateViewdb(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_db.IsOpen() && IsQuerySQLStatement(m_strSQLStatement));	
	pCmdUI->SetCheck(m_presentation == ViewDB ? 1 : 0);
}

void CCompressorDoc::OnUpdateViewdoc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();	
	pCmdUI->SetCheck(m_presentation == ViewDoc ? 1 : 0);	
}

void CCompressorDoc::OnViewdb() 
{
	m_presentation = ViewDB;
	UpdateAllViews(NULL, InputDataChanged);
}

void CCompressorDoc::OnViewdoc() 
{
	m_presentation = ViewDoc;
	UpdateAllViews(NULL, InputDataChanged);
}

void CCompressorDoc::FillFromDB()
{
	if(!m_db.IsOpen() || !IsQuerySQLStatement(m_strSQLStatement)) return;
	
	BeginWaitCursor();
	
	CODBCRecordset rs(&m_db);
	
	if(!rs.Open(m_strSQLStatement))
	{
		EndWaitCursor();
		return;
	}
	
	RestoreWaitCursor();

	std::vector<size_t> numericalFields(0);
	
	size_t rsFieldCount = rs.GetODBCFieldCount();
	
	size_t i;
	for(i = 0; i < rsFieldCount; i++)
		if(rs.Field(i).IsNumber())
			numericalFields.insert(numericalFields.end(), i);
	
	for(i = 0, m_inputDataSet.clear(); !rs.IsEOF(); rs.MoveNext(), i++)
	{
		size_t j, numericalFieldCount;
		bool bNullCellPresent;
		
		for(j = 0, numericalFieldCount = numericalFields.size(); j < numericalFieldCount && !(bNullCellPresent = rs(numericalFields[j]).IsNull()); j++);
		
		if(bNullCellPresent)
			continue;
		else
		{
			DataSet::iterator curVector =
				m_inputDataSet.insert(m_inputDataSet.end(), ColumnVector(numericalFields.size()));
			for(j = 0, numericalFieldCount = numericalFields.size(); j < numericalFieldCount; j++)
				(*curVector)[j] = rs(numericalFields[j]).AsDouble();
		}
	}

	rs.Close();
	
	EndWaitCursor();

	SetModifiedFlag();
}

void CCompressorDoc::OnUpdateAnalyze(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_inputDataSet.empty());
}

void CCompressorDoc::OnAnalyze() 
{
	BeginWaitCursor();

	try
	{
		m_pAnalyser->ComputeChain(m_inputDataSet.begin(), m_inputDataSet.end(), m_chain);
	}
	catch(std::invalid_argument& e)
	{
		AfxMessageBox(e.what());
	}

	EndWaitCursor();

	SetModifiedFlag();

	UpdateAllViews(NULL, ResultsChanged);
}

void CCompressorDoc::OnAnalyserSettings() 
{
	CAnalyserSettings settings(&m_pAnalyser->m_infFactor);
	if(settings.DoModal() == IDOK)
		SetModifiedFlag();	
}

void CCompressorDoc::OnUpdateInitCompressor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_inputDataSet.empty());
}

void CCompressorDoc::OnInitCompressor() 
{
	BeginWaitCursor();
	m_pCompressor->Initialize(m_inputDataSet.begin(), m_inputDataSet.end());	
	EndWaitCursor();
}

void CCompressorDoc::OnUpdateCompress(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pCompressor->ReadyToCompress());
}

void CCompressorDoc::OnCompress() 
{
	BeginWaitCursor();
	if(m_pCompressor->Compress(m_inputDataSet.begin(), m_inputDataSet.end(), m_outputDataSet))
		UpdateAllViews(NULL, OutputDataChanged);
	EndWaitCursor();
}

void CCompressorDoc::OnUpdateDecompress(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pCompressor->ReadyToDecompress());
}

void CCompressorDoc::OnDecompress() 
{
	BeginWaitCursor();
	if(m_pCompressor->Decompress(m_inputDataSet.begin(), m_inputDataSet.end(), m_outputDataSet))
		UpdateAllViews(NULL, OutputDataChanged);
	EndWaitCursor();
}

void CCompressorDoc::OnOpenOutputDB() 
{
	// If already open, close it and reselect
	if (m_outputDB.IsOpen())
		m_outputDB.Close();

	if (!m_outputDB.OpenEx(NULL, NULL))
	{
		CString errorStr;
		
		errorStr.LoadString(IDS_MSG_ERROR_DBOPENFAIL);
		AfxMessageBox(errorStr, MB_OK | MB_ICONEXCLAMATION);
		return;
	}
}

void CCompressorDoc::OnOutputDBInfo() 
{
	CDBInfo(&m_outputDB).DoModal();	
}

void CCompressorDoc::OnOutputDBAdjustment() 
{
	CDBAdjustment(&m_strOutputTable).DoModal();	
}

void CCompressorDoc::OnUpdateSaveProcessedData(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_outputDB.IsOpen() && !m_outputDataSet.empty() && m_strOutputTable.GetLength());
}

void CCompressorDoc::OnSaveProcessedData() 
{
	ASSERT(m_outputDB.IsOpen());

	if(m_outputDataSet.empty()) return;
	if(!m_outputDataSet.begin()->Nrows()) return;

	CString strSQLStatement = "CREATE TABLE";
	strSQLStatement += " [" + m_strOutputTable + ']';
	strSQLStatement += " (F1 FLOAT";
	for(int i = 2; i <= m_outputDataSet.begin()->Nrows(); i++)
	{
		CString str;
		str.Format("F%d DOUBLE", i);
		strSQLStatement += ", " + str;
	}
	strSQLStatement += ");";
	try
	{
		m_outputDB.ExecuteSQL(strSQLStatement);
	}
	catch(CDBException* e)
	{
		AfxMessageBox(e->m_strError, MB_OK | MB_ICONERROR);
		return;
	}

	BeginWaitCursor();
	
	CODBCRecordset rs(&m_outputDB);
	
	if(!rs.Open("SELECT * FROM [" + m_strOutputTable + "];", CRecordset::dynaset))
	{
		EndWaitCursor();
		return;
	}
	
	RestoreWaitCursor();

	DataSet::const_iterator iDS;
	for(iDS = m_outputDataSet.begin(); iDS != m_outputDataSet.end(); iDS++)
	{
		try
		{
			rs.AddNew();
		}
		catch(CDBException* e)
		{
			AfxMessageBox(e->m_strError, MB_OK | MB_ICONERROR);
			return;
		}
		
		int i;
		for(i = 0; i < rs.GetODBCFieldCount(); i++)
		{
			rs(i) = (*iDS)[i];
		}

		try
		{
			rs.Update();
		}
		catch(CDBException* e)
		{
			AfxMessageBox(e->m_strError, MB_OK | MB_ICONERROR);
			return;
		}
	}

	rs.Close();

	EndWaitCursor();
}

void CCompressorDoc::OnUpdateOutputDBAdjustment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_outputDB.IsOpen());
}

void CCompressorDoc::OnUpdateOutputDBInfo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_outputDB.IsOpen());
}

const short	CCompressorDoc::m_version = 0x0001;

/////////////////////////////////////////////////////////////////////////////
// CDataSet functions

void CDataSet::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// Сохранение >>
		size_t i = (*this).size();
		ar << i;
		if(i)
		{
			const_iterator iThis;
			ar << (*this).begin()->Nrows();
			for(iThis = (*this).begin(); iThis != (*this).end(); iThis++)
			{
				size_t j;
				for(j = 0; j < (*iThis).Nrows(); j++)
					ar << (*iThis)[j];
			}
		}
		// << Сохранение
	}
	else
	{
		// Загрузка >>
		(*this).clear();
		size_t i, nRows;
		ar >> nRows;
		if(nRows)
		{
			size_t j, nCols;
			ar >> nCols;
			for(i = 0; i < nRows; i++)
			{
				iterator curVector =
					(*this).insert((*this).end(), ColumnVector(nCols));
				for(j = 0; j < nCols; j++)
					ar >> (*curVector)[j];
			}
		}
		// << Загрузка
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChain functions

void CChain::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// Сохранение >>
		size_t i = (*this).size();
		ar << i;
		for(i = 0; i < (*this).size(); i++)
		{
			ar << (*this)[i].first << (*this)[i].second;
		}
		// << Сохранение
	}
	else
	{
		// Загрузка >>
		(*this).clear();
		size_t i, nElements;
		ar >> nElements;
		for(i = 0; i < nElements; i++)
		{
			push_back(value_type());
			ar >> back().first >> back().second;
		}
		// << Загрузка
	}
}
