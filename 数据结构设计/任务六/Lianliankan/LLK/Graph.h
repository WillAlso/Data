#pragma once

class CGraph
{
public:
	CGraph(void);
	~CGraph(void);
#define MAX_VERTEX_NUM 16
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
};

