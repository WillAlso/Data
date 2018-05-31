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

void CGraph::DFS(int nVex,bool bVisited[],int &nIndex,PathList &pList)
{
	bVisited[nVex] = true;
	pList->vex[nIndex++] = nVex;
	int nVexNum = 0;
	for(int i = 0;i < m_nVexNum;i++)
	{
		if(bVisited[i])
		{
			nVexNum++;
		}
	}
	if(nVexNum == m_nVexNum)
	{
		pList->next = new Path;
		for(int i = 0;i < m_nVexNum;i++)
		{
			pList->next->vex[i] = pList->vex[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}else
	{
		for(int i = 0;i < m_nVexNum;i++)
		{
			if((!bVisited[i]) && (m_aAdjMatrix[nVex][i] > 0))
			{
				DFS(i,bVisited,nIndex,pList);
				bVisited[i] = false;
				nIndex--;
			}
		}
	}
}

void CGraph::DFSTraverse(int nVex,PathList pList)
{
	int nIndex = 0;
	bool aVisited[20] = {false};
	DFS(nVex,aVisited,nIndex,pList);
}

int CGraph::FindShortPath(int nVexStart,int nVexEnd,Edge aPath[])
{
	int nShortPath[20][20];
	int nShortDistance[20];
	bool aVisited[20];
	int v;
	for(v = 0;v < m_nVexNum;v++)
	{
		aVisited[v] = false;
		if(m_aAdjMatrix[nVexStart][v] != 0)
		{
			nShortDistance[v] = m_aAdjMatrix[nVexStart][v];
		}else{
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;
		for(int w = 1;w < m_nVexNum;w++)
		{
			nShortPath[v][w] = -1;
		}
	}
	aVisited[nVexStart] = true;
	int min;
	for(int i = 1;i < m_nVexNum;i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;
		for(int w = 0;w < m_nVexNum;w++)
		{
			if(!aVisited[w])
			{
				if(nShortDistance[w] < min)
				{
					v = w;
					min = nShortDistance[w];
					bAdd = true;
				}
			}
		}
		if(!bAdd)
		{
			break;
		}
		aVisited[v] = true;
		nShortPath[v][i] = v;
		for(int w = 0;w < m_nVexNum;w++)
		{
			if(!aVisited[w] && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && m_aAdjMatrix[v][w] != 0)
			{
				nShortDistance[w] = min + m_aAdjMatrix[v][w];
				for(int i = 0;i < m_nVexNum;i++)
				{	
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}
	int nIndex = 0;
	int nVex1 = nVexStart;
	for(int i = 1;i < m_nVexNum;i++)
	{
		if(nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_aAdjMatrix[aPath[nIndex].vex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}

void CGraph::FindMinTree(Edge aPath[])
{
	bool aVisited[20];
	for(int i = 0;i < 20;i++)
	{
		aVisited[i] = false;
	}
	aVisited[0] = true;
	int min;
	int nVex1,nVex2;
	for(int i = 0;i < 20;i++)
	{
		min = 0x7FFFFFFF;
		for(int j = 0;j < 20;j++)
		{
			if(aVisited[j])
			{
				for(int k = 0;k < 20;k++)
				{
					if(!aVisited[k])
					{
						if((m_aAdjMatrix[j][k] < min) && (m_aAdjMatrix[j][k] != 0))
						{
							nVex1 = j;
							nVex2 = k;
							min = m_aAdjMatrix[j][k];
						}
					}
				}
			}
		}
		aPath[i].vex1 = nVex1;
		aPath[i].vex2 = nVex2;
		aPath[i].weight = m_aAdjMatrix[nVex1][nVex2];
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
}
void CGraph::Sort(Vex sVex[])
{
	int n = m_nVexNum;
	for(int i = 0;i < n;i++)
	{
		for(int j = i + 1;j < n;j++)
		{
			if(sVex[i].time < sVex[j].time)
			{
				Vex t = sVex[i];
				sVex[i] = sVex[j];
				sVex[j] = t;
			}
		}
	}
}
