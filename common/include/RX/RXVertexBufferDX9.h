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
struct VertexInfo
{
	D3DXVECTOR3 vPos;    // ������ ��ǥ�Դϴ�.
	DWORD       dwColor; // ������ �����Դϴ�.
	static const DWORD FORMAT = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

// �ε����� ������ �����մϴ�.
struct IndexInfo
{
	WORD triangleIndices[3];
	static const D3DFORMAT FORMAT = D3DFMT_INDEX16; // �ε��� ������ 2����Ʈ�Դϴ�.
};

namespace RX
{

	class DLL_DEFINE RXVertexBufferDX9
	{
	public:
		RXVertexBufferDX9();
		virtual ~RXVertexBufferDX9();

		void    InsertVertex(FLOAT rX, FLOAT rY, FLOAT rZ, DWORD dwColor);
		void    InsertVertex(const D3DXVECTOR3& vPos, DWORD dwColor);
		void    InsertIndex(WORD first, WORD second, WORD third);
		void    DrawPrimitive(D3DPRIMITIVETYPE primitiveType);
		void    DrawIndexedPrimitive(); // D3DPT_TRIANGLELIST �����Դϴ�.

		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer(INT32 triangleCnt);

		// ====================================================================================
		// Getter
		INT32 getVertexCount() const noexcept
		{
			return (m_vecVertex.size());
		}

		// ====================================================================================
		// Setter

	private:
		INT32                      m_vertexCnt;
		INT32                      m_triangleCnt;
		std::vector<VertexInfo>    m_vecVertex;
		std::vector<IndexInfo>     m_vecIndex;
		IDirect3DVertexBuffer9*    m_pVB;
		IDirect3DIndexBuffer9*     m_pIB;
	};

} // namespace RX end
#endif