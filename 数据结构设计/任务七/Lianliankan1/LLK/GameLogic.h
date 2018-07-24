#pragma once

#include "global.h"
#include "Graph.h"

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	void InitMap(CGraph &g);
	bool IsLink(CGraph &g,Vertex v1,Vertex v2);
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);
protected:
	Vertex m_acPath[16];
	int m_anPath[16];
	int nVertexNum;
	int m_nCorner;
public:
	int GetVexPath(Vertex avPath[16]);
	void AddVertex(Vertex v);
	void UpdateArc(CGraph &g, int nRow, int nCol);
	bool SearchPath(CGraph& g, int nV0, int nV1);
	bool IsExsit(int nVi);
	bool IsCornor(void);
	void PushVertex(int nV);
	void PopVertex(void);
};

