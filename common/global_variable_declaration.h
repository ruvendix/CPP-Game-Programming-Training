/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-07
 *
 * <���� ����>
 * �������� ���Ǵ� ���� ���� �����Դϴ�. ���� �Ǿ��ֽ��ϴ�.
 * ������ �� ������Ʈ������ �� ��� ������ �����ؾ� �մϴ�.
 *
 ====================================================================================*/
#ifndef GLOBAL_VARIABLE_DECLARATION_H__
#define GLOBAL_VARIABLE_DECLARATION_H__

extern HWND g_hMainWnd;
extern HDC  g_hMainDC;

extern HBRUSH  g_hHighlightBrush;
extern HDC     g_hBackBufferDC;
extern HBITMAP g_hBackBufferBitmap;
extern HBITMAP g_hOldBackBufferBitmap;

extern IDirect3DDevice9* g_pD3DDevice9;
extern HRESULT           g_DXResult;

#endif