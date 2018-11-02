/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-12
 *
 * <���� ����>
 * 3D �⺻ ���� �ٷ�ϴ�.
 *
 ====================================================================================*/
#ifndef RX3DAXISDX9_H__
#define RX3DAXISDX9_H__

#include "common.h"
#include "RXRenderObjectDX9.h"

namespace RX
{

	class DLL_DEFINE RX3DAxisDX9 : public RXRenderObjectDX9
	{
	public:
		RX3DAxisDX9() = default;
		virtual ~RX3DAxisDX9() = default;

		HRESULT CreateAxis(FLOAT rDist);
		void    DrawAxis();
	};

} // namespace RX end
#endif