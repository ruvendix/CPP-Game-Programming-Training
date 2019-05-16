// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#ifndef LOG_BASE_H
#define LOG_BASE_H

#include <string>

/*
	�𸮾� ������ �α� �ý����� �����ϰ� �����ý��ϴ�.
*/

// �α��� Ÿ���Դϴ�.
enum class ELogType : int
{
	DEFAULT = 0,
	SHOW_MESSAGEBOX,
	WRITE_FILE,
	MAX,
};

// ������ �α׸� ����� ������ �Լ��Դϴ�.
void MyLog(const std::string& szCategory, ELogType logType);

// �α��� �⺻ Ŭ�����Դϴ�.
// ������ �α� Ŭ������ LogBase�� ��ӹް� �˴ϴ�.
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

// LogBase�� ��� �޴� ���ο� �α� Ŭ������ �����մϴ�.
#define DECLARE_MY_LOG(CategoryName)\
	class MyLog##CategoryName : public LogBase\
	{\
	public:\
		MyLog##CategoryName() : LogBase(#CategoryName) { }\
	};\
	\
	extern MyLog##CategoryName CategoryName;

// DECLARE_MY_LOG()���� ������ Ŭ������ ��ü�� ����ϴ�.
#define DEFINE_MY_LOG(CategoryName) MyLog##CategoryName CategoryName;

// DEFINE_MY_LOG()���� ���� ��ü�� �̿��ؼ� �α׸� ����մϴ�.
#define MY_LOG(CategoryName, logType) MyLog(CategoryName.getCategoryName(), ELogType::logType)

#endif