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
#ifndef RXTIMER_H_
#define RXTIMER_H_

#include "../common.h"

namespace RX
{

	class DLL_DEFINE RXTimer
	{
	public:
		RXTimer();
		~RXTimer();

		FLOAT CalcDeltaSecond();
		FLOAT CalcFixedDeltaSecondByFPS(FPS_TYPE type);
		FLOAT CalcHigResoultionDeltaSecond();

		// ====================================================================================
		// Getter
		FLOAT getDeltaSecond() const noexcept
		{
			return m_rDeltaSecond;
		}

	private:
		bool  m_bInit;              // Ÿ�̸� ù �۵� �����Դϴ�.
		FLOAT m_rDeltaSecond;       // ������ ���� �ð� �����Դϴ�. ������ ���Դϴ�.
		DWORD m_dwPrevFrameTime;    // ���� ������ �ð��Դϴ�.
		DWORD m_dwCurrentFrameTime; // ���� ������ �ð��Դϴ�.

		// ���ػ� Ÿ�̸��Դϴ�. LARGE_INTEGER�� 8����Ʈ �ڷ����Դϴ�.
		// ���ػ� Ÿ�̸��� ���ļ�(�ʴ� ������)�� CPU�� Ŭ������ �̿��մϴ�.
		LARGE_INTEGER m_highPrevTime;    // ���� �����ӿ��� CPU�� Ŭ����
		LARGE_INTEGER m_highCurrentTime; // ���� �����ӿ��� CPU�� Ŭ����
		LARGE_INTEGER m_highFrequency;   // CPU�� ���ļ�
	};

} // namespace RX end

#endif