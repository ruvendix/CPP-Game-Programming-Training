#include "base_project.h"
#include "global_variable_definition.h"

#include "game\game_board.h"

// ====================================================================================
// ��ũ�� ���Ǻ��Դϴ�.


// ====================================================================================
// ����ü �� ����ü ������Դϴ�.


// ====================================================================================
// ���� ���� ������Դϴ�.
namespace
{
	RX::RXMain* g_pMain         = nullptr;
	POINT       g_ptClientMouse = { 0, 0 };
	GameBoard*  g_pGameBoard    = nullptr;
}


// ====================================================================================
// �Լ� ������Դϴ�.
HRESULT CALLBACK OnInit();
HRESULT CALLBACK OnRelease();

// �޽��� ���ν����Դϴ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OnPaint();
void OnMouseLButtonDown(LPARAM lParam);
void OnMouseMove(LPARAM lParam);
void OnMinMaxInfo(LPARAM lParam);
void OnDestroy();

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

// Ŭ���� �Լ��Դϴ�.
HRESULT CALLBACK OnRelease()
{
	SAFE_DELTE(g_pGameBoard);
	::ReleaseDC(g_hMainWnd, g_hMainDC); // ���� DC�� �������ݴϴ�. (���۷��� ī��Ʈ ����)
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
	case WM_GETMINMAXINFO: // �ִ� �ּ�ȭ ���� �ɱ�
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

	// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
	if (g_pGameBoard)
	{
		g_pGameBoard->CalcGameBoard();
		g_pGameBoard->DrawGameBoard();
	}

	POINT ptMouseInDesktop;
	::GetCursorPos(&ptMouseInDesktop);

	WCHAR szTemp[DEFAULT_STRING_LENGTH];
	_snwprintf_s(szTemp, _countof(szTemp),
		L"����ũž ���콺 ��ǥ (%d, %d)",
		ptMouseInDesktop.x, ptMouseInDesktop.y);
	TextOut(g_hMainDC, 0, 0, szTemp, wcslen(szTemp));

	_snwprintf_s(szTemp, _countof(szTemp),
		L"Ŭ���̾�Ʈ ���콺 ��ǥ (%d, %d)",
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