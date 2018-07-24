#pragma once

#include "global.h"

class CGraph
{
public:
	CGraph(void);
	~CGraph(void);
	typedef int Vertexs[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

protected:
	Vertexs m_Vertexs;
	AdjMatrix m_AdjMatrix;
	int m_nVexNum;
	int m_nArcnum;

public:
	void InitGraph();
	void AddVertex(int ninfo);
	void AddArc(int nV1Index, int nV2Index);
	int GetVertex(int nIndex);
	bool GetArc(int nV1Index, int nV2Index);
	void UpdateVertex(int nIndex,int info);
	int GetVexnum();
	void SetVexnum(int n);
	int GetArcnum();
	void ClearGraph(void);
};

