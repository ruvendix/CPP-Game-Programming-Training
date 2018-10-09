/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <작성 날짜>
 * 2018-08-07
 *
 * <파일 내용>
 * 공동으로 사용되는 전역 변수 모음입니다. 정의가 되어있습니다.
 * 따라서 각 프로젝트에서는 중복 정의가 발생하지 않도록 주의해야 합니다.
 * DLL과 관계 없는 전역 변수만 있습니다.
 *
 ====================================================================================*/
#ifndef GLOBAL_VARIABLE_DEFINITION_H__
#define GLOBAL_VARIABLE_DEFINITION_H__


// ====================================================================================
// 전체 프로젝트가 공유하는 전역 상수입니다.
extern HWND g_hMainWnd = nullptr;
extern HDC  g_hMainDC  = nullptr;

extern HDC     g_hBackBufferDC        = nullptr;
extern HBITMAP g_hBackBufferBitmap    = nullptr;
extern HBITMAP g_hOldBackBufferBitmap = nullptr;

// ====================================================================================
// 각 프로젝트별로 사용하는 전역 상수입니다.
//
// 001 프로젝트입니다.
extern HBRUSH g_hHighlightBrush = nullptr;


#endif