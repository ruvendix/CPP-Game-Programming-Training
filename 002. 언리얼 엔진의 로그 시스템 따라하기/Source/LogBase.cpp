// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "LogBase.h"

void MyLog(const std::string& szCategory, ELogType logType)
{
	switch (logType)
	{
	case ELogType::DEFAULT:
	{
		printf("%s : 언리얼 엔진4 로그 따라하기입니다! (기본 로그)\n", szCategory.c_str());
		break;
	}
	case ELogType::SHOW_MESSAGEBOX:
	{
		printf("%s : 언리얼 엔진4 로그 따라하기입니다! (메시지 박스)\n", szCategory.c_str());
		break;
	}
	case ELogType::WRITE_FILE:
	{
		printf("%s : 언리얼 엔진4 로그 따라하기입니다! (파일에 기록)\n", szCategory.c_str());
		break;
	}
	}
}