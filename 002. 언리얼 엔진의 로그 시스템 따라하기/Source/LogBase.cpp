// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "LogBase.h"

void MyLog(const std::string& szCategory, ELogType logType)
{
	switch (logType)
	{
	case ELogType::DEFAULT:
	{
		printf("%s : �𸮾� ����4 �α� �����ϱ��Դϴ�! (�⺻ �α�)\n", szCategory.c_str());
		break;
	}
	case ELogType::SHOW_MESSAGEBOX:
	{
		printf("%s : �𸮾� ����4 �α� �����ϱ��Դϴ�! (�޽��� �ڽ�)\n", szCategory.c_str());
		break;
	}
	case ELogType::WRITE_FILE:
	{
		printf("%s : �𸮾� ����4 �α� �����ϱ��Դϴ�! (���Ͽ� ���)\n", szCategory.c_str());
		break;
	}
	}
}