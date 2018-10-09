/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-09
 *
 * <���� ����>
 * ���Ӻ��� Ŭ�����Դϴ�.
 *
 ====================================================================================*/
#include "base_project.h"
#include "game_board.h"

GameBoard::GameBoard()
{
	InitGameBoard();
}

void GameBoard::InitGameBoard()
{
	::SetRectEmpty(&m_rtGameBoard);
	m_cellIdxByPlayerClicked = -1;
	m_columnCnt = 3;
	m_rowCnt    = 3;
}

void GameBoard::CalcGameBoard()
{
	RECT rtClient;
	::SetRectEmpty(&rtClient);
	::GetClientRect(g_hMainWnd, &rtClient);

	INT32 width  = rtClient.right - rtClient.left;
	INT32 height = rtClient.bottom - rtClient.top;

	// ȭ�� �߾ӿ� ���� �ϴ� ���
	m_rtGameBoard.left = (width - CELL_SIZE * m_columnCnt) / 2;
	m_rtGameBoard.top  = (height - CELL_SIZE * m_columnCnt) / 2;

	m_rtGameBoard.right  = m_rtGameBoard.left + CELL_SIZE * m_columnCnt;
	m_rtGameBoard.bottom = m_rtGameBoard.top + CELL_SIZE * m_rowCnt;
}

void GameBoard::ConvertMousePosToCellIdx(INT32 clientMouseX, INT32 clientMouseY)
{
	POINT ptClickedPos = { clientMouseX, clientMouseY };
	if (PtInRect(&m_rtGameBoard, ptClickedPos) == TRUE)
	{
		// Ŭ���� ���콺 ��ǥ�� ���Ӻ��� ��ġ�� �����ݴϴ�.
		POINT PosInGameBoard =
		{ 
			ptClickedPos.x - m_rtGameBoard.left,
			ptClickedPos.y - m_rtGameBoard.top
		};

		// ���Ӻ��� ������ ��ǥ�� �ε����� ��ȯ�մϴ�.
		INT32 column = PosInGameBoard.x / CELL_SIZE;
		INT32 row    = PosInGameBoard.y / CELL_SIZE;

		m_cellIdxByPlayerClicked = column + (row * m_columnCnt);
	}
}

RECT* GameBoard::ConvertCellIdxToGameBoardRect(INT32 cellIdx, RECT * pRtCell)
{
	if ( (cellIdx < 0) ||
		 (cellIdx > (m_rowCnt * m_columnCnt) - 1) )
	{
		return nullptr;
	}

	// �� �ε����� ��� ���� �и��մϴ�.
	INT32 column = cellIdx % m_columnCnt;
	INT32 row    = cellIdx / m_columnCnt;

	// ���Ӻ��� ��ġ�� �����ְ�
	// �� �ε����� �̿��ؼ� �� ���̸�ŭ �����ݴϴ�.
	pRtCell->left   = m_rtGameBoard.left + (column * CELL_SIZE) + 1;
	pRtCell->top    = m_rtGameBoard.top + (row * CELL_SIZE) + 1;
	pRtCell->right  = pRtCell->left + CELL_SIZE - 1;
	pRtCell->bottom = pRtCell->top + CELL_SIZE - 1;

	return pRtCell;
}

void GameBoard::DrawGameBoard()
{
	//::Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	::FillRect(g_hMainDC, &m_rtGameBoard, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));

	for (INT32 i = 0; i < m_columnCnt; ++i)
	{
		// �������� �׸��ϴ�.
		RX::DrawLineWin32(g_hMainDC, m_rtGameBoard.left + CELL_SIZE * i, m_rtGameBoard.top,
			m_rtGameBoard.left + CELL_SIZE * i, m_rtGameBoard.bottom);
	}

	for (INT32 i = 0; i < m_rowCnt; ++i)
	{
		// �������� �׸��ϴ�.
		RX::DrawLineWin32(g_hMainDC, m_rtGameBoard.left, m_rtGameBoard.top + CELL_SIZE * i,
			m_rtGameBoard.right, m_rtGameBoard.top + CELL_SIZE * i);
	}

	// Ŭ���� �� �ε����� �ִٸ� �� ���� g_hHighlightBrush�� ä��ϴ�.
	if (m_cellIdxByPlayerClicked != -1)
	{
		ConvertCellIdxToGameBoardRect(m_cellIdxByPlayerClicked, &m_rtCellByPlayerClicked);
		::FillRect(g_hMainDC, &m_rtCellByPlayerClicked, g_hHighlightBrush);
	}

#ifdef _DEBUG // ����� ����
	RECT rtDebug = { 0, 0, 256, 60 };
	::FillRect(g_hMainDC, &rtDebug, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));

	WCHAR szTemp[256];
	for (INT32 i = 0; i < m_rowCnt; ++i)
	{
		for (INT32 j = 0; j < m_columnCnt; ++j)
		{
			_snwprintf_s(szTemp, _countof(szTemp), L"%d", j + (i * m_columnCnt));

			RECT rtCell;
			::SetRect(&rtCell, m_rtGameBoard.left + (CELL_SIZE * j),
				m_rtGameBoard.top + (CELL_SIZE * i), 0, 0);
			rtCell.right = rtCell.left + CELL_SIZE;
			rtCell.bottom = rtCell.top + CELL_SIZE;
			
			::DrawText(g_hMainDC, szTemp, -1, &rtCell, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
	}

	INT32 clickedIdx = getCellIdxByPlayerClicked();
	_snwprintf_s(szTemp, _countof(szTemp),
		L"Ŭ���� �� �ε��� = %d", clickedIdx);
	TextOut(g_hMainDC, 0, 40, szTemp, wcslen(szTemp));
#endif
}