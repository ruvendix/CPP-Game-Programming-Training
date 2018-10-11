#include "base_project.h"
#include "global_variable_declaration.h"
#include "game/game_board.h"
#include "main.h"

// ====================================================================================
// 매크로 정의부입니다.


// ====================================================================================
// 구조체 및 공용체 선언부입니다.


// ====================================================================================
// 전역 변수 선언부입니다.
namespace
{
	RX::RXMain* g_pMain         = nullptr;
	GameBoard*  g_pGameBoard    = nullptr;
	POINT       g_ptClientMouse = { 0, 0 };
}

extern HWND g_hMainWnd = nullptr;
extern HDC  g_hMainDC  = nullptr;

extern HBRUSH  g_hHighlightBrush      = nullptr;
extern HDC     g_hBackBufferDC        = nullptr;
extern HBITMAP g_hBackBufferBitmap    = nullptr;
extern HBITMAP g_hOldBackBufferBitmap = nullptr;

// ====================================================================================
// 함수 선언부입니다.
HRESULT CALLBACK OnInit();
HRESULT CALLBACK OnRender();
HRESULT CALLBACK OnRelease();


// 메시지 프로시저입니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OnMouseLButtonDown(LPARAM lParam);
void OnMouseMove(LPARAM lParam);
void OnChangeSize();
void OnMinMaxInfo(LPARAM lParam);
void OnDestroy();

// 그 외의 함수입니다.
void RecreateBackBuffer();

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
	g_pMain->setSubFunc(OnRender,  SUBFUNC_TYPE::RENDER);
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
	g_hMainDC = ::GetDC(g_hMainWnd);

	// 더블 버퍼링 초기화입니다.
	g_hBackBufferDC = ::CreateCompatibleDC(g_hMainDC);
	g_hBackBufferBitmap = ::CreateCompatibleBitmap(g_hMainDC,
		g_pMain->getClientWidth(), g_pMain->getClientHeight());
	g_hOldBackBufferBitmap =
		static_cast<HBITMAP>(::SelectObject(g_hBackBufferDC, g_hBackBufferBitmap));

	// 기본 렌더링 옵션 설정입니다.
	::SetBkMode(g_hBackBufferDC, TRANSPARENT);
	g_hHighlightBrush = ::CreateSolidBrush(RGB(0, 255, 0));

	g_pMain->setWndProc(WndProc);
	g_pMain->ChangeProgramTitle(L"IndexAndCoordinates");

	g_pGameBoard = RXNew GameBoard;
	NULLCHK_HEAPALLOC(g_pGameBoard);
	g_pGameBoard->InitGameBoard();

	return S_OK;
}

HRESULT CALLBACK OnRender()
{
	// 백버퍼를 클리어해줍니다.
	::FillRect(g_hBackBufferDC, &g_pMain->getClientRect(),
		static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH)));

	if (g_pGameBoard)
	{
		g_pGameBoard->CalcGameBoard();
		g_pGameBoard->DrawGameBoard();
	}

#ifdef _DEBUG
	POINT ptMouseInDesktop;
	::GetCursorPos(&ptMouseInDesktop);

	WCHAR szTemp[DEFAULT_STRING_LENGTH];
	_snwprintf_s(szTemp, _countof(szTemp),
		L"데스크탑 마우스 좌표 (%d, %d)",
		ptMouseInDesktop.x, ptMouseInDesktop.y);
	TextOut(g_hBackBufferDC, 0, 0, szTemp, wcslen(szTemp));

	_snwprintf_s(szTemp, _countof(szTemp),
		L"클라이언트 마우스 좌표 (%d, %d)",
		g_ptClientMouse.x, g_ptClientMouse.y);
	TextOut(g_hBackBufferDC, 0, 20, szTemp, wcslen(szTemp));
#endif

	// 백버퍼의 내용을 화면으로 복사합니다.
	::BitBlt(g_hMainDC, 0, 0, g_pMain->getClientWidth(),
		g_pMain->getClientHeight(),
		g_hBackBufferDC, 0, 0, SRCCOPY);

	return S_OK;
}

// 클린업 함수입니다.
HRESULT CALLBACK OnRelease()
{
	SAFE_DELTE(g_pGameBoard);
	return S_OK;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		OnRender();
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
	case WM_SIZE:
	{
		OnChangeSize();
		break;
	}
	case WM_GETMINMAXINFO: // 최대 최소화 제한 걸기
	{
		OnMinMaxInfo(lParam);
		break;
	}
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_MAXIMIZE:
		{
			g_pMain->ToggleFullScreenMode(true);
			g_pMain->AdjustClientRect();
			RecreateBackBuffer();
			RXDEBUGLOG("최대화를 클릭했습니다. 창 화면 -> 전체 화면");
			break;
		}
		}

		break;
	}
	}

	// Alt + Enter를 위한 처리입니다.
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		// 왼쪽 Alt + Enter입니다.
		// 오른쪽 Alt는 WM_KEYDOWN으로 들어옵니다.
		if (wParam == VK_RETURN)
		{
			if ((HIWORD(lParam) & KF_ALTDOWN)) // Alt를 눌렀는지 비트 플래그로 확인합니다.
			{
				g_pMain->ToggleFullScreenMode();
				g_pMain->AdjustClientRect();
				RecreateBackBuffer();
				RXDEBUGLOG("왼쪽 Alt + Enter를 눌렀습니다. 전체 화면 <-> 창 화면");
			}
		}

		break;
	}
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

//void OnPaint()
//{
//	PAINTSTRUCT ps;
//	HDC hdc = BeginPaint(g_hMainWnd, &ps);
//	EndPaint(g_hMainWnd, &ps);
//}

void OnMouseLButtonDown(LPARAM lParam)
{
	g_pGameBoard->ConvertMousePosToCellIdx(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	g_pGameBoard->ApplyCellRectByPlayerClicked();
	InvalidateRect(g_hMainWnd, nullptr, TRUE);
}

void OnMouseMove(LPARAM lParam)
{
	g_ptClientMouse.x = GET_X_LPARAM(lParam);
	g_ptClientMouse.y = GET_Y_LPARAM(lParam);

	// 더블 버퍼링에서는 무효화 영역을 알리지 않아도 됩니다.
	//InvalidateRect(g_hMainWnd, nullptr, TRUE);
}

void OnChangeSize()
{
	g_pMain->AdjustClientRect();
	RecreateBackBuffer();
}

void OnMinMaxInfo(LPARAM lParam)
{
	MINMAXINFO* pMinMax = reinterpret_cast<MINMAXINFO*>(lParam);
	NULLCHK_RETURN_NOCOMENT(pMinMax);

	pMinMax->ptMinTrackSize.x = CELL_SIZE * 5;
	pMinMax->ptMinTrackSize.y = CELL_SIZE * 5;
}

void OnDestroy()
{
	::DeleteObject(g_hHighlightBrush);

	::SelectObject(g_hBackBufferDC, g_hOldBackBufferBitmap);
	::DeleteObject(g_hBackBufferBitmap);
	::DeleteDC(g_hBackBufferDC);

	::ReleaseDC(g_hMainWnd, g_hMainDC); // 메인 DC를 정리해줍니다. (레퍼런스 카운트 감소)
	::PostQuitMessage(0);
}

void RecreateBackBuffer()
{
	::SelectObject(g_hBackBufferDC, g_hOldBackBufferBitmap);
	::DeleteObject(g_hBackBufferBitmap);
	g_hBackBufferBitmap = ::CreateCompatibleBitmap(g_hMainDC,
		g_pMain->getClientWidth(), g_pMain->getClientHeight());
	g_hOldBackBufferBitmap =
		static_cast<HBITMAP>(::SelectObject(g_hBackBufferDC, g_hBackBufferBitmap));
}