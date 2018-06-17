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
	gameLogic.InitMap(m_anMap);
}


int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
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
	if(m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] != m_anMap[m_ptSelSec.row][m_ptSelSec.col])
	{
		return false;
	}
	CGameLogic gameLogic;
	if(gameLogic.IsLink(m_anMap,m_ptSelFirst,m_ptSelSec) == true)
	{
		
		gameLogic.Clear(m_anMap,m_ptSelFirst,m_ptSelSec);
		//avPath[0] = m_ptSelFirst;
		//avPath[1] = m_ptSelSec;
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}
