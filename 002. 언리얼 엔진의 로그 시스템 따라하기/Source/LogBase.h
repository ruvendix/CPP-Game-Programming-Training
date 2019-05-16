// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#ifndef LOG_BASE_H
#define LOG_BASE_H

#include <string>

/*
	언리얼 엔진의 로그 시스템을 간단하게 만들어봤습니다.
*/

// 로그의 타입입니다.
enum class ELogType : int
{
	DEFAULT = 0,
	SHOW_MESSAGEBOX,
	WRITE_FILE,
	MAX,
};

// 실제로 로그를 출력이 구현된 함수입니다.
void MyLog(const std::string& szCategory, ELogType logType);

// 로그의 기본 클래스입니다.
// 실제로 로그 클래스는 LogBase를 상속받게 됩니다.
class LogBase
{
public:
	LogBase(const std::string& szCategoryName)
	{
		setCategoryName(szCategoryName);
	}

	std::string getCategoryName() const noexcept
	{
		return m_szCategory;
	}

	void setCategoryName(const std::string& szCategory)
	{
		m_szCategory = szCategory;
	}

private:
	std::string m_szCategory;
};

// LogBase를 상속 받는 새로운 로그 클래스를 선언합니다.
#define DECLARE_MY_LOG(CategoryName)\
	class MyLog##CategoryName : public LogBase\
	{\
	public:\
		MyLog##CategoryName() : LogBase(#CategoryName) { }\
	};\
	\
	extern MyLog##CategoryName CategoryName;

// DECLARE_MY_LOG()에서 선언한 클래스를 객체로 만듭니다.
#define DEFINE_MY_LOG(CategoryName) MyLog##CategoryName CategoryName;

// DEFINE_MY_LOG()에서 만든 객체를 이용해서 로그를 출력합니다.
#define MY_LOG(CategoryName, logType) MyLog(CategoryName.getCategoryName(), ELogType::logType)

#endif