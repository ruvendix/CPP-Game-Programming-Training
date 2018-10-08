#include "base_project.h"
#include "global_variable_definition.h"

#include "game\game_board.h"

// ====================================================================================
// 매크로 정의부입니다.


// ====================================================================================
// 구조체 및 공용체 선언부입니다.


// ====================================================================================
// 전역 변수 선언부입니다.
namespace
{
	RX::RXMain* g_pMain         = nullptr;
	POINT       g_ptClientMouse = { 0, 0 };
	GameBoard*  g_pGameBoard    = nullptr;
}


// ====================================================================================
// 함수 선언부입니다.
HRESULT CALLBACK OnInit();
HRESULT CALLBACK OnRelease();

// 메시지 프로시저입니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OnPaint();
void OnMouseLButtonDown(LPARAM lParam);
void OnMouseMove(LPARAM lParam);
void OnMinMaxInfo(LPARAM lParam);
void OnDestroy();

// ====================================================================================
// <Win32 API는 WinMain()이 진입점입니다>
INT32 APIENTRY _tWinMain(HINSTANCE hInstance,
	                     HINSTANCE hPrevInstance,
	                     LPTSTR    szCmdLine,
	                     INT32     cmdShow)
{
	// 사용하지 않는 매개변수를 표시해줍니다.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCmdLine);
	UNREFERENCED_PARAMETER(cmdShow);

	g_pMain = RXNew RX::RXMain;
	NULLCHK_HEAPALLOC(g_pMain);
	
	g_pMain->setSubFunc(OnInit,    SUBFUNC_TYPE::INIT);
	g_pMain->setSubFunc(OnRelease, SUBFUNC_TYPE::RELEASE);

	g_pMain->RunMainRoutine(hInstance, IDI_RUVENDIX_ICO);

	INT32 messageCode = g_pMain->getMessageCode();
	SAFE_DELTE(g_pMain);
	return messageCode;
}

// 초기화 함수입니다.
HRESULT CALLBACK OnInit()
{
	// 프로젝트에서 자주 사용하는
	// 메인 윈도우 핸들과 메인 DC를 초기화해줍니다.
	g_hMainWnd = g_pMain->getMainWindowHandle();
	g_hMainDC  = ::GetDC(g_hMainWnd);

	::SetBkMode(g_hMainDC, TRANSPARENT);
	g_pMain->setWndProc(WndProc);
	g_pMain->ChangeProgramTitle(L"IndexAndCoordinates");

	g_hHighlightBrush = ::CreateSolidBrush(RGB(0, 255, 0));

	g_pGameBoard = RXNew GameBoard;
	NULLCHK_HEAPALLOC(g_pGameBoard);
	g_pGameBoard->InitGameBoard();

	return S_OK;
}

// 클린업 함수입니다.
HRESULT CALLBACK OnRelease()
{
	SAFE_DELTE(g_pGameBoard);
	::ReleaseDC(g_hMainWnd, g_hMainDC); // 메인 DC를 정리해줍니다. (레퍼런스 카운트 감소)
	return S_OK;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		OnPaint();
		break;
	}
	case WM_DESTROY:
	{	
		OnDestroy();
		break;
	}
	case WM_LBUTTONDOWN:
	{
		OnMouseLButtonDown(lParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		OnMouseMove(lParam);
		break;
	}
	case WM_GETMINMAXINFO: // 최대 최소화 제한 걸기
	{
		OnMinMaxInfo(lParam);
		break;
	}
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void OnPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(g_hMainWnd, &ps);

	::SetBkMode(hdc, TRANSPARENT);

	HBRUSH hOldBrush = static_cast<HBRUSH>(::SelectObject(hdc, g_hHighlightBrush));

	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
	if (g_pGameBoard)
	{
		g_pGameBoard->CalcGameBoard();
		g_pGameBoard->DrawGameBoard();
	}

	POINT ptMouseInDesktop;
	::GetCursorPos(&ptMouseInDesktop);

	WCHAR szTemp[DEFAULT_STRING_LENGTH];
	_snwprintf_s(szTemp, _countof(szTemp),
		L"데스크탑 마우스 좌표 (%d, %d)",
		ptMouseInDesktop.x, ptMouseInDesktop.y);
	TextOut(g_hMainDC, 0, 0, szTemp, wcslen(szTemp));

	_snwprintf_s(szTemp, _countof(szTemp),
		L"클라이언트 마우스 좌표 (%d, %d)",
		g_ptClientMouse.x, g_ptClientMouse.y);
	TextOut(g_hMainDC, 0, 20, szTemp, wcslen(szTemp));

	::SelectObject(hdc, hOldBrush);

	EndPaint(g_hMainWnd, &ps);
}

void OnMouseLButtonDown(LPARAM lParam)
{
	g_pGameBoard->ConvertMousePosToCellIdx(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	g_pGameBoard->ApplyCellRectByPlayerClicked();
	InvalidateRect(g_hMainWnd, nullptr, true);
}

void OnMouseMove(LPARAM lParam)
{
	g_ptClientMouse.x = GET_X_LPARAM(lParam);
	g_ptClientMouse.y = GET_Y_LPARAM(lParam);
	InvalidateRect(g_hMainWnd, nullptr, true);
}

void OnMinMaxInfo(LPARAM lParam)
{
	MINMAXINFO* pMinMax = reinterpret_cast<MINMAXINFO*>(lParam);
	if (pMinMax == nullptr)
	{
		return;
	}

	pMinMax->ptMinTrackSize.x = 100 * 5;
	pMinMax->ptMinTrackSize.y = 100 * 5;
}

void OnDestroy()
{
	::DeleteObject(g_hHighlightBrush);
	PostQuitMessage(0);
}