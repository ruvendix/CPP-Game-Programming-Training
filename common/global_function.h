/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-11
 *
 * <���� ����>
 * �������� ���Ǵ� ���� �Լ� �����Դϴ�.
 * �Լ� ����θ� ������, �����δ� �� ������Ʈ�� ���Խ��Ѿ� �մϴ�.
 * ��ũ�ο� ������ ���� �ʽ��ϴ�.
 * DLL�� ����Ǿ����Ƿ� DLL ����ο� �����η� �������ϴ�.
 * ����� ������Ʈ�� ���� ������ ��ġ�� �� �˴ϴ�. ��ġ�� ���� �۵��� ������� �ʽ��ϴ�.
 *
 ====================================================================================*/
#ifndef GLOBAL_FUNCTION_H__
#define GLOBAL_FUNCTION_H__

#include "base.h"

namespace RX
{

	// �����ڵ� �����Դϴ�.
	DLL_DEFINE void RXDebugLogImplW(const WCHAR* szText);
	DLL_DEFINE void RXLogImplW(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const WCHAR* szFile, INT32 line, const WCHAR* szFunSig, const WCHAR* szFormat, ...);
	DLL_DEFINE void ShowMessageBoxImplW(const WCHAR* szText);
	DLL_DEFINE void ShowErrorMessageBoxImplW(const WCHAR* szErr, const WCHAR* szFileName, INT32 line);
	DLL_DEFINE void DXErrorHandlerImplW(HRESULT DXError, PROJECT_MODE eMode, const WCHAR* szFileName,
		INT32 line, const WCHAR* szFunSig);
	DLL_DEFINE void Win32LastErrorHandlerImplW(PROJECT_MODE eMode, const WCHAR* szFileName,
		INT32 line, const WCHAR* szFunSig);

	// ��Ƽ����Ʈ �����Դϴ�.
	DLL_DEFINE void RXDebugLogImplA(const CHAR* szText);
	DLL_DEFINE void RXLogImplA(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const CHAR* szFile, INT32 line, const CHAR* szFunSig, const CHAR* szFormat, ...);
	DLL_DEFINE void ShowMessageBoxImplA(const CHAR* szText);
	DLL_DEFINE void ShowErrorMessageBoxImplA(const CHAR* szErr, const CHAR* szFileName, INT32 line);
	DLL_DEFINE void DXErrorHandlerImplA(HRESULT DXError, PROJECT_MODE eMode, const CHAR* szFileName,
		INT32 line, const CHAR* szFunSig);
	DLL_DEFINE void Win32LastErrorHandlerImplA(PROJECT_MODE eMode, const CHAR* szFileName,
		INT32 line, const CHAR* szFunSig);

	DLL_DEFINE void DrawLineWin32(HDC hDC, INT32 startX, INT32 startY, INT32 endX, INT32 endY);

} // namespace RX end

#endif