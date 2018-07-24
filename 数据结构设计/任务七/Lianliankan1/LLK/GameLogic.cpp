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
	int m_TMap[4][4] = {2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3};
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			g.AddVertex(m_TMap[i][j]);
			UpdateArc(g,i,j);
		}
	}
}


bool CGameLogic::IsLink(CGraph &g,Vertex v1,Vertex v2)
{
	int nV1Index = v1.row * 4 + v1.col;
	int nV2Index = v2.row * 4 + v2.col;
	AddVertex(v1);
	PushVertex(nV1Index);
	if(SearchPath(g,nV1Index,nV2Index) == true)
	{
		return true;
	}
	PopVertex();
	return false;
}

void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * 4 + v1.col;
	int nV2Index = v2.row * 4 + v2.col;

	g.UpdateVertex(nV1Index,BLANK);
	g.UpdateVertex(nV2Index,BLANK);
	UpdateArc(g,v1.row,v1.col);
	UpdateArc(g,v2.row,v2.col);
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
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

bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
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


bool CGameLogic::LineX(int anMap[][4], int nRow, int nCol1, int nCol2)
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

bool CGameLogic::LineY(int anMap[][4], int nRow1, int nRow2, int nCol)
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

bool CGameLogic::OneCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	if (anMap[v1.row][v2.col] == BLANK)
		{
			if (LineY(anMap, v1.row, v2.row, v2.col) && LineX(anMap, v1.row, v1.col,
				v2.col))
			{
				Vertex v = { v1.row, v2.col, BLANK };
				AddVertex(v);
				PushVertex(v.row * 4 + v.col);
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
			PushVertex(v.row * 4 + v.col);
			return true;
		}
	}
	return false;
}


int CGameLogic::GetVexPath(Vertex avPath[16])
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
}

bool CGameLogic::TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	for(int nCol = 0;nCol < 4;nCol++)
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
					PushVertex(vx1.row * 4 + vx1.col);
					PushVertex(vx2.row * 4 + vx2.col);
					return true;
				}
			}
		}
	}
	for(int nRow = 0;nRow < 4;nRow++)
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
					PushVertex(vx1.row * 4 + vx1.col);
					PushVertex(vx2.row * 4 + vx2.col);
					return true;
				}
			}
		}
	}
	return false;
}

void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol)
{
	int nV1Index = nRow * 4 + nCol;
	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < 3 ) {
		int nV2Index = nV1Index + 1;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}

	}
	if (nRow > 0) {
		int nV2Index = nV1Index - 4;
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < 3) {
		int nV2Index = nV1Index + 4;
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
			t.row = nVi / 4;
			t.col = nVi - t.row * 4;
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
	for(int i = 0;i < 16;i++)
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
