#include "StdAfx.h"
#include "Graph.h"


CGraph::CGraph(void)
{
	InitGraph();
	m_nVexNum = 0;
	m_nArcnum = 0;
}


CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertexs[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			m_AdjMatrix[i][j] = false;
	}
}

void CGraph::AddVertex(int ninfo)
{
	if (m_nVexNum >= MAX_VERTEX_NUM) {
		return;
	}	
	m_Vertexs[m_nVexNum] = ninfo;
	m_nVexNum++;
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertexs[nIndex];
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

void CGraph::UpdateVertex(int nIndex,int info)
{
	m_Vertexs[nIndex] = info;
}

int CGraph::GetVexnum()
{
	return m_nVexNum;
}

int CGraph::GetArcnum()
{
	return m_nArcnum;
}


void CGraph::ClearGraph(void)
{
	InitGraph();
}

void CGraph::SetVexnum(int n)
{
	m_nVexNum = n;
}
