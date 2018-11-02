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

namespace RX
{

	class DLL_DEFINE RXVertexBufferDX9
	{
	public:
		RXVertexBufferDX9();
		virtual ~RXVertexBufferDX9();

		void    InsertVertex(FLOAT rX, FLOAT rY, FLOAT rZ, DWORD dwColor);
		void    InsertVertex(const D3DXVECTOR3& vPos, DWORD dwColor);
		HRESULT CreateVertexBuffer();

		// ====================================================================================
		// Getter
		INT32 getVertexCount() const noexcept
		{
			return m_vertexCnt;
		}

		IDirect3DVertexBuffer9* getVB() const noexcept
		{
			return m_pVB;
		}

	private:
		INT32                   m_vertexCnt; // ���� �����Դϴ�. �ӵ��� ���� �̸� �����صӴϴ�.
		std::vector<VertexInfo> m_vecVertex; // ���� �����Դϴ�.
		IDirect3DVertexBuffer9* m_pVB;       // DX9 ���� �����Դϴ�.
	};

} // namespace RX end
#endif