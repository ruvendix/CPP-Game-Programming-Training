// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "ConsoleLog.h"

int main()
{
	MY_LOG(ConsoleLog, SHOW_MESSAGEBOX);
	MY_LOG(ConsoleLog, DEFAULT);
	MY_LOG(ConsoleLog, WRITE_FILE);
	return 0;
}