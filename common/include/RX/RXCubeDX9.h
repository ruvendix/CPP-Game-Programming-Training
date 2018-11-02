/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-14
 *
 * <���� ����>
 * �׽�Ʈ�� ť�긦 �ٷ�ϴ�.
 *
 ====================================================================================*/
#ifndef RXCUBEDX9_H__
#define RXCUBEDX9_H__

#include "common.h"
#include "RXRenderObjectDX9.h"

namespace RX
{

	class DLL_DEFINE RXCubeDX9 : public RXRenderObjectDX9
	{
	public:
		RXCubeDX9() = default;
		virtual ~RXCubeDX9() = default;

		HRESULT CreateCubeByVertex(const D3DXVECTOR3& vMin, const D3DXVECTOR3& vMax);
		HRESULT CreateCubeByIndex(const D3DXVECTOR3& vMin, const D3DXVECTOR3& vMax);
		void    InitBaseVertex(const D3DXVECTOR3& vMin, const D3DXVECTOR3& vMax);
		void    DrawCubeByVertex();
		void    DrawCubeByIndex();

	private:
		D3DXVECTOR3 m_vBase[8]; // ������ �Ǵ� ����
	};

} // namespace RX end
#endif