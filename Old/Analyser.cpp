// Analyser.cpp: implementation of the Analyser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comprssr.h"
#include "Analyser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Analyser::Analyser()
{

}

Analyser::~Analyser()
{

}

ColumnVector Analyser::ComputeMeanVector(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd)const
{
	using std::invalid_argument;

	if(iBegin == iEnd) throw *new invalid_argument("empty set");

	ColumnVector meanVec(iBegin->Nrows());
	for(int i = 1; i <= meanVec.Nrows(); i++) meanVec(i) = 0.0;

	DataSet::const_iterator	iDS;
	int n;
	for(iDS = iBegin, n = 0; iDS != iEnd; iDS++, n++)
	{
		meanVec += *iDS;
	}

	return meanVec / n;
}

SymmetricMatrix Analyser::ComputeCovMatrix(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd)
{
	using std::invalid_argument;

	if(iBegin == iEnd) throw *new invalid_argument("empty set");

	ColumnVector meanVec = ComputeMeanVector(iBegin, iEnd);
	SymmetricMatrix CovMatrix(meanVec.Nrows());

	int nRows, nCols;
	nRows = nCols = iBegin->Nrows();
	
	int i, j;
	DataSet::const_iterator	iDS;
	for(i = 1; i <= nRows; i++)
	{
		for(j = 1; j <= i/*nCols - Non-symmetric*/; j++)
		{
			CovMatrix(i, j) = 0;
			int n;
			for(iDS = iBegin, n = 0; iDS != iEnd; iDS++, n++)
			{
				CovMatrix(i, j) += ((*iDS)(i) - meanVec(i)) * ((*iDS)(j) - meanVec(j));
			}
			CovMatrix(i, j) /= n;
		}
	}

	return CovMatrix;
}

void Analyser::ComputeChain(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd, Chain &chain)
{
	using std::invalid_argument;

	if(iBegin == iEnd) throw *new invalid_argument("empty set");

	DataSet::const_iterator	iDS, iCurEnd = iBegin;
	
	int step = 1;
	chain.clear();
	for(iDS = iBegin; iDS != iEnd; iDS++)
	{
		iCurEnd++;
		SymmetricMatrix CovMatrix = ComputeCovMatrix(iBegin, iCurEnd);
		NEWMAT::DiagonalMatrix	eigenValues;
		NEWMAT::EigenValues(CovMatrix, eigenValues);
		NEWMAT::SortDescending(eigenValues);
		int n = 0;
		for(int i = 1; i <= eigenValues.Nrows(); i++)
			if(eigenValues(i) > (eigenValues(1) * 0.001)) n++;

		chain.push_back(std::pair<int, int>(step, n));
		step++;
	}
}
