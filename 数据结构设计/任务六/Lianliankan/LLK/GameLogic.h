#pragma once

#include "global.h"
#include "Graph.h"

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4],Vertex v1,Vertex v2);
	void Clear(int anMap[][4], Vertex v1, Vertex v2);
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);
protected:
	Vertex m_acPath[4];
	int nVertexNum;
public:
	int GetVexPath(Vertex avPath[4]);
	void AddVertex(Vertex v);
	void DeleteVertex(void);
};

