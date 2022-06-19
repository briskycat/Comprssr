// Analyser.h: interface for the Analyser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSER_H__B1402429_7FE9_4E92_A3DF_F21988050262__INCLUDED_)
#define AFX_ANALYSER_H__B1402429_7FE9_4E92_A3DF_F21988050262__INCLUDED_

#include "types.h"
#include <stdexcept>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Analyser  
{
public:
	void ComputeChain(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd, Chain& chain) throw(std::invalid_argument&);
	SymmetricMatrix ComputeCovMatrix(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd) throw(std::invalid_argument&);
	ColumnVector ComputeMeanVector(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd)const throw(std::invalid_argument&);
	Analyser();
	virtual ~Analyser();

};

#endif // !defined(AFX_ANALYSER_H__B1402429_7FE9_4E92_A3DF_F21988050262__INCLUDED_)
