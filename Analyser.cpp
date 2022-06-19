// Analyser.cpp: implementation of the Analyser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comprssr.h"
#include "Analyser.h"

#include <map>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Analyser::Analyser() : m_infFactor(0.999)
{

}

Analyser::~Analyser()
{

}

ColumnVector Analyser::ComputeMeanVector(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd)const
{
	using std::invalid_argument;

	if(iBegin == iEnd) throw invalid_argument("empty set");

	ColumnVector meanVec(iBegin->Nrows());
	for(int i = 1; i <= meanVec.Nrows(); i++)
		meanVec(i) = 0.0;

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
	
	if(iBegin == iEnd) throw invalid_argument("empty set");
	
	SymmetricMatrix covMatrix(iBegin->Nrows());
	int  i, j, nRows = iBegin->Nrows(), nCols = iBegin->Ncols();
	for(i = 1; i <= nRows; i++)	for(j = 1; j <= nCols; j++)
		covMatrix(i, j) = 0.0;

	ColumnVector meanVec(iBegin->Nrows());
	for(i = 1; i <= meanVec.Nrows(); i++)
		meanVec(i) = 0.0;

	DataSet::const_iterator	iDS;
	int step;
	for(iDS = iBegin, step = 1; iDS != iEnd; iDS++, step++)
	{
		meanVec += ((*iDS) - meanVec) / step;
		
		for(i = 1; i <= nRows; i++)
		{
			for(j = 1; j <= i/*nCols - Non-symmetric*/; j++)
			{
				covMatrix(i, j) += ( ((*iDS)(i) - meanVec(i))*((*iDS)(j) - meanVec(j)) - covMatrix(i, j) ) / step;
			}
		}
	}
	
	return covMatrix;
}

void Analyser::ComputeChain(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd, Chain &chain)
{
	using std::invalid_argument;
	
	if(iBegin == iEnd) throw invalid_argument("empty set");
	if(m_infFactor > 1.0 || m_infFactor < 0.0) throw invalid_argument("invalid informative factor");
	
	SymmetricMatrix covMatrix(iBegin->Nrows());
	int  i, j, nRows = iBegin->Nrows(), nCols = iBegin->Ncols();
	for(i = 1; i <= nRows; i++)	for(j = 1; j <= nCols; j++)
		covMatrix(i, j) = 0.0;
	
	ColumnVector meanVec(iBegin->Nrows());
	for(i = 1; i <= meanVec.Nrows(); i++)
		meanVec(i) = 0.0;
	
	chain.clear();

	DataSet::const_iterator	iDS;
	int step;
	for(iDS = iBegin, step = 1; iDS != iEnd; iDS++, step++)
	{
		meanVec += ((*iDS) - meanVec) / step;
		
		for(i = 1; i <= nRows; i++)
		{
			for(j = 1; j <= i/*nCols - Non-symmetric*/; j++)
			{
				covMatrix(i, j) += ( ((*iDS)(i) - meanVec(i))*((*iDS)(j) - meanVec(j)) - covMatrix(i, j) ) / step;
			}
		}
		
		//Вычисление собственных чисел >>
		NEWMAT::DiagonalMatrix	eigenValues;

		NEWMAT::EigenValues(covMatrix, eigenValues);
		NEWMAT::SortDescending(eigenValues);
		
		double sum = 0, trace = eigenValues.Trace();
		int nev = 0;

		if(!trace)
		{
			chain.push_back(std::pair<int, int>(step, nev));
			continue;
		}
		
		for(int ev_i = 1; ev_i <= eigenValues.Nrows(); ev_i++)
		{
			//if(eigenValues(ev_i) > (eigenValues(1) * 0.001)) nev++;
			if((sum += eigenValues(ev_i) / trace) < m_infFactor)
				nev++;
			else
				break;
		}

		chain.push_back(std::pair<int, int>(step, nev));
		//<< Вычисление собственных чисел
	}

}

//////////////////////////////////////////////////////////////////////
// Compressor Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Compressor::Compressor(Analyser* pAnalyser) : m_pAnalyser(pAnalyser)
{

}

Compressor::~Compressor()
{

}

bool Compressor::Initialize(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd)
{
	if(iBegin == iEnd) return false;

	SymmetricMatrix		covMatrix;

	try
	{
		covMatrix = m_pAnalyser->ComputeCovMatrix(iBegin, iEnd);
		m_meanVector = m_pAnalyser->ComputeMeanVector(iBegin, iEnd);
	}
	catch(std::invalid_argument& e)
	{
		e;
		return false;
	}

	NEWMAT::DiagonalMatrix	eigenValues;
	Matrix					eigenVectors;

	NEWMAT::EigenValues(covMatrix, eigenValues);
	NEWMAT::SortDescending(eigenValues);

	//Вычисление размерности >>
	double sum = 0, trace = eigenValues.Trace();
	int nev = 0;

	if(!trace)
	{
		m_targetDimension = 0;
		m_transformMatrix.Release();
		return false;
	}
	for(int ev_i = 1; ev_i <= eigenValues.Nrows(); ev_i++)
	{
		if((sum += eigenValues(ev_i) / trace) < m_pAnalyser->m_infFactor)
			nev++;
		else
			break;
	}
	m_decompTargetDimension = m_inputDimension = iBegin->Nrows();
	m_targetDimension = nev;
	//<< Вычисление размерности

	NEWMAT::EigenValues(covMatrix, eigenValues, eigenVectors);

	
	std::multimap<double, ColumnVector> eigenValuesAndVectors;

	int i;
	for(i = 1; i <= eigenValues.Nrows(); i++)
		eigenValuesAndVectors.insert(std::multimap<double, ColumnVector>::value_type(eigenValues(i), eigenVectors.Column(i)));
	
	m_transformMatrix.ReSize(eigenValuesAndVectors.size(), eigenValuesAndVectors.size());

	std::multimap<double, ColumnVector>::reverse_iterator iEVaV;
	for(iEVaV = eigenValuesAndVectors.rbegin(), i = 1; iEVaV != eigenValuesAndVectors.rend(); iEVaV++, i++)
		m_transformMatrix.Row(i) = iEVaV->second.t();
	
	return true;
}

bool Compressor::Compress(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd, DataSet& outputDS)
{
	if(iBegin == iEnd)
	{
		outputDS.clear();
		return true;
	}

	if(!m_targetDimension || m_targetDimension > m_inputDimension) return false;//Нужно будет бросать исключение

	outputDS.clear();
	DataSet::const_iterator iDS;
	for(iDS = iBegin; iDS != iEnd; iDS++)
	{
		DataSet::value_type tmpVec = m_transformMatrix * ((*iDS) - m_meanVector);

		outputDS.insert(outputDS.end(), tmpVec.Rows(1, m_targetDimension));
	}

	return true;
}

bool Compressor::Decompress(DataSet::const_iterator iBegin, DataSet::const_iterator iEnd, DataSet& outputDS)
{
	if(iBegin == iEnd)
	{
		outputDS.clear();
		return true;
	}

	if(!m_decompTargetDimension || m_decompTargetDimension < m_inputDimension) return false;//Нужно будет бросать исключение

	outputDS.clear();
	DataSet::const_iterator iDS;
	for(iDS = iBegin; iDS != iEnd; iDS++)
	{
		int i;
		DataSet::value_type tmpVec(m_decompTargetDimension);

		for(i = 1; i <= (*iDS).Nrows(); i++)
			tmpVec(i) = (*iDS)(i);
		for(; i <= tmpVec.Nrows(); i++)
			tmpVec(i) = 0.0;

		tmpVec = m_transformMatrix.t() * tmpVec + m_meanVector;

		outputDS.insert(outputDS.end(), tmpVec);
	}

	return true;
}

bool Compressor::ReadyToCompress()
{
	return m_targetDimension && !(m_targetDimension > m_inputDimension) && m_transformMatrix.Nrows();
}

bool Compressor::ReadyToDecompress()
{
	return m_decompTargetDimension && !(m_decompTargetDimension < m_inputDimension) && m_transformMatrix.Nrows();
}

void Compressor::SetInputDimension(int dimension)
{
	m_inputDimension = dimension;
}
