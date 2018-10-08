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
 * ��ũ�� ������ ���ԵǹǷ� ��ũ�ο� ������ ���� �ʽ��ϴ�.
 * DLL�� ����Ǿ����Ƿ� DLL ����ο� �����η� �������ϴ�.
 *
 ====================================================================================*/
#include "stdafx.h"
#include "global_function.h"

// ���� �Լ������� ���Ǹ� ���� �����Դϴ�.
// ����� DLL�� ����ϴ� ������Ʈ�� ���� ���� ������ ��ġ�� �� �˴ϴ�.
namespace
{
	CHAR g_szLogFile[DEFAULT_STRING_LENGTH];
}

namespace RX
{

	// ����� ��忡���� Ȯ�� ������ �α��Դϴ�.
	// �α״� ����� ���â���� Ȯ���� �� �ֽ��ϴ�.
	DLL_DEFINE void RXDebugLogImplA(const CHAR* szText)
	{
		::OutputDebugStringA(szText);
	}

	DLL_DEFINE void RXDebugLogImplW(const WCHAR* szText)
	{
		::OutputDebugStringW(szText);
	}

	// ��Ģ�����δ� �����, ����� ������� ���� �Ǵ� ������ �α׸� ���ܾ� �մϴ�.
	// ���� ���ڿ��� �����ϸ� "����(����) <�Լ�> : ����" �̷� �������� �αװ� ��µ˴ϴ�.
	// ����� ����� ����� ���� ����� ���â���� �α׸� ����ϴ�.
	// ��� ������ �α��� ���̴� ��Ƽ����Ʈ �������� ���� 512���Դϴ�.
	// �տ� �⺻ ���ڿ��� �߰��ǹǷ� �� ��� ������ �α��� ���̴� 512 + 512 = 1024�Դϴ�.
	// �޽��� �ڽ� ��� ��ɵ� �ִµ� �Ϲ� �޽��� �ڽ��� ���� �޽��� �ڽ��� �����մϴ�.
	DLL_DEFINE void RXLogImplA(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const CHAR* szFile, INT32 line, const CHAR* szFunSig, const CHAR* szFormat, ...)
	{
		CHAR szFull[MAX_STRING_LENGTH];
		_snprintf_s(szFull, _countof(szFull), "%s(%d) <%s> : ", szFile, line, szFunSig);

		CHAR szText[DEFAULT_STRING_LENGTH];
		va_list vaList;
		va_start(vaList, szFormat);
		_vsnprintf_s(szText, _countof(szText), szFormat, vaList);
		va_end(vaList);

		strcat_s(szFull, szText);
		strcat_s(szFull, "\n");

		if (eMode == PROJECT_MODE::PM_DEBUG)
		{
			RXDebugLogImplA(szFull);
		}

		if (bMessageBox)
		{
			if (bError)
			{
				ShowErrorMessageBoxImplA(szText, szFile, line);
			}
			else
			{
				ShowMessageBoxImplA(szText);
			}
		}

		// �����̳� ������ �α׸� ����� ��ƾ�� ���� �˴ϴ�.
		if ( (bFile == true) &&
			 (strlen(g_szLogFile) <= 0) )
		{
			// �ý��� �ð��� �̿��ؼ� ���� �ð��� ���մϴ�.
			SYSTEMTIME sysTime;
			::ZeroMemory(&sysTime, sizeof(sysTime));
			WCHAR szCurTime[DEFAULT_STRING_LENGTH];
			::GetLocalTime(&sysTime);
			_snwprintf_s(szCurTime, _countof(szCurTime),
				L"%02d-%02d-%02d-%02d-%02d-%02d",
				sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,
				sysTime.wMinute, sysTime.wSecond);

			// ���� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲ� �ʿ�� ������
			// �ð� ���ڿ��� �����ڵ��̹Ƿ� ��� �Լ��� �����ڵ� �������� �ٲ�� �մϴ�.
			// ������ �ð� ���ڿ��� ��Ƽ����Ʈ�� ��ȯ�ϸ� ��Ƽ����Ʈ �Լ��� �����ϸ� �˴ϴ�.
			CHAR szTemp[DEFAULT_STRING_LENGTH];
			::WideCharToMultiByte(CP_ACP, 0, szCurTime, -1, szTemp, _countof(szTemp), nullptr, nullptr);

			::CreateDirectoryA("Log", nullptr);

#if defined(DEBUG) | defined(_DEBUG)
			_snprintf_s(g_szLogFile, _countof(g_szLogFile), "Log\\Debug_Program(%s).log", szTemp);
#else
			_snprintf_s(g_szLogFile, _countof(g_szLogFile), "Log\\Program(%s).log", szTemp);
#endif
		}

		// ���Ͽ� ������ ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
		// Win32 API�ε� ���� �ڵ�� ��Ʈ���� ���� �ݽ��ϴ�.
		// �� �� ���� ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
		FILE* pLog = nullptr;
		fopen_s(&pLog, g_szLogFile, "at");
		fprintf(pLog, szFull);
		fclose(pLog);

		if (bError)
		{
			// ����� ����� �� �ߴ����� �˴ϴ�.
			// ����Ű� ���� ���� ���α׷��� �ڵ� ����˴ϴ�.
			__debugbreak();
		}
	}

	DLL_DEFINE void RXLogImplW(PROJECT_MODE eMode, bool bMessageBox, bool bFile, bool bError,
		const WCHAR* szFile, INT32 line, const WCHAR* szFunSig, const WCHAR* szFormat, ...)
	{
		WCHAR szFull[MAX_STRING_LENGTH];
		::ZeroMemory(szFull, _countof(szFull));

		if (szFile != nullptr)
		{
			_snwprintf_s(szFull, _countof(szFull), L"%s(%d) <%s> : ", szFile, line, szFunSig);
		}

		WCHAR szText[DEFAULT_STRING_LENGTH];
		va_list vaList;
		va_start(vaList, szFormat);
		_vsnwprintf_s(szText, _countof(szText), szFormat, vaList);
		va_end(vaList);

		wcscat_s(szFull, szText);
		wcscat_s(szFull, L"\n");

		if (eMode == PROJECT_MODE::PM_DEBUG)
		{
			RXDebugLogImplW(szFull);
		}

		if (bMessageBox)
		{
			if (bError)
			{
				ShowErrorMessageBoxImplW(szText, szFile, line);
			}
			else
			{
				ShowMessageBoxImplW(szText);
			}
		}

		// �����̳� ������ �α׸� ����� ��ƾ�� ���� �˴ϴ�.
		if ( (bFile == true) &&
			 (strlen(g_szLogFile) <= 0) )
		{
			// �ý��� �ð��� �̿��ؼ� ���� �ð��� ���մϴ�.
			SYSTEMTIME sysTime;
			::ZeroMemory(&sysTime, sizeof(sysTime));
			WCHAR szCurTime[DEFAULT_STRING_LENGTH];
			::GetLocalTime(&sysTime);
			_snwprintf_s(szCurTime, _countof(szCurTime),
				L"%02d-%02d-%02d-%02d-%02d-%02d",
				sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,
				sysTime.wMinute, sysTime.wSecond);

			// ���� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲ� �ʿ�� ������
			// �ð� ���ڿ��� �����ڵ��̹Ƿ� ��� �Լ��� �����ڵ� �������� �ٲ�� �մϴ�.
			// ������ �ð� ���ڿ��� ��Ƽ����Ʈ�� ��ȯ�ϸ� ��Ƽ����Ʈ �Լ��� �����ϸ� �˴ϴ�.
			CHAR szTemp[DEFAULT_STRING_LENGTH];
			::WideCharToMultiByte(CP_ACP, 0, szCurTime, -1, szTemp, _countof(szTemp), nullptr, nullptr);

			::CreateDirectoryA("Log", nullptr);

#if defined(DEBUG) | defined(_DEBUG)
			_snprintf_s(g_szLogFile, _countof(g_szLogFile), "Log\\Debug_Program(%s).log", szTemp);
#else
			_snprintf_s(g_szLogFile, _countof(g_szLogFile), "Log\\Program(%s).log", szTemp);
#endif
		}

		// ���Ͽ� ������ ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
		// Win32 API�ε� ���� �ڵ�� ��Ʈ���� ���� �ݽ��ϴ�.
		// �� �� ���� ������ ���� ��Ʈ���� ���� �ݾƾ� �մϴ�.
		FILE* pLog = nullptr;
		fopen_s(&pLog, g_szLogFile, "at");
		fwprintf(pLog, szFull);
		fclose(pLog);

		if (bError)
		{
			// ����� ����� �� �ߴ����� �˴ϴ�.
			// ����Ű� ���� ���� ���α׷��� �ڵ� ����˴ϴ�.
			__debugbreak();
		}
	}

	// �޽��� �ڽ��� �����ִ� �Լ��Դϴ�.
	DLL_DEFINE void ShowMessageBoxImplA(const CHAR* szText)
	{
		::MessageBoxA(nullptr, szText, "Caption", MB_OK);
	}

	DLL_DEFINE void ShowMessageBoxImplW(const WCHAR* szText)
	{
		::MessageBoxW(nullptr, szText, L"Caption", MB_OK);
	}

	// �޽��� �ڽ��� ������ �����ִ� �Լ��Դϴ�.
	DLL_DEFINE void ShowErrorMessageBoxImplA(const CHAR* szErr, const CHAR* szFileName, INT32 line)
	{
		CHAR szText[DEFAULT_STRING_LENGTH];
		_snprintf_s(szText, _countof(szText), "%s\n%s(%d)", szErr, szFileName, line);
		::MessageBoxA(nullptr, szText, "Error", MB_ICONERROR);
	}

	DLL_DEFINE void ShowErrorMessageBoxImplW(const WCHAR* szErr, const WCHAR* szFileName, INT32 line)
	{
		WCHAR szText[DEFAULT_STRING_LENGTH];
		_snwprintf_s(szText, _countof(szText), L"%s\n%s(%d)", szErr, szFileName, line);
		::MessageBoxW(nullptr, szText, L"Error", MB_ICONERROR);
	}

	// ���� �ڵ鷯�Դϴ�. ���� �������Դϴ�.
	// "DxErr.h"�� �̿��ؼ� ������ �� �� �ڼ��� �����ݴϴ�.
	// HRESULT�� ��ȯ�ϴ� �Լ��� ���� ����� �� �ֽ��ϴ�.
	// ������ �߻��ϸ� "legacy_stdio_definitions.lib"�� �߰����ּ���.
	// �޽��� �ڽ� ��� ��ɵ� �ֽ��ϴ�.
	DLL_DEFINE void DXErrorHandlerImplA(HRESULT DXError, PROJECT_MODE eMode,
		const CHAR* szFileName, INT32 line, const CHAR* szFunSig)
	{
		const CHAR* szErrName = DXGetErrorStringA(DXError);
		const CHAR* szErrText = DXGetErrorDescriptionA(DXError);

		CHAR szErr[DEFAULT_STRING_LENGTH];
		_snprintf_s(szErr, _countof(szErr), "Error : %s\nText : %s", szErrName, szErrText);
		ShowErrorMessageBoxImplA(szErr, szFileName, line);

		// �α׷ε� ����մϴ�.
		RXLogImplA(eMode, false, true, true, szFileName, line, szFunSig,
			"Error(%s) Text(%s)", szErrName, szErrText);
	}

	DLL_DEFINE void DXErrorHandlerImplW(HRESULT DXError, PROJECT_MODE eMode,
		const WCHAR* szFileName, INT32 line, const WCHAR* szFunSig)
	{
		const WCHAR* szErrName = DXGetErrorStringW(DXError);
		const WCHAR* szErrText = DXGetErrorDescriptionW(DXError);

		WCHAR szErr[DEFAULT_STRING_LENGTH];
		_snwprintf_s(szErr, _countof(szErr), L"Error : %s\nText : %s", szErrName, szErrText);
		ShowErrorMessageBoxImplW(szErr, szFileName, line);

		// �α׷ε� ����մϴ�.
		RXLogImplW(eMode, false, true, true, szFileName, line, szFunSig,
			L"Error(%s) Text(%s)", szErrName, szErrText);
	}

	// ::GetLastError()�� �̿��� Win32 API ���� �ڵ鷯�Դϴ�.
	DLL_DEFINE void Win32LastErrorHandlerImplA(PROJECT_MODE eMode, const CHAR* szFileName,
		INT32 line, const CHAR* szFunSig)
	{
		DWORD errorCode = ::GetLastError();
		if (errorCode == 0)
		{
			return;
		}

		CHAR* szText = nullptr;
		::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), szText, 0, nullptr);

		CHAR szErr[DEFAULT_STRING_LENGTH];
		_snprintf_s(szErr, _countof(szErr), "Error : %0x\nText : %s", errorCode, szText);
		ShowErrorMessageBoxImplA(szErr, szFileName, line);

		RXLogImplA(eMode, false, true, true, szFileName, line, szFunSig,
			"Error(%0x) Text(%s)", errorCode, szText);

		LocalFree(szText);

		// ����� ����� �� �ߴ����� �˴ϴ�.
		// ����Ű� ���� ���� ���α׷��� �ڵ� ����˴ϴ�.
		__debugbreak();
	}

	DLL_DEFINE void Win32LastErrorHandlerImplW(PROJECT_MODE eMode, const WCHAR* szFileName,
		INT32 line, const WCHAR* szFunSig)
	{
		DWORD errorCode = ::GetLastError();
		if (errorCode == 0)
		{
			return;
		}

		WCHAR* szText = nullptr;
		::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), szText, 0, nullptr);

		WCHAR szErr[DEFAULT_STRING_LENGTH];
		_snwprintf_s(szErr, _countof(szErr), L"Error : %0x\nText : %s", errorCode, szText);
		ShowErrorMessageBoxImplW(szErr, szFileName, line);

		RXLogImplW(eMode, false, true, true, szFileName, line, szFunSig,
			L"Error(%0x) Text(%s)", errorCode, szText);

		LocalFree(szText);
	}

} // namespace RX end