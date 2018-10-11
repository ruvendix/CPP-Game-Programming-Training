/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-06
 *
 * <���� ����>
 * �������� ���Ǵ� �ּ����� ���븸 ���ԵǾ��ֽ��ϴ�.
 * ��, �������� ���� ���� ��� ���ϵ鸸 ���ԵǾ��ֽ��ϴ�.
 *
 ====================================================================================*/
#ifndef BASE_H__
#define BASE_H__

#include <tchar.h>
#include <intrin.h> // __debugbreak()�� ����ϱ� ���� ��� �����Դϴ�.
#include <crtdbg.h> // ����� �޸� ������ ���� ��� ����

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <ctime>

#include <vector>

// SDKDDKVer.h�� �����ϸ� �ְ� ������ ���뼺�� ���� Windows �÷����� ���ǵ˴ϴ�.
// ���� Windows �÷����� ���� ���� ���α׷��� �����Ϸ��� ��쿡�� SDKDDKVer.h�� �����ϱ� ����
// WinSDKVer.h�� �����ϰ� _WIN32_WINNT ��ũ�θ� �����Ϸ��� �÷������� �����Ͻʽÿ�.
#include <SDKDDKVer.h>

// ���ʿ��� ������ �������� �ʱ� ���ؼ� ����մϴ�.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#ifdef RXBASEDX_EXPORTS
#define DLL_DEFINE __declspec(dllexport)
#else
#define DLL_DEFINE __declspec(dllimport)
#endif

#include "global_type.h"
#include "global_constant.h"

#endif