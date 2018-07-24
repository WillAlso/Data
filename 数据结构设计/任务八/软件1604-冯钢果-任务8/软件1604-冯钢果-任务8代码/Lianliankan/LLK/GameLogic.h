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
	bool LinkInRow(int anMap[][MAX_COL], Vertex v1, Vertex v2);
	bool LinkInCol(int anMap[][MAX_COL], Vertex v1, Vertex v2);
	bool LineX(int anMap[][MAX_COL], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][MAX_COL], int nRow1, int nRow2, int nCol);
	bool OneCornerLink(int anMap[][MAX_COL], Vertex v1, Vertex v2);
	bool TwoCornerLink(int anMap[][MAX_COL], Vertex v1, Vertex v2);
protected:
	Vertex m_acPath[4];
	int m_anPath[MAX_VERTEX_NUM];
	int nVertexNum;
	int m_nCorner;
public:
	int GetVexPath(Vertex avPath[4]);
	void AddVertex(Vertex v);
	void UpdateArc(CGraph &g, int nRow, int nCol);
	bool SearchPath(CGraph& g, int nV0, int nV1);
	bool IsExsit(int nVi);
	bool IsCornor(void);
	void PushVertex(int nV);
	void PopVertex(void);
	void DeleteVertex(void);
	bool IsBlank(CGraph& graph);
	bool SearchValidPath(CGraph& g,Vertex &v1,Vertex &v2);
	void ResetGraph(CGraph& g);
};

