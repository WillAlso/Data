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
	//int m_anMap[4][4];

	CGraph m_graph;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	
public:
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[16],int &nVexnum);
};

