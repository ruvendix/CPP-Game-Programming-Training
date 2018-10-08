/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-06
 *
 * <���� ����>
 * ������Ʈ ���ο��� �������� ���Ǵ� ��� ���� �����Դϴ�.
 *
 ====================================================================================*/
#ifndef BASE_PROJECT_H__
#define BASE_PROJECT_H__

#include "common.h"

// ====================================================================================
// DirectX9�� ����ϱ� ���� ��� �����Դϴ�.
// ������Ʈ�� DirectX SDK�� ��ġ�� ��θ� ��������� �մϴ�.
#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

// ====================================================================================
// main ��ƾ�� ����ϱ� ���� ��� �����Դϴ�.
#include "RX/RXMain_DX9.h"

#include "resource.h"

// ====================================================================================
// <���̺귯�� ������Դϴ�.>
//
// Win32 API�� Lib �����Դϴ�.
#pragma comment(lib, "winmm.lib")
//
// DirectX9 ���̺귯�� �����Դϴ�
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "DxErr.lib")
//
// Window Kit�� ������ ���Ƽ� ��ũ���� �ʴ� �Լ�����
// ��ũ�����ֱ� ���� ����մϴ�. ���� ��� "DxErr.h"�� �ֽ��ϴ�.
#pragma comment(lib, "legacy_stdio_definitions.lib")
//
// RX ���̺귯�� �����Դϴ�.
#pragma comment(lib, "RXBaseDX_Debug.lib")

#endif