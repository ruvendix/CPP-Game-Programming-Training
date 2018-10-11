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

	void RXVertexBufferDX9::DrawPrimitive()
	{
		g_pD3DDevice9->SetFVF(m_dwFVF);
		g_pD3DDevice9->SetStreamSource(
			0,                     // ��Ʈ�� �ѹ��� 0���� �����մϴ�.
			m_pVertexBuffer,       // ���� ���۸� �������ݴϴ�.
			0,                     // �������� 0���� �����մϴ�.
			sizeof(CustomVertex)); // ����(Stride)�� FVF�� ������ ũ��� ��ġ�ؾ� �մϴ�.

		g_pD3DDevice9->DrawPrimitive(
			D3DPT_TRIANGLELIST,      // ������ ������ �����մϴ�.
			0,                       // �������� 0���� �����մϴ�.
			m_vecVertex.size() / 3); // ������Ƽ�� �����Դϴ�.
	}

	HRESULT RXVertexBufferDX9::CreateVertexBuffer()
	{
		INT32 vertexCnt = m_vecVertex.size();

		// ���� ���۸� �����մϴ�.
		g_DXResult = g_pD3DDevice9->CreateVertexBuffer(
			sizeof(CustomVertex) * vertexCnt, // ���� ������ ũ���Դϴ�.
			0,                                // Usage�� 0���� �����մϴ�.
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
			0);                               // ��� �÷��״� 0���� �����մϴ�.

		::CopyMemory(pVertexData, &m_vecVertex[0], sizeof(CustomVertex) * vertexCnt);
		m_pVertexBuffer->Unlock();

		return S_OK;
	}

} // namespace RX end