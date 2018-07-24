#pragma once
#include "StdAfx.h"
#include "GameControl.h"
#include "GameLogic.h"


CGameControl::CGameControl(void)
{
}

CGameControl::~CGameControl(void)
{
}

void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	
	gameLogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
}


void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}


void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}


bool CGameControl::Link(Vertex avPath[4],int &nVexnum)
{
	if(m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}
	if(m_graph.GetVertex(m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col)
		!= m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col))
	{
		return false;
	}
	CGameLogic gameLogic;
	if(gameLogic.IsLink(m_graph,m_ptSelFirst,m_ptSelSec) == true)
	{
		gameLogic.Clear(m_graph,m_ptSelFirst,m_ptSelSec);
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}


bool CGameControl::IsWin(void)
{
	CGameLogic gameLogic;
	if(gameLogic.IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return true;
	}
	return false;
}


bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum,Vertex& v1,Vertex& v2)
{
	CGameLogic logic;
	CGraph g;
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		g.AddVertex(avPath[i].info);
	}
	if(logic.IsBlank(g))
	{
		return false;
	}
	if(logic.SearchValidPath(g,v1,v2))
	{
		return true;
	}
	return false;
}

CGraph CGameControl::GetGraph()
{
	return m_graph;
}


void CGameControl::ResetGraph(void)
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}


CGraph CGameControl::SetGraph(CGraph g)
{
	CGraph temp = m_graph;
	m_graph = g;
	return temp;
}