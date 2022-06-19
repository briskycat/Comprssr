// types.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPES_H__C22B60B6_2BAC_4895_8D6C_0807D9FD3030__INCLUDED_)
#define AFX_TYPES_H__C22B60B6_2BAC_4895_8D6C_0807D9FD3030__INCLUDED_

#include "newmat/newmatap.h"
#include <vector>
#include <utility>
#include <set>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef NEWMAT::RowVector						RowVector;
typedef NEWMAT::ColumnVector					ColumnVector;
typedef NEWMAT::Matrix							Matrix;
typedef NEWMAT::SymmetricMatrix					SymmetricMatrix;

typedef	std::vector<ColumnVector>				DataSet;
/*
class VecLess
{
public:
	bool operator()(const ColumnVector& v1, const ColumnVector& v2)
	{
		return v1.SumSquare() < v2.SumSquare();
	}
};
typedef	std::multiset<ColumnVector, VecLess>	DataSet;
*/
typedef	std::vector<std::pair<int, int> >		Chain;

#endif // !defined(AFX_TYPES_H__C22B60B6_2BAC_4895_8D6C_0807D9FD3030__INCLUDED_)
