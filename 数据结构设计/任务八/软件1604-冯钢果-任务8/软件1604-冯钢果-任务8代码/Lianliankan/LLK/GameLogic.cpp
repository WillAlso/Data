#include "StdAfx.h"
#include "GameLogic.h"


CGameLogic::CGameLogic(void)
{
	nVertexNum = 0;
	m_nCorner = 0;
}


CGameLogic::~CGameLogic(void)
{
}


void CGameLogic::InitMap(CGraph &g)
{
	int anTemp[MAX_PIC_NUM * REPEAT_NUM];
	for(int i = 0;i < MAX_PIC_NUM;i++)
	{
		for(int j = 0;j < REPEAT_NUM;j++)
		{
			anTemp[i * REPEAT_NUM + j] = i;
			g.UpdateVertex(i * REPEAT_NUM + j,i);
		}
	}
	srand((int)time(NULL));
	int nVertex = MAX_ROW * MAX_COL;
	for(int i = 0;i < nVertex;i++)
	{
		int nIndex1 = rand() % nVertex;
		int nIndex2 = rand() % nVertex;
		int temp = 0;
		int temp1 = g.GetVertex(nIndex1);
		int temp2 = g.GetVertex(nIndex2);
		temp = temp1;
		temp1 = temp2;
		temp2 = temp;
		g.UpdateVertex(nIndex1,temp1);
		g.UpdateVertex(nIndex2,temp2);
	}
}


bool CGameLogic::IsLink(CGraph &g,Vertex v1,Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	int anMap[MAX_ROW][MAX_COL];
	for(int i = 0;i < MAX_ROW;i++)
	{
		for(int j = 0;j < MAX_COL;j++)
		{
			anMap[i][j] = g.GetVertex(i * MAX_COL + j);
		}
	}
	AddVertex(v1);
	if(nRow1 == nRow2)
	{
		if(LinkInRow(anMap,v1,v2))
		{
			AddVertex(v2);
			return true;
		}
	}
	if(nCol1 == nCol2)
	{
		if(LinkInCol(anMap,v1,v2))
		{
			AddVertex(v2);
			return true;
		}
	}
	//two
	if(OneCornerLink(anMap,v1,v2))
	{
		AddVertex(v2);
		return true;
	}
	//three
	if(TwoCornerLink(anMap,v1,v2))
	{
		AddVertex(v2);
		return true;
	}
	DeleteVertex();
	return false;
}

void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;

	g.UpdateVertex(nV1Index,BLANK);
	g.UpdateVertex(nV2Index,BLANK);
	UpdateArc(g,v1.row,v1.col);
	UpdateArc(g,v2.row,v2.col);
}

bool CGameLogic::LinkInRow(int anMap[][MAX_COL], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if(nCol1 > nCol2)
	{
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	for(int i = nCol1 + 1;i <= nCol2;i++)
	{
		if(i == nCol2)
		{
			return true;
		}
		if(anMap[nRow1][i] != BLANK)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::LinkInCol(int anMap[][MAX_COL], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if(nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	for(int i = nRow1 + 1;i <= nRow2;i++)
	{
		if(i == nRow2)
		{
			return true;
		}
		if(anMap[i][nCol1] != BLANK)
		{
			break;
		}
	}
	return false;
}


bool CGameLogic::LineX(int anMap[][MAX_COL], int nRow, int nCol1, int nCol2)
{
	if(nCol1 > nCol2)
	{
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	for(int nCol = nCol1 + 1;nCol <= nCol2;nCol++)
	{
		if(nCol == nCol2)
		{
			return true;
		}
		if(anMap[nRow][nCol] != BLANK)
		{
			return false;
		}
	}
	return false;
}

bool CGameLogic::LineY(int anMap[][MAX_COL], int nRow1, int nRow2, int nCol)
{
	if(nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	for(int nRow = nRow1 + 1;nRow <= nRow2;nRow++)
	{
		if(nRow == nRow2)
		{
			return true;
		}
		if(anMap[nRow][nCol] != BLANK)
		{
			return false;
		}
	}
	return false;
}

bool CGameLogic::OneCornerLink(int anMap[][MAX_COL], Vertex v1, Vertex v2)
{
	if (anMap[v1.row][v2.col] == BLANK)
		{
			if (LineY(anMap, v1.row, v2.row, v2.col) && LineX(anMap, v1.row, v1.col,
				v2.col))
			{
				Vertex v = { v1.row, v2.col, BLANK };
				AddVertex(v);
				return true;
			}
		}
	if (anMap[v2.row][v1.col] == BLANK)
	{
		if (LineY(anMap, v1.row, v2.row, v1.col) && LineX(anMap, v2.row, v1.col,
			v2.col))
		{
			Vertex v = { v2.row, v1.col, BLANK };
			AddVertex(v);
			return true;
		}
	}
	return false;
}


int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	for(int i = 0;i < nVertexNum;i++)
	{
		avPath[i] = m_acPath[i];
	}
	return nVertexNum;
}


void CGameLogic::AddVertex(Vertex v)
{
	m_acPath[nVertexNum] = v;
	nVertexNum++;
}

void CGameLogic::DeleteVertex(void)
{
	nVertexNum--;
}

bool CGameLogic::TwoCornerLink(int anMap[][MAX_COL], Vertex v1, Vertex v2)
{
	for(int nCol = 0;nCol < MAX_COL;nCol++)
	{
		if(anMap[v1.row][nCol] == BLANK && anMap[v2.row][nCol] == BLANK)
		{
			if(LineY(anMap,v1.row,v2.row,nCol))
			{
				if(LineX(anMap,v1.row,v1.col,nCol) && LineX(anMap,v2.row,v2.col,nCol))
				{
					Vertex vx1 = {v1.row,nCol,BLANK};
					Vertex vx2 = {v2.row,nCol,BLANK};
					AddVertex(vx1);
					AddVertex(vx2);
					return true;
				}
			}
		}
	}
	for(int nRow = 0;nRow < MAX_ROW;nRow++)
	{
		if(anMap[nRow][v1.col] == BLANK && anMap[nRow][v2.col] == BLANK)
		{
			if(LineX(anMap,nRow,v1.col,v2.col))
			{
				if(LineY(anMap,nRow,v1.row,v1.col) && LineY(anMap,nRow,v2.row,v2.col))
				{
					Vertex vx1 = {nRow,v1.col,BLANK};
					Vertex vx2 = {nRow,v2.col,BLANK};
					AddVertex(vx1);
					AddVertex(vx2);
					return true;
				}
			}
		}
	}
	return false;
}

void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_COL + nCol;
	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < MAX_COL - 1) {
		int nV2Index = nV1Index + 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}

	}
	if (nRow > 0) {
		int nV2Index = nV1Index - MAX_COL;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < MAX_ROW - 1) {
		int nV2Index = nV1Index + MAX_COL;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}


bool CGameLogic::SearchPath(CGraph& g, int nV0, int nV1)
{
	int nVexnum = g.GetVexnum();
	for(int nVi = 0;nVi < nVexnum;nVi++)
	{
		if(g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			Vertex t;
			t.row = nVi / MAX_COL;
			t.col = nVi - t.row * MAX_COL;
			AddVertex(t);
			PushVertex(nVi);
			if(m_nCorner > 2)
			{
				PopVertex();
				continue;
			}
			if(nVi != nV1)
			{
				if(g.GetVertex(nVi) != BLANK)
				{
					PopVertex();
					continue;
				}
				if(SearchPath(g,nVi,nV1))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
			PopVertex();
		}
	}
	return false;
}


bool CGameLogic::IsExsit(int nVi)
{
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		if(m_anPath[i] == nVi)
		{
			return true;
		}
	}
	return false;
}


bool CGameLogic::IsCornor(void)
{
	if(nVertexNum >= 3)
	{
		/*if((m_anPath[nVertexNum - 1] + m_anPath[nVertexNum - 3]) / 2 == m_anPath[nVertexNum - 2])
		{
			return true;
		}*/
		if((m_acPath[nVertexNum - 1].row == m_acPath[nVertexNum - 2].row || m_acPath[nVertexNum - 1].col == m_acPath[nVertexNum - 2].col) &&
			(m_acPath[nVertexNum - 3].row == m_acPath[nVertexNum - 2].row || m_acPath[nVertexNum - 3].col == m_acPath[nVertexNum - 2].col) &&
			!(m_acPath[nVertexNum - 1].row == m_acPath[nVertexNum - 3].row || m_acPath[nVertexNum - 1].col == m_acPath[nVertexNum - 3].col))
		{
			return true;
		}
	}
	return false;
}


void CGameLogic::PushVertex(int nV)
{
	m_anPath[nVertexNum] = nV;
	nVertexNum++;
	if(IsCornor())
	{
		m_nCorner++;
	}
}


void CGameLogic::PopVertex(void)
{
	if(IsCornor())
	{
		m_nCorner--;
	}
	nVertexNum--;
}


bool CGameLogic::IsBlank(CGraph& graph)
{
	int nVexnum = graph.GetVexnum();
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		if(graph.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}


bool CGameLogic::SearchValidPath(CGraph& g,Vertex &v1,Vertex &v2)
{
	int nVexnum = g.GetVexnum();
	for(int i = 0;i < nVexnum;i++)
	{
		if(g.GetVertex(i) != BLANK)
		{
			v1.row = i / MAX_COL;
			v1.col = i - v1.row * MAX_COL;
		}else
		{
			continue;
		}
		for(int j = 0;j < nVexnum;j++)
		{
			if(g.GetVertex(j) != BLANK && i != j && g.GetVertex(i) == g.GetVertex(j))
			{
				v2.row = j / MAX_COL;
				v2.col = j - v2.row * MAX_COL;
				if(IsLink(g,v1,v2))
				{
					return true;
				}
			}else
			{
				continue;
			}
		}
	}
	return false;
}


void CGameLogic::ResetGraph(CGraph& g)
{
	InitMap(g);
	int nRows = MAX_ROW;
	int nCols = MAX_COL;
	srand((int)time(NULL));
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		int temp = 0;
		int temp1 = g.GetVertex(nIndex1);
		int temp2 = g.GetVertex(nIndex2);
		temp = temp1;
		temp1 = temp2;
		temp2 = temp;
		g.UpdateVertex(nIndex1,temp1);
		g.UpdateVertex(nIndex2,temp2);
	}
}
