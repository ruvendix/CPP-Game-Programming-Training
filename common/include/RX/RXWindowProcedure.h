/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-21
 *
 * <���� ����>
 * ������ ���ν���(�޽��� ���ν���)���� ���ǵǾ��ֽ��ϴ�.
 *
 ====================================================================================*/
#ifndef RXWINDOWPROCEDURE_H_
#define RXWINDOWPROCEDURE_H_

#include "common.h"

ROUTINE_RETURN_TYPE BaseWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DefaultWndProcDX9(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ���� �޽��� �ڵ鷯�Դϴ�.
void OnCreate();
void OnClose();
void OnDestroy();
void OnKeyEscape();
void OnMouseLButtonDown(LPARAM lParam);
void OnMouseRButtonDown(LPARAM lParam);
void OnMouseMove();
void OnGetMinMaxInfo(LPARAM lParam);
void OnNoneClientHitTest();
void OnEraseBackGround();

// ������ ���� �޽��� �ڵ鷯�Դϴ�.
void OnMaximize();
void OnAltEnter(WPARAM wParam, LPARAM lParam);

// DirectX9 ���� �޽��� �ڵ鷯�Դϴ�.
void OnKeyF12DX9(); // ��ũ������ ����ϴ�.
void OnMaximizeDX9();
void OnAltEnterDX9(WPARAM wParam, LPARAM lParam);

#endif