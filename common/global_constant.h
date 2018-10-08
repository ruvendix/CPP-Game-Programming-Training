/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-07
 *
 * <���� ����>
 * �������� ���Ǵ� ���� ��� �����Դϴ�.
 * �̸� �����ϵ� ��� ���Ͽ� �ۼ��Ǵ� ��� �����Դϴ�.
 *
 ====================================================================================*/
#ifndef GLOBAL_CONSTANT_H__
#define GLOBAL_CONSTANT_H__

const INT32 DEFAULT_CLIENT_WIDTH  = 1024;
const INT32 DEFAULT_CLIENT_HEIGHT = 768;

const INT32 DEFAULT_STRING_LENGTH = 512;
const INT32 MAX_STRING_LENGTH     = 1024;
const INT32 MAX_FILE_NAME         = 256;

const INT32 D3DUSAGE_NONE = 0;

// ������ ī��Ʈ���� ���ǰ�
// ���� �������� �ð����� �����Ǳ� ������
// ���� ���������� �۵��մϴ�.
//const INT32 FRAME_COUNT_THIRTY = 30;
//const INT32 FRAME_COUNT_SIXTY  = 60;

const INT32 UPDATE_FRAME_PER_SECOND = 25; // �������� ������ ���� ���� ���� FPS
const INT32 FRAME_SKIP_TIME         = 1000 / UPDATE_FRAME_PER_SECOND;
const INT32 MAX_FRAMESKIP           = 10;

// ���ڿ��� �̸� �����ϵ� ��� ���Ͽ��� �ߺ� ���Ƿ� �ν��ϹǷ�
// ǥ�� ���̺귯���� ���� ���ڿ��� ��ũ�� ����� �����մϴ�.
#define SZ_WINDOW_CLASS     _T("Default_3D_Program")
#define SZ_PROGRAM_TITLE    _T("Default_3D_Program")
#define SZ_NONE             _T("None")

#endif