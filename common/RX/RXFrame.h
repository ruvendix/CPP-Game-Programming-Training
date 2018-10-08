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
#ifndef RXFRAME_H_
#define RXFRAME_H_

#include "../common.h"
#include "RXTime.h"

namespace RX
{

	class DLL_DEFINE RXFrame
	{
	public:
		RXFrame();
		virtual ~RXFrame();

		void InitFrame();
		void UpdateFrame();

		// getter
		DWORD getFPS() const
		{
			return m_FPS;
		}

	private:
		// ====================================================================================
		// �⺻ ����
		INT32     m_frameCount;
		INT32     m_framePerSecond;
		DWORD     m_FPS;
		RXTime    m_frameTime;
	};

} // namespace RX end

#endif