#include "StdAfx.h"
#include "GameLogic.h"


CGameLogic::CGameLogic(void)
{
	nVertexNum = 0;
}


CGameLogic::~CGameLogic(void)
{
}


void CGameLogic::InitMap(int anMap[][4])
{
	int m_TMap[4][4] = {2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3};
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			anMap[i][j] = m_TMap[i][j];
		}
	}
}


bool CGameLogic::IsLink(int anMap[][4],Vertex v1,Vertex v2)
{
	/*int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	if(anMap[nRow1][nCol1] == anMap[nRow2][nCol2])
	{
		return true;
	}*/
	//one
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
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


void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
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
	/*
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	if(nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
		nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	if(nCol1 > nCol2)
	{
		if(LineY(anMap,nRow1 + 1,nRow2,nCol1) && LineX(anMap,nRow2,nCol1,nCol2 + 1))
		{
			Vertex v;
			v.row = nRow2;
			v.col = nCol1;
			AddVertex(v);
			return true;
		}
		if(LineY(anMap,nRow2 - 1,nRow1,nCol2) && LineX(anMap,nRow1,nCol2,nCol1 - 1))
		{
			Vertex v;
			v.row = nRow1;
			v.col = nCol2;
			AddVertex(v);
			return true;
		}
	}else{
		if(LineY(anMap,nRow1 + 1,nRow2,nCol1) && LineX(anMap,nRow2,nCol1,nCol2 - 1))
		{
			Vertex v;
			v.row = nRow2;
			v.col = nCol1;
			AddVertex(v);
			return true;
		}
		if(LineY(anMap,nRow2 - 1,nRow1,nCol2) && LineX(anMap,nRow1,nCol2,nCol1 + 1))
		{
			Vertex v;
			v.row = nRow1;
			v.col = nCol2;
			AddVertex(v);
			return true;
		}
	}*/
	
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


int CGameLogic::GetVexPath(Vertex avPath[4])
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
					return true;
				}
			}
		}
	}
	return false;
}