#if !defined(AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_)
#define AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_

#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphSeries.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries window

class CGraphSeries : public CStatic
{
// Construction
public:
	CGraphSeries();

// Attributes
public:


private:
	CString				seriesLabel;
	std::vector<int>	dataValue;	//allows 10 data values in a group

// Operations
public:

	void SetLabel(CString label);
	void SetData(int group, int dValue);
	CString GetLabel();
	int GetData(int group);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphSeries)
	//}}AFX_VIRTUAL

// Implementation
public:
	int Size();
	virtual ~CGraphSeries();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphSeries)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHSERIES_H__A059628E_F6C8_4DA0_9E2F_820131D257E7__INCLUDED_)
