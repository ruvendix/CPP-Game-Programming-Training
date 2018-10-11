/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-12
 *
 * <���� ����>
 * �������� �ٷ�� Ŭ�����Դϴ�.
 * ����� ���� �����ӿ����� ���ǰ� �ֽ��ϴ�.
 *
 ====================================================================================*/
#include "PCH.h"
#include "RXFrame.h"

namespace RX
{

	RXFrame::RXFrame()
	{
		m_frameCount = 0;
		m_FPS        = 0;
	}

	RXFrame::~RXFrame()
	{

	}

	void RXFrame::InitFrame()
	{
		m_frameTime.SubstituteStartTimeWithEndTime();
		m_frameCount = 0;
	}

	void RXFrame::UpdateFrame()
	{
		// ������ ī��Ʈ�� 0�� ���� ���� �ð��� �����մϴ�.
		if (m_frameCount == 0)
		{
			m_frameTime.MeasureStartTime();
		}

		m_frameTime.MeasureEndTime();
		++m_frameCount;

		// 1�ʰ� �Ѿ�� ������ üũ
		if (m_frameTime.CalcTimeInterval() >= CLOCKS_PER_SEC)
		{
			// FPS = ������ ī��Ʈ / 1��
			m_FPS = m_frameCount * CLOCKS_PER_SEC / m_frameTime.getIntervalTime();
			//RXDEBUGLOG("���� ������ ī��Ʈ %d, FPS : %d", m_frameCount, m_FPS);
			InitFrame();
		}
	}

} // namespace RX end