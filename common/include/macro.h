/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-07
 *
 * <���� ����>
 * �������� ���Ǵ� ��ũ�� �����Դϴ�.
 * ���� �Լ��� ������ �޽��ϴ�.
 *
 ====================================================================================*/
#ifndef MACRO_H__
#define MACRO_H__

#include "global_function.h"

// ====================================================================================
// ���� �Ҵ�, Release, LostDevice, ResetDevice ���� ��ũ���Դϴ�.
// ���� �Ҵ� ������ _NORMAL_BLOCK���� �����մϴ�.
//
#if defined(DEBUG) | defined(_DEBUG)
#define RXNew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define RXNew new
#endif

#if defined(DEBUG) | defined(_DEBUG)
#define RXMalloc(size) _malloc_dbg(size, _NORMAL_BLOCK, __FILE__ , __LINE__)
#else
#define RXMalloc(size) malloc(size)
#endif

#define SAFE_DELTE(ptr)\
if (ptr)\
{\
	delete ptr;\
	ptr = nullptr;\
}

#define SAFE_DELTE_ARR(ptr)\
if (ptr)\
{\
	delete[] ptr;\
	ptr = nullptr;\
}

#define SAFE_RELEASE(ptr)\
if (ptr)\
{\
    ptr->Release();\
    ptr = nullptr;\
}

// ��ġ�� �ս����� �� ���˴ϴ�.
#define SAFE_LOST_DEVICE(ptr)\
if (ptr)\
{\
	ptr->OnLostDevice();\
}

// ��ġ�� ������ �� ���˴ϴ�.
#define SAFE_RESET_DEVICE(ptr)\
if (ptr)\
{\
	ptr->OnResetDevice();\
}

// ====================================================================================
// �޽��� �ڽ� ���� ��ũ���Դϴ�.
//
#if defined(_UNICODE) || defined(UNICODE)
#define WIDEN(x)       L##x
#define WIDEN2(x)      WIDEN(x)
#define __TFILE__      WIDEN2(__FILE__)
#define __TFUNCTION__  WIDEN2(__FUNCTION__)
#define __TFUNSIG__    WIDEN2(__FUNCSIG__)
#else
#define __TFILE__      __FILE__
#define __TFUNCTION__  __FUNCTION__
#define __TFUNSIG__    __FUNCSIG__
#endif

// �޽��� �ڽ��� ����մϴ�.
// ������Ʈ ��忡 ������� ������ �˷���� �� �� ����մϴ�.
// ERRMSGBOX()�� �α׷ε� ����մϴ�.
#if defined(_UNICODE) || defined(UNICODE)
#define MSGBOX(szText)      RX::ShowMessageBoxImplW(L##szText)
#else					         
#define MSGBOX(szText)      RX::ShowMessageBoxImplA(szText)
#endif

#define NULLCHK(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is nullptr!");\
}

#define NULLCHK_RETURN_NOCOMENT(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG_RETURN(#ptr " is nullptr!");\
}

#define NULL_RETURN(ptr)\
if (ptr == nullptr)\
{\
    return;\
}

#define NULL_OK_RETURN(ptr)\
if (ptr == nullptr)\
{\
    return S_OK;\
}

#define NULLCHK_RETURN(ptr, szErr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is nullptr!");\
	RXERRLOG_RETURN(szErr);\
}

#define NULLCHK_EFAIL_RETURN(ptr, szErr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is nullptr!");\
	RXERRLOG_EFAIL_RETURN(szErr);\
}

#define NULLCHK_HEAPALLOC(ptr)\
if (ptr == nullptr)\
{\
    RXERRLOG(#ptr " is failed in heap allocation!");\
}

#define RXERRLOG_RETURN(szErr)       RXERRLOG(szErr); return
#define RXERRLOG_EFAIL_RETURN(szErr) RXERRLOG(szErr); return E_FAIL

// ====================================================================================
// ��Ʈ�� ���� ��ũ���Դϴ�.
//
// ����� ��常 �۵�, ������ ���� X
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXDEBUGLOG(szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::PM_DEBUG, false, false, false,\
			nullptr, __LINE__, __TFUNSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXDEBUGLOG(szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::PM_DEBUG, false, false, false,\
			nullptr, __LINE__, __TFUNSIG__, szFormat, __VA_ARGS__)
	#endif
#else
	#define RXDEBUGLOG __noop
#endif

// ���� ���ڿ� ����, ����� ��忡���� ����� ���â���� ���
// �޽��� �ڽ� ��� ����, �Ϲ� �޽��� �ڽ��� �����մϴ�.
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXLOG(bMessageBox, szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::PM_DEBUG, bMessageBox, true, false,\
			__TFILE__, __LINE__, __TFUNSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXLOG(bMessageBox, szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::PM_DEBUG, bMessageBox, true, false,\
			__TFILE__, __LINE__, __TFUNSIG__, szFormat, __VA_ARGS__)
	#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXLOG(bMessageBox, szFormat, ...)\
		RX::RXLogImplW(PROJECT_MODE::PM_RELEASE, bMessageBox, true, false,\
			__TFILE__, __LINE__, __TFUNSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXLOG(bMessageBox, szFormat, ...)\
		RX::RXLogImplA(PROJECT_MODE::PM_RELEASE, bMessageBox, true, false,\
			__TFILE__, __LINE__, __TFUNSIG__, szFormat, __VA_ARGS__)
	#endif
#endif

// ���� ���ڿ� ����, ����� ��忡���� ����� ���â���� ���
// �޽��� �ڽ� ��� ����, ���� �޽��� �ڽ��� �����մϴ�.
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXERRLOG(szFormat, ...) RX::RXLogImplW(PROJECT_MODE::PM_DEBUG, true, true, true,\
		__TFILE__, __LINE__, __TFUNSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXERRLOG(szFormat, ...) RX::RXLogImplA(PROJECT_MODE::PM_DEBUG, true, true, true,\
		__TFILE__, __LINE__, __TFUNSIG__, szFormat, __VA_ARGS__)
	#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define RXERRLOG(szFormat, ...) RX::RXLogImplW(PROJECT_MODE::PM_RELEASE, true, true, true,\
		__TFILE__, __LINE__, __TFUNSIG__, L##szFormat, __VA_ARGS__)
	#else
	#define RXERRLOG(szFormat, ...) RX::RXLogImplA(PROJECT_MODE::PM_RELEASE, true, true, true,\
		__TFILE__, __LINE__, __TFUNSIG__, szFormat, __VA_ARGS__)
	#endif
#endif

// ====================================================================================
// DirectX ���� ��ũ���Դϴ�.
//
#define DXCOLOR_WHITE   D3DCOLOR_ARGB(255, 255, 255, 255)
#define DXCOLOR_BLACK   D3DCOLOR_ARGB(255,   0,   0,   0)
#define DXCOLOR_RED     D3DCOLOR_ARGB(255, 255,   0,   0)
#define DXCOLOR_GREEN   D3DCOLOR_ARGB(255,   0, 255,   0)
#define DXCOLOR_BLUE    D3DCOLOR_ARGB(255,   0,   0, 255)
#define DXCOLOR_MAGENTA D3DCOLOR_ARGB(255, 255,   0, 255)

// DirectX ���� �ڵ鷯 ��ũ���Դϴ�.
// HRESULT���� �־�� ���� �۵��մϴ�.
#define DXERR_HANDLER(hDXResult)\
if (FAILED(hDXResult))\
{\
	DXERR_HANDLER_IMPL(hDXResult);\
}

// ����, ����, ���� �̸�, ���� ����
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define DXERR_HANDLER_IMPL(hDXResult) RX::DXErrorHandlerImplW(hDXResult, PROJECT_MODE::PM_DEBUG,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#else
	#define DXERR_HANDLER_IMPL(hDXResult) RX::DXErrorHandlerImplA(hDXResult, PROJECT_MODE::PM_DEBUG,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define DXERR_HANDLER_IMPL(hDXResult) RX::DXErrorHandlerImplW(hDXResult, PROJECT_MODE::PM_RELEASE,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#else
	#define DXERR_HANDLER_IMPL(hDXResult) RX::DXErrorHandlerImplA(hDXResult, PROJECT_MODE::PM_RELEASE,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#endif
#endif

// ====================================================================================
// �� ���� ��ũ���Դϴ�.
//
#if defined(_UNICODE) || defined(UNICODE)
#define Win32LastErrorHandler Win32LastErrorHandlerImplW()
#else
#define Win32LastErrorHandler Win32LastErrorHandlerImplA()
#endif

// ����, ����, ���� �̸�, ���� ����
// GetLastError()�� �̿��� Win32 API�� ���� �ڵ鷯�Դϴ�.
#if defined(DEBUG) || defined(_DEBUG)
	#if defined(_UNICODE) || defined(UNICODE)
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplW(PROJECT_MODE::PM_DEBUG,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#else
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplW(PROJECT_MODE::PM_DEBUG,\
				__TFILE__, __LINE__, __TFUNSIG__);
#endif
#else
	#if defined(_UNICODE) || defined(UNICODE)
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplA(PROJECT_MODE::PM_RELEASE,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#else
	#define WIN32ERR_HANDLER() RX::Win32LastErrorHandlerImplA(PROJECT_MODE::PM_RELEASE,\
				__TFILE__, __LINE__, __TFUNSIG__);
	#endif
#endif

#endif