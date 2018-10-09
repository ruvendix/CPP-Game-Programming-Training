/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-07
 *
 * <���� ����>
 * �������� ���Ǵ� ���� ���� �����Դϴ�. ���ǰ� �Ǿ��ֽ��ϴ�.
 * ���� �� ������Ʈ������ �ߺ� ���ǰ� �߻����� �ʵ��� �����ؾ� �մϴ�.
 * DLL�� ���� ���� ���� ������ �ֽ��ϴ�.
 *
 ====================================================================================*/
#ifndef GLOBAL_VARIABLE_DEFINITION_H__
#define GLOBAL_VARIABLE_DEFINITION_H__


// ====================================================================================
// ��ü ������Ʈ�� �����ϴ� ���� ����Դϴ�.
extern HWND g_hMainWnd = nullptr;
extern HDC  g_hMainDC  = nullptr;

extern HDC     g_hBackBufferDC        = nullptr;
extern HBITMAP g_hBackBufferBitmap    = nullptr;
extern HBITMAP g_hOldBackBufferBitmap = nullptr;

// ====================================================================================
// �� ������Ʈ���� ����ϴ� ���� ����Դϴ�.
//
// 001 ������Ʈ�Դϴ�.
extern HBRUSH g_hHighlightBrush = nullptr;


#endif