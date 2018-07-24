#pragma once

#include "global.h"
#include "Graph.h"

class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
private:
	CGraph m_graph;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	
public:
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4],int &nVexnum);
	bool IsWin(void);
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum,Vertex& v1,Vertex& v2);
	CGraph GetGraph();
	void ResetGraph(void);
	CGraph SetGraph(CGraph g);
};

