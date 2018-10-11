/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-11
 *
 * <���� ����>
 * DirectX9�� ���� ���۸� Ŭ������ �����߽��ϴ�.
 *
 ====================================================================================*/
#ifndef RXVERTEXBUFFERDX9_H__
#define RXVERTEXBUFFERDX9_H__

#include "common.h"

// ������ ������ �����մϴ�.
struct CustomVertex
{
	D3DXVECTOR3 vPos;    // ������ ��ǥ�Դϴ�.
	DWORD       dwColor; // ������ �����Դϴ�.
};

namespace RX
{

	class DLL_DEFINE RXVertexBufferDX9
	{
	public:
		RXVertexBufferDX9();
		virtual ~RXVertexBufferDX9();

		void    InsertVertex(FLOAT rX, FLOAT rY, FLOAT rZ, DWORD dwColor);
		void    DrawPrimitive(D3DPRIMITIVETYPE primitiveType);
		HRESULT CreateVertexBuffer();

		// ====================================================================================
		// Getter
		INT32 getVertexCount() const noexcept
		{
			return (m_vecVertex.size());
		}

		// ====================================================================================
		// Setter
		void setFVF(DWORD fvf)
		{
			m_dwFVF = fvf;
		}

	private:
		DWORD                        m_dwFVF;
		std::vector<CustomVertex>    m_vecVertex;
		IDirect3DVertexBuffer9*      m_pVertexBuffer;
	};

} // namespace RX end
#endif