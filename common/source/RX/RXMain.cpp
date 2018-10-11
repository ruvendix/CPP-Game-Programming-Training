/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-12
 *
 * <���� ����>
 * _tWinMain()�� �ھ� ���� ��ƾ�Դϴ�.
 * �ܺ� ������Ʈ���� ����ϸ� ���ϰ� ���α׷����� �� �� �ֽ��ϴ�.
 * ���� Ŭ���̵� �����ϹǷ� �����ο� ������ �����մϴ�.
 *
 ====================================================================================*/
#include "PCH.h"
#include "RXMain.h"

namespace
{
	RX::RXMain* g_pThis = nullptr;
}

HRESULT CALLBACK DefaultSubInit()
{
	return S_OK;
}

HRESULT CALLBACK DefaultSubUpdate()
{
	return S_OK;
}

HRESULT CALLBACK DefaultSubRender()
{
	return S_OK;
}

HRESULT CALLBACK DefaultSubRelease()
{
	return S_OK;
}

HRESULT CALLBACK DefaultSubLostDevice()
{
	return S_OK;
}

HRESULT CALLBACK DefaultSubResetDevice()
{
	return S_OK;
}

namespace
{
	SubFunc subFuncTable[SubFuncInfo::MAX_SUBFUNC] =
	{
		DefaultSubInit, DefaultSubUpdate, DefaultSubRender,
		DefaultSubRelease, DefaultSubLostDevice, DefaultSubResetDevice
	};
}

LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		RXDEBUGLOG("���α׷� â�� �����߽��ϴ�.");
		return 0;
	}
	case WM_CLOSE:
	{
		::DestroyWindow(hWnd);
		RXDEBUGLOG("�ݱ� ��ư�� Ŭ���߽��ϴ�.");
		return 0;
	}
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		RXDEBUGLOG("���α׷� â�� �����߽��ϴ�.");
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			::SendMessage(hWnd, WM_CLOSE, 0, 0); // ����ȭ �Լ�
			RXDEBUGLOG("ESC Ű�� �������ϴ�.");
			break;
		}
		}

		break;
	}
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_MAXIMIZE:
		{
			g_pThis->ToggleFullScreenMode(true);
			RXDEBUGLOG("�ִ�ȭ�� Ŭ���߽��ϴ�. â ȭ�� -> ��ü ȭ��");
			break;
		}
		}

		break;
	}
	case WM_SIZE:
	{
		g_pThis->AdjustClientRect();
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
				g_pThis->ToggleFullScreenMode();
				RXDEBUGLOG("���� Alt + Enter�� �������ϴ�. ��ü ȭ�� <-> â ȭ��");
			}
		}

		break;
	}
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

namespace RX
{

	RXMain::RXMain()
	{
		g_pThis = this;

		m_bFullScreen  = false;
		m_hMainWnd     = nullptr;
		m_hInst        = nullptr;
		m_routineState = ROUTINE_STATE::NORMAL;
		m_clientWidth  = 0;
		m_clientHeight = 0;
		m_msgCode      = 0;

		for (INT32 i = 0; i < SubFuncInfo::MAX_SUBFUNC; ++i)
		{
			m_subFunc[i].Reset();
		}

		m_iconID = 0;
	}

	RXMain::~RXMain()
	{

	}

	HRESULT RXMain::InitMain()
	{
#if defined(DEBUG) || defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

		if (FAILED(InitInstance()))
		{
			return E_FAIL;
		}

		if (FAILED(CreateProgramWindow()))
		{
			return E_FAIL;
		}

		for (INT32 i = 0; i < SubFuncInfo::MAX_SUBFUNC; ++i)
		{
			// subFunc�� nullptr�� �ƴϸ� �̹� ��ϵ� �����Դϴ�.
			if (m_subFunc[i].func == nullptr)
			{
				m_subFunc[i].func = subFuncTable[i];
			}
		}

		return S_OK;
	}

	HRESULT RXMain::InitInstance()
	{
		WNDCLASSEX wcex;
		::ZeroMemory(&wcex, sizeof(wcex));

		wcex.cbSize        = sizeof(wcex);
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = DefaultWndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = m_hInst;
		
		if (m_iconID != 0)
		{
			wcex.hIcon = ::LoadIcon(m_hInst, MAKEINTRESOURCE(m_iconID));
		}
		else
		{
			wcex.hIcon = ::LoadIcon(nullptr, 0);
		}

		wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
		wcex.lpszMenuName  = SZ_NONE;
		wcex.lpszClassName = SZ_WINDOW_CLASS;
		wcex.hIconSm       = wcex.hIcon;

		if (::RegisterClassEx(&wcex) == 0)
		{
			RXERRLOG_EFAIL_RETURN("���α׷� �ʱ�ȭ ����!");
		}
		
		RXLOG(false, "���α׷� �ʱ�ȭ ����!");
		return S_OK;
	}

	HRESULT RXMain::CreateProgramWindow()
	{
		// Ŭ���̾�Ʈ ������ ũ�⸦ �������ݴϴ�.
		RECT rtClient = { 0, 0, DEFAULT_CLIENT_WIDTH, DEFAULT_CLIENT_HEIGHT };
		::CopyRect(&m_rtClient, &rtClient);

		m_clientWidth  = DEFAULT_CLIENT_WIDTH;
		m_clientHeight = DEFAULT_CLIENT_HEIGHT;

		DWORD dwStyle;
		if (m_bFullScreen)
		{
			dwStyle = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
		}
		else
		{
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		// Ŭ���̾�Ʈ ������ ũ�⸦ �������ݴϴ�.
		// ������ �����츦 �����ؼ� �����ϰ� Ŭ���̾�Ʈ ������ ũ�⸸ ����մϴ�.
		// ��, ���� â�� ũ�⺸�� �� Ŀ���ϴ�.
		::AdjustWindowRect(&rtClient, dwStyle, FALSE);

		INT fullClientWidth  = rtClient.right - rtClient.left;
		INT fullClientHeight = rtClient.bottom - rtClient.top;
		::SetRect(&m_rtClient, 0, 0, m_clientWidth, m_clientHeight);

		// ���� ����� �ػ󵵿� ������ ���� �����ɴϴ�.
		// ���� ������ �ػ󵵰� 1920 X 1080�̶��
		// screenWidth���� 1920�� screenHeight���� 1080�� ���Ե˴ϴ�.
		INT32 screenWidth  = ::GetSystemMetrics(SM_CXSCREEN);
		INT32 screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

		// ���α׷� â�� �����մϴ�.
		// â�� ��ġ�� ����� �ػ� �������� ������Դϴ�.
		// ���� ��� 1024 X 768�� Ŭ���̾�Ʈ ������ 1920 X 1080�� ����� ������ ���� ��
		// X ��ǥ�� ((1920 - 1024) / 2), Y ��ǥ�� ((1080 - 768) / 2)�� �˴ϴ�.
		// ������ Ŭ���̾�Ʈ ������ ũ�⸦ �����ؼ� ���α׷� â�� �����ؾ� �ϹǷ�
		// rtClient.right - rtClient.left�� �����ؾ� �մϴ�.
		m_hMainWnd = ::CreateWindow(SZ_WINDOW_CLASS, SZ_PROGRAM_TITLE, dwStyle,
			(screenWidth - fullClientWidth) / 2,
			(screenHeight - fullClientHeight) / 2,
			fullClientWidth, fullClientHeight,
			::GetDesktopWindow(), // ����ȭ���� �θ� â���� �����մϴ�.
			nullptr, m_hInst, nullptr);

		NULLCHK_EFAIL_RETURN(m_hMainWnd, "���α׷� â ���� ����!");
		::ShowWindow(m_hMainWnd, SW_NORMAL);
		::UpdateWindow(m_hMainWnd);
		::ShowCursor(TRUE);

		RXLOG(false, "���α׷� â ���� ����!");
		return S_OK;
	}

	HRESULT RXMain::DriveMain()
	{
		MSG msg;
		::ZeroMemory(&msg, sizeof(msg));

		bool m_bDriveFailure = false;

		for ( ; ; )
		{
			// �ܺο����� ������ ���� ��Ʈ���� �����մϴ�.
			if (m_routineState == ROUTINE_STATE::EXIT)
			{
				m_msgCode = 0;
				break;
			}

			if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					m_routineState = ROUTINE_STATE::EXIT;
					m_msgCode = msg.wParam;
					break;
				}

				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				Update();
				Render();

				if (m_routineState == ROUTINE_STATE::FAILURE)
				{
					m_msgCode = 0;
					m_bDriveFailure = true;
					break;
				}
			}
		}

		if (m_bDriveFailure)
		{
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXMain::Update()
	{
		if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::UPDATE)].func()))
		{
			RXERRLOG_EFAIL_RETURN("���� ������Ʈ ����!");
		}

		return S_OK;
	}

	HRESULT RXMain::Render()
	{
		if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::RENDER)].func()))
		{
			RXERRLOG_EFAIL_RETURN("���� ���� ����!");
		}

		return S_OK;
	}

	HRESULT RXMain::Release()
	{
		if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::RELEASE)].func()))
		{
			RXERRLOG_EFAIL_RETURN("���� ������ ����!");
		}
		::UnregisterClass(SZ_WINDOW_CLASS, m_hInst);
		return S_OK;
	}

	void RXMain::ChangeProgramTitle(const TCHAR* szTitle)
	{
		::SetWindowText(m_hMainWnd, szTitle);
	}

	void RXMain::AdjustClientRect()
	{
		RECT rtClient;
		GetClientRect(m_hMainWnd, &rtClient);
		m_clientWidth  = rtClient.right - rtClient.left;
		m_clientHeight = rtClient.bottom - rtClient.top;
		::SetRect(&m_rtClient, 0, 0, m_clientWidth, m_clientHeight);
	}

	HRESULT RXMain::RunMainRoutine(HINSTANCE hInst, INT32 iconID)
	{
#if defined(_UNICODE) || defined(UNICODE)
		// �⺻ �������� �ѱ���� �����մϴ�.
		_wsetlocale(LC_ALL, L"kor");
#endif

		m_hInst = hInst;

		if (iconID != 0)
		{
			m_iconID = iconID;
		}

		if (FAILED(InitMain()))
		{
			Release();
			m_routineState = ROUTINE_STATE::FAILURE;
			m_msgCode      = 0;
			RXERRLOG_EFAIL_RETURN("���α׷� ������ ����!");
		}

		if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::INIT)].func()))
		{
			RXERRLOG_EFAIL_RETURN("���� �ʱ�ȭ ����!");
		}

		if (FAILED(DriveMain()))
		{
			Release();
			m_routineState = ROUTINE_STATE::FAILURE;
			m_msgCode = 0;
			RXERRLOG_EFAIL_RETURN("���α׷� ������ ����!");
		}

		Release();
		RXLOG(false, "���α׷� ���� ����!");
		return S_OK;
	}

	void RXMain::ToggleFullScreenMode(bool bFullScreen)
	{
		if (bFullScreen) // �ִ�ȭ Ű�� ���� �����Դϴ�.
		{
			m_bFullScreen = bFullScreen;
		}
		else
		{
			// ��ü ȭ���̸� â ȭ������, â ȭ���̸� ��ü ȭ������ ��ȯ�մϴ�.
			m_bFullScreen == true ? m_bFullScreen = false : m_bFullScreen = true;
		}

		INT32 screenWidth  = GetSystemMetrics(SM_CXSCREEN);
		INT32 screenHeight = GetSystemMetrics(SM_CYSCREEN);

		if (m_bFullScreen) // ��ü ȭ�� ���
		{
			SetWindowLongPtr(m_hMainWnd, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
			SetWindowPos(m_hMainWnd, HWND_TOP, 0, 0,
				screenWidth, screenHeight, SWP_NOZORDER | SWP_SHOWWINDOW);

			RXLOG(false, "��ü ȭ�� ���� ��ȯ!");
		}
		else // â ȭ�� ���
		{
			RECT clientRt;
			::SetRect(&clientRt, 0, 0, DEFAULT_CLIENT_WIDTH, DEFAULT_CLIENT_HEIGHT);
			AdjustWindowRect(&clientRt, WS_OVERLAPPEDWINDOW, false);

			SetWindowLongPtr(m_hMainWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(m_hMainWnd, HWND_TOP,
				(screenWidth - (clientRt.right - clientRt.left)) / 2,
				(screenHeight - (clientRt.bottom - clientRt.top)) / 2,
				clientRt.right, clientRt.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);

			RXLOG(false, "â ȭ�� ���� ��ȯ!");
		}

		AdjustClientRect();
	}

} // namespace RX end