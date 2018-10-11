/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-12
 *
 * <���� ����>
 * �ð��� �ٷ�� Ŭ�����Դϴ�.
 *
 ====================================================================================*/
#ifndef RXTIME_H_
#define RXTIME_H_

#include "../common.h"

namespace RX
{

	class DLL_DEFINE RXTime
	{
	public:
		RXTime();
		~RXTime();

		void MeasureStartTime()
		{
			m_dwStartTime = ::timeGetTime();
		}

		void MeasureEndTime()
		{
			m_dwEndTime = ::timeGetTime();
		}

		DWORD CalcTimeInterval()
		{
			m_dwIntervalTime = m_dwEndTime - m_dwStartTime;
			return m_dwIntervalTime; // �и������� ����, 1000�� 1��
		}

		void SubstituteStartTimeWithEndTime()
		{
			m_dwStartTime = m_dwEndTime;
		}

		// ====================================================================================
		// Getter
		DWORD getStartTime() const noexcept
		{
			return m_dwStartTime;
		}

		DWORD getEndTime() const noexcept
		{
			return m_dwEndTime;
		}

		DWORD getIntervalTime() const noexcept
		{
			return m_dwIntervalTime;
		}

	private:
		// ====================================================================================
		// �⺻ ����
		DWORD    m_dwStartTime;
		DWORD    m_dwEndTime;
		DWORD    m_dwIntervalTime;
	};

} // namespace RX end

#endif