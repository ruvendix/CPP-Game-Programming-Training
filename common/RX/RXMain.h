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
#ifndef MAIN_SUB_H_
#define MAIN_SUB_H_

#include "../common.h"

namespace RX
{

	class DLL_DEFINE RXMain
	{
	public:
		RXMain();
		virtual ~RXMain();

		HRESULT InitInstance();
		HRESULT CreateProgramWindow();

		virtual HRESULT RunMainRoutine(HINSTANCE hInst, INT32 iconID = 0);
		virtual HRESULT InitMain();
		virtual HRESULT DriveMain();
		virtual HRESULT Update();
		virtual HRESULT Release();
		virtual void    ToggleFullScreenMode(bool bFullScreen = false);

		void ChangeProgramTitle(const TCHAR* szTitle);
		
		// ====================================================================================
		// getter
		ROUTINE_STATE getRoutineState() const noexcept
		{
			return m_routineState;
		}

		INT32 getMessageCode() const noexcept
		{
			return m_msgCode;
		}

		HINSTANCE getProgramInstanceHandle() const noexcept
		{
			return m_hInst;
		}

		HWND getMainWindowHandle() const noexcept
		{
			return m_hMainWnd;
		}

		// ====================================================================================
		// setter
		void setWndProc(WNDPROC wndProc)
		{
			::SetWindowLongPtr(m_hMainWnd, GWLP_WNDPROC, reinterpret_cast<LONG>(wndProc));
		}

		void setSubFunc(SubFunc func, SUBFUNC_TYPE type)
		{
			m_subFunc[static_cast<INT32>(type)].func = func;
		}

		void setFullScreen(bool bFullScreen)
		{
			m_bFullScreen = bFullScreen;
		}

	protected:
		// ====================================================================================
		// �⺻ ����
		bool             m_bFullScreen;
		HWND             m_hMainWnd;
		HINSTANCE        m_hInst;
		ROUTINE_STATE    m_routineState;
		INT32            m_msgCode;
		SubFuncInfo      m_subFunc[SubFuncInfo::MAX_SUBFUNC];

		// ====================================================================================
		// ���ҽ� ����
		INT32            m_iconID;
	};

} // namespace RX end

#endif