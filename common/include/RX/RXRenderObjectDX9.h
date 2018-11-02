/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-15
 *
 * <���� ����>
 * �������Ǵ� ������Ʈ�� �⺻ Ŭ�����Դϴ�.
 *
 ====================================================================================*/
#ifndef RXRENDEROBJECTDX9_H__
#define RXRENDEROBJECTDX9_H__

#include "common.h"
#include "RXVertexBufferDX9.h"

namespace RX
{

	class DLL_DEFINE RXRenderObjectDX9
	{
	public:
		RXRenderObjectDX9();
		virtual ~RXRenderObjectDX9();

		void AllocVertexBuffer();
		void AllocIndexBuffer();
		void CreateVertexBuffer();
		void CreateIndexBuffer(INT32 triangleCnt);
		void InsertVertex(FLOAT rX, FLOAT rY, FLOAT rZ, DWORD dwColor);
		void InsertVertex(const D3DXVECTOR3& vPos, DWORD dwColor);
		void InsertIndex(WORD first, WORD second, WORD third);

		HRESULT DrawPrimitive();
		HRESULT DrawIdxedPrimitive();

		// ====================================================================================
		// Setter
		void setPrimitiveType(D3DPRIMITIVETYPE primitiveType)
		{
			m_primitiveType = primitiveType;
		}

	private:
		RX::RXVertexBufferDX9* m_pVB;           // ���� �����Դϴ�.
		RX::RXIndexBufferDX9*  m_pIB;           // �ε��� �����Դϴ�.
		D3DPRIMITIVETYPE       m_primitiveType; // ������ ����Դϴ�.
	};

} // namespace RX end
#endif