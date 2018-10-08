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
#ifndef GAME_GAMEBOARD_H__
#define GAME_GAMEBOARD_H__

class GameBoard
{
public:
	GameBoard();
	virtual ~GameBoard() = default;

	void InitGameBoard();
	void CalcGameBoard();
	void DrawGameBoard();

	// Ŭ���̾�Ʈ �������� Ŭ���� ���콺 ��ǥ��
	// ���Ӻ����� �� �ε����� ��ȯ���ִ� �Լ�
	void ConvertMousePosToCellIdx(INT32 clientMouseX, INT32 clientMouseY);

	// ���Ӻ����� �� �ε�����
	// Ŭ���̾�Ʈ ������ RECT ��ǥ�� ��ȯ���ִ� �Լ�
	RECT* ConvertCellIdxToGameBoardRect(INT32 cellIdx, RECT* pRtCell);

	// �۾��� �� �� ���ϰ� �Ϸ��� ���� �Լ�
	void ApplyCellRectByPlayerClicked()
	{
		ConvertCellIdxToGameBoardRect(m_cellIdxByPlayerClicked, &m_rtCellByPlayerClicked);
	}

	// ====================================================================================
	// getter
	INT32 getCellIdxByPlayerClicked() const noexcept
	{
		return m_cellIdxByPlayerClicked;
	}

	// ====================================================================================
	// setter

private:
	RECT  m_rtGameBoard;
	RECT  m_rtCellByPlayerClicked;
	INT32 m_cellIdxByPlayerClicked;
	INT32 m_columnCnt;
	INT32 m_rowCnt;
};

#endif