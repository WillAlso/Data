#include "Graph.h"

void CGraph::Init()
{
	for(int i = 0;i < 20;i++)
	{
		for(int j = 0;j < 20;j++)
		{
			m_aAdjMatrix[i][j] = 0;
		}
	}
	m_nVexNum = 0;
}

bool CGraph::InsertVex(Vex sVex)
{
	if(m_nVexNum == 20)
	{
		return false;
	}
	m_aVexs[m_nVexNum++] = sVex;
	return true;
}

bool CGraph::InsertEdge(Edge sEdge)
{
	if(sEdge.vex1 < 0 || sEdge.vex2 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 >= m_nVexNum)
	{
		return false;
	}
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

Vex CGraph::GetVex(int v)
{
	return m_aVexs[v];
}

int CGraph::FindEdge(int v,Edge aEdge[])
{
	int k = 0;
	for(int i = 0;i < m_nVexNum;i++)
	{
		if(m_aAdjMatrix[v][i] != 0)
		{
			aEdge[k].vex1 = v;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[v][i];
			k++;
		}
	}
	return k;
}

int CGraph::GetVexNum()
{
	return m_nVexNum; 
}

Edge CGraph::GetEdge(int x1,int x2)
{
	Edge t;
	t.vex1 = x1;
	t.vex2 = x2;
	t.weight = m_aAdjMatrix[x1][x2];
	return t;
}

void CGraph::DFS(int nVex,bool bVisted[],int &nIndex,PathList &pList)
{
}

void CGraph::DFSTraverse(int nVex,PathList pList)
{
	int nIndex = 0;
	bool aVisited[20] = {false};
	DFS(nVex,aVisited,nIndex,pList);
}