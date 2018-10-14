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
		m_vertexCnt = 0;
		m_pVB       = nullptr;
		m_pIB       = nullptr;
	}

	RXVertexBufferDX9::~RXVertexBufferDX9()
	{
		SAFE_RELEASE(m_pIB);
		SAFE_RELEASE(m_pVB);
	}

	void RXVertexBufferDX9::InsertVertex(FLOAT rX, FLOAT rY, FLOAT rZ, DWORD dwColor)
	{
		VertexInfo vertexInfo = { { rX, rY, rZ }, dwColor };
		m_vecVertex.push_back(vertexInfo);
	}

	void RXVertexBufferDX9::InsertVertex(const D3DXVECTOR3& vPos, DWORD dwColor)
	{
		VertexInfo vertexInfo = { { vPos.x, vPos.y, vPos.z }, dwColor };
		m_vecVertex.push_back(vertexInfo);
	}

	void RXVertexBufferDX9::InsertIndex(WORD first, WORD second, WORD third)
	{
		IndexInfo indexInfo = { first, second, third };
		m_vecIndex.push_back(indexInfo);
	}

	void RXVertexBufferDX9::DrawPrimitive(D3DPRIMITIVETYPE primitiveType)
	{
		g_pD3DDevice9->SetFVF(VertexInfo::FORMAT);
		g_pD3DDevice9->SetStreamSource(
			0,                   // ��Ʈ�� �ѹ��� 0���� �����մϴ�.
			m_pVB,               // ���� ���۸� �������ݴϴ�.
			0,                   // �������� 0���� �����մϴ�.
			sizeof(VertexInfo)); // ����(Stride)�� FVF�� ������ ũ��� ��ġ�ؾ� �մϴ�.

		g_pD3DDevice9->DrawPrimitive(
			primitiveType, // ������ ������ �����մϴ�.
			0,             // �������� 0���� �����մϴ�.
			CalcPrimitiveCount(primitiveType, m_vecVertex.size())); // ������Ƽ�� �����Դϴ�.
	}

	void RXVertexBufferDX9::DrawIndexedPrimitive()
	{
		NULL_RETURN(m_pIB); // �ε��� ���۰� ������ ���� ó���˴ϴ�.

		g_pD3DDevice9->SetFVF(VertexInfo::FORMAT);
		g_pD3DDevice9->SetStreamSource(
			0,                   // ��Ʈ�� �ѹ��� 0���� �����մϴ�.
			m_pVB,               // ���� ���۸� �������ݴϴ�.
			0,                   // �������� 0���� �����մϴ�.
			sizeof(VertexInfo)); // ����(Stride)�� FVF�� ������ ũ��� ��ġ�ؾ� �մϴ�.

		// �ε��� ���۸� ���� ����̽��� �������ݴϴ�.
		g_pD3DDevice9->SetIndices(m_pIB);

		g_pD3DDevice9->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST, // ������ ������ �����մϴ�.
			0,                  // ���� ���ۿ��� ������ ���� �ε����� �����մϴ�. (0���� ����)
			0,                  // ������ �ε����� �����մϴ�. (0���� ����)
			m_vertexCnt,        // ���� ������ �����մϴ�.
			0,                  // �ε��� ������ �������Դϴ�. (0���� ����)
			m_triangleCnt);     // ������Ƽ�� �����Դϴ�.

		// �ε��� ������ ������Ƽ�� ������ �⺻ ������ ��
		// D3DPT_TRIANGLESTRIP�� �����մϴ�.
	}

	HRESULT RXVertexBufferDX9::CreateVertexBuffer()
	{
		m_vertexCnt = m_vecVertex.size();

		// ���� ���۸� �����մϴ�.
		g_DXResult = g_pD3DDevice9->CreateVertexBuffer(
			sizeof(VertexInfo) * m_vertexCnt, // ���� ������ ũ���Դϴ�.
			D3DUSAGE_NONE,                    // Usage�� 0���� �����մϴ�.
			VertexInfo::FORMAT,               // FVF �����Դϴ�.
			D3DPOOL_MANAGED,                  // �޸�Ǯ�Դϴ�.
			&m_pVB,                           // ���� ������ �������Դϴ�.
			nullptr);                         // nullptr�� �����մϴ�.

		DXERR_HANDLER(g_DXResult);
		NULLCHK_EFAIL_RETURN(m_pVB, "���� ���� �ʱ�ȭ ����!");

		// ���� ���ۿ� ������ ���� ������ �����մϴ�.
		// �޸𸮿� �����ϱ� ������ �޸𸮸� ��װ� Ǫ�� ������ �ֽ��ϴ�.
		void* pVertexData = nullptr;
		m_pVB->Lock(
			0,                                // �������� 0�̸� ��ü ����Դϴ�.
			sizeof(VertexInfo) * m_vertexCnt, // ������ ���� ������ ũ�⸦ �Ѱ��ݴϴ�.
			&pVertexData,                     // ����� ���� ������ �ٷ� �� �ִ� �����͸� �������ݴϴ�.
			D3DFLAG_NONE);                    // ��� �÷��״� 0���� �����մϴ�.

		::CopyMemory(pVertexData, &m_vecVertex[0], sizeof(VertexInfo) * m_vertexCnt);
		m_pVB->Unlock();
		
		return S_OK;
	}

	HRESULT RXVertexBufferDX9::CreateIndexBuffer(INT32 triangleCnt)
	{
		m_triangleCnt = triangleCnt;

		// �ε��� ���۸� �����մϴ�.
		g_DXResult = g_pD3DDevice9->CreateIndexBuffer(
			sizeof(IndexInfo) * m_triangleCnt, // �ε����� ũ���Դϴ�.
			D3DUSAGE_NONE,                     // Usage�� 0���� �����մϴ�.
			IndexInfo::FORMAT,                 // �ε��� ���� �����Դϴ�. (D3DFMT_INDEX16)
			D3DPOOL_MANAGED,                   // �޸�Ǯ�Դϴ�.
			&m_pIB,                            // �ε��� ������ �������Դϴ�.
			nullptr);                          // nullptr�� �����մϴ�.
			
		DXERR_HANDLER(g_DXResult);
		NULLCHK_EFAIL_RETURN(m_pIB, "�ε��� ���� �ʱ�ȭ ����!");

		// �ε��� ���ۿ� ������ �ε��� ������ �����մϴ�.
		// �޸𸮿� �����ϱ� ������ �޸𸮸� ��װ� Ǫ�� ������ �ֽ��ϴ�.
		void* pIndexData = nullptr;
		m_pIB->Lock(
			0,                                 // �������� 0�̸� ��ü ����Դϴ�.
			sizeof(IndexInfo) * m_triangleCnt, // ������ �ε��� ������ ũ�⸦ �Ѱ��ݴϴ�.
			&pIndexData,                       // ����� �ε��� ������ �ٷ� �� �ִ� �����͸� �������ݴϴ�.
			D3DFLAG_NONE);                     // ��� �÷��״� 0���� �����մϴ�.

		::CopyMemory(pIndexData, &m_vecIndex[0], sizeof(IndexInfo) * m_triangleCnt);
		m_pIB->Unlock();

		return S_OK;
	}

} // namespace RX end