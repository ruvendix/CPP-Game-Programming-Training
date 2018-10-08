/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-10-09
 *
 * <파일 내용>
 * 게임보드 클래스입니다.
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

	// 클라이언트 영역에서 클릭한 마우스 좌표를
	// 게임보드의 셀 인덱스로 변환해주는 함수
	void ConvertMousePosToCellIdx(INT32 clientMouseX, INT32 clientMouseY);

	// 게임보드의 셀 인덱스를
	// 클라이언트 영역의 RECT 좌표로 변환해주는 함수
	RECT* ConvertCellIdxToGameBoardRect(INT32 cellIdx, RECT* pRtCell);

	// 작업을 좀 더 편하게 하려고 만든 함수
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