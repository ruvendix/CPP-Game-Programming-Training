#include "base_project.h"
#include "global_variable_declaration.h"
#include "game/game_board.h"
#include "main.h"

// ====================================================================================
// ��ũ�� ���Ǻ��Դϴ�.


// ====================================================================================
// ����ü �� ����ü ������Դϴ�.


// ====================================================================================
// ���� ���� ������Դϴ�.
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
// �Լ� ������Դϴ�.
HRESULT CALLBACK OnInit();
HRESULT CALLBACK OnRender();
HRESULT CALLBACK OnRelease();


// �޽��� ���ν����Դϴ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OnMouseLButtonDown(LPARAM lParam);
void OnMouseMove(LPARAM lParam);
void OnChangeSize();
void OnMinMaxInfo(LPARAM lParam);
void OnDestroy();

// �� ���� �Լ��Դϴ�.
void RecreateBackBuffer();

// ====================================================================================
// <Win32 API�� WinMain()�� �������Դϴ�>
INT32 APIENTRY _tWinMain(HINSTANCE hInstance,
	                     HINSTANCE hPrevInstance,
	                     LPTSTR    szCmdLine,
	                     INT32     cmdShow)
{
	// ������� �ʴ� �Ű������� ǥ�����ݴϴ�.
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

// �ʱ�ȭ �Լ��Դϴ�.
HRESULT CALLBACK OnInit()
{
	// ������Ʈ���� ���� ����ϴ�
	// ���� ������ �ڵ�� ���� DC�� �ʱ�ȭ���ݴϴ�.
	g_hMainWnd = g_pMain->getMainWindowHandle();
	g_hMainDC = ::GetDC(g_hMainWnd);

	// ���� ���۸� �ʱ�ȭ�Դϴ�.
	g_hBackBufferDC = ::CreateCompatibleDC(g_hMainDC);
	g_hBackBufferBitmap = ::CreateCompatibleBitmap(g_hMainDC,
		g_pMain->getClientWidth(), g_pMain->getClientHeight());
	g_hOldBackBufferBitmap =
		static_cast<HBITMAP>(::SelectObject(g_hBackBufferDC, g_hBackBufferBitmap));

	// �⺻ ������ �ɼ� �����Դϴ�.
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
	// ����۸� Ŭ�������ݴϴ�.
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
		L"����ũž ���콺 ��ǥ (%d, %d)",
		ptMouseInDesktop.x, ptMouseInDesktop.y);
	TextOut(g_hBackBufferDC, 0, 0, szTemp, wcslen(szTemp));

	_snwprintf_s(szTemp, _countof(szTemp),
		L"Ŭ���̾�Ʈ ���콺 ��ǥ (%d, %d)",
		g_ptClientMouse.x, g_ptClientMouse.y);
	TextOut(g_hBackBufferDC, 0, 20, szTemp, wcslen(szTemp));
#endif

	// ������� ������ ȭ������ �����մϴ�.
	::BitBlt(g_hMainDC, 0, 0, g_pMain->getClientWidth(),
		g_pMain->getClientHeight(),
		g_hBackBufferDC, 0, 0, SRCCOPY);

	return S_OK;
}

// Ŭ���� �Լ��Դϴ�.
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
	case WM_GETMINMAXINFO: // �ִ� �ּ�ȭ ���� �ɱ�
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
			RXDEBUGLOG("�ִ�ȭ�� Ŭ���߽��ϴ�. â ȭ�� -> ��ü ȭ��");
			break;
		}
		}

		break;
	}
	}

	// Alt + Enter�� ���� ó���Դϴ�.
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		// ���� Alt + Enter�Դϴ�.
		// ������ Alt�� WM_KEYDOWN���� ���ɴϴ�.
		if (wParam == VK_RETURN)
		{
			if ((HIWORD(lParam) & KF_ALTDOWN)) // Alt�� �������� ��Ʈ �÷��׷� Ȯ���մϴ�.
			{
				g_pMain->ToggleFullScreenMode();
				g_pMain->AdjustClientRect();
				RecreateBackBuffer();
				RXDEBUGLOG("���� Alt + Enter�� �������ϴ�. ��ü ȭ�� <-> â ȭ��");
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

	// ���� ���۸������� ��ȿȭ ������ �˸��� �ʾƵ� �˴ϴ�.
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

	::ReleaseDC(g_hMainWnd, g_hMainDC); // ���� DC�� �������ݴϴ�. (���۷��� ī��Ʈ ����)
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