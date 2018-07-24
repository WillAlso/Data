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
	//return m_anMap[nRow][nCol];
	return m_graph.GetVertex(nRow * 4 + nCol);
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


bool CGameControl::Link(Vertex avPath[16],int &nVexnum)
{
	if(m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}
	if(m_graph.GetVertex(m_ptSelFirst.row * 4 + m_ptSelFirst.col)
		!= m_graph.GetVertex(m_ptSelSec.row * 4 + m_ptSelSec.col))
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
