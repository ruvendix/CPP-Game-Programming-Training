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
#include "PCH.h"
#include "RXVertexBufferDX9.h"

namespace
{
	INT32 CalcPrimitiveCount(D3DPRIMITIVETYPE primitiveType, INT32 vertexCnt)
	{
		INT32 primitiveCnt = 0;
		switch (primitiveType)
		{
		case D3DPT_POINTLIST:
			primitiveCnt = vertexCnt;
			break;
		case D3DPT_LINELIST:
			primitiveCnt = vertexCnt / 2;
			break;
		case D3DPT_LINESTRIP:
			primitiveCnt = vertexCnt - 1;
			break;
		case D3DPT_TRIANGLELIST:
			primitiveCnt = vertexCnt / 3;
			break;
		case D3DPT_TRIANGLESTRIP:
			primitiveCnt = vertexCnt - 2;
			break;
		case D3DPT_TRIANGLEFAN:
			primitiveCnt = vertexCnt - 2;
			break;
		}

		return primitiveCnt;
	}
}

namespace RX
{

	RXVertexBufferDX9::RXVertexBufferDX9()
	{
		m_dwFVF = 0;
		m_pVertexBuffer = nullptr;
	}

	RXVertexBufferDX9::~RXVertexBufferDX9()
	{
		SAFE_RELEASE(m_pVertexBuffer);
	}

	void RXVertexBufferDX9::InsertVertex(FLOAT rX, FLOAT rY, FLOAT rZ, DWORD dwColor)
	{
		CustomVertex customVertex = { { rX, rY, rZ }, dwColor };
		m_vecVertex.push_back(customVertex);
	}

	void RXVertexBufferDX9::DrawPrimitive(D3DPRIMITIVETYPE primitiveType)
	{
		g_pD3DDevice9->SetFVF(m_dwFVF);
		g_pD3DDevice9->SetStreamSource(
			0,                     // ��Ʈ�� �ѹ��� 0���� �����մϴ�.
			m_pVertexBuffer,       // ���� ���۸� �������ݴϴ�.
			0,                     // �������� 0���� �����մϴ�.
			sizeof(CustomVertex)); // ����(Stride)�� FVF�� ������ ũ��� ��ġ�ؾ� �մϴ�.

		g_pD3DDevice9->DrawPrimitive(
			primitiveType,           // ������ ������ �����մϴ�.
			0,                       // �������� 0���� �����մϴ�.
			CalcPrimitiveCount(primitiveType, m_vecVertex.size())); // ������Ƽ�� �����Դϴ�.
	}

	HRESULT RXVertexBufferDX9::CreateVertexBuffer()
	{
		INT32 vertexCnt = m_vecVertex.size();

		// ���� ���۸� �����մϴ�.
		g_DXResult = g_pD3DDevice9->CreateVertexBuffer(
			sizeof(CustomVertex) * vertexCnt, // ���� ������ ũ���Դϴ�.
			D3DUSAGE_NONE,                    // Usage�� 0���� �����մϴ�.
			m_dwFVF,                          // FVF �����Դϴ�.
			D3DPOOL_MANAGED,                  // �޸�Ǯ�Դϴ�.
			&m_pVertexBuffer,                 // ���� ������ �������Դϴ�.
			nullptr);                         // nullptr�� �����մϴ�.

		DXERR_HANDLER(g_DXResult);
		NULLCHK_EFAIL_RETURN(m_pVertexBuffer, "���� ���� �ʱ�ȭ ����!");

		// ���� ���ۿ� ������ ���� ������ �����մϴ�.
		// �޸𸮿� �����ϱ� ������ �޸𸮸� ��װ� Ǫ�� ������ �ֽ��ϴ�.
		void* pVertexData = nullptr;
		m_pVertexBuffer->Lock(
			0,                                // �������� 0�̸� ��ü ����Դϴ�.
			sizeof(CustomVertex) * vertexCnt, // ������ ���� ������ ũ�⸦ �Ѱ��ݴϴ�.
			&pVertexData,                     // ����� ���� ������ �ٷ� �� �ִ� �����͸� �������ݴϴ�.
			D3DFLAG_NONE);                    // ��� �÷��״� 0���� �����մϴ�.

		::CopyMemory(pVertexData, &m_vecVertex[0], sizeof(CustomVertex) * vertexCnt);
		m_pVertexBuffer->Unlock();
		
		return S_OK;
	}

} // namespace RX end