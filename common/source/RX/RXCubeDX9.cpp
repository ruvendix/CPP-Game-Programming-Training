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
#include "PCH.h"
#include "RXCubeDX9.h"

namespace RX
{

	RXCubeDX9::~RXCubeDX9()
	{
		SAFE_DELTE(m_pVB);
	}

	HRESULT RXCubeDX9::CreateCube(const D3DXVECTOR3& vMin,
		const D3DXVECTOR3& vMax, CUBE_DRAW_TYPE type)
	{
		// �� �� �������� ���̸� ���մϴ�.
		FLOAT rDistX = std::abs(vMax.x - vMin.x);
		FLOAT rDistY = std::abs(vMax.y - vMin.y);
		FLOAT rDistZ = std::abs(vMax.z - vMin.z);

		// ===============================================
		// ť�긦 �������Ϸ��� �ﰢ�� 12���� �ʿ��մϴ�.
		// �� �ﰢ���� ���ϱ� ���ؼ��� ���� 8���� �ʿ��մϴ�.
		// ���� ���� 8������ ���س��� �� ���մϴ�.
		// �� �κ��� �ּ����� ǥ���س����Կ�.
		// ===============================================

		// ���� ���� 4��
		D3DXVECTOR3 vCube[8];
		::ZeroMemory(vCube, sizeof(D3DXVECTOR3) * _countof(vCube));
		RX::SetVector(&vCube[0], vMax.x - rDistX, vMax.y, vMax.z - rDistZ); // 0
		RX::SetVector(&vCube[1], vMax.x, vMax.y, vMax.z - rDistZ);          // 1
		RX::SetVector(&vCube[2], vMax.x, vMax.y, vMax.z);                   // 2
		RX::SetVector(&vCube[3], vMax.x - rDistX, vMax.y, vMax.z);          // 3

		// �Ʒ��� ���� 4��
		RX::SetVector(&vCube[4], vMin.x, vMin.y, vMin.z);                   // 4
		RX::SetVector(&vCube[5], vMin.x + rDistX, vMin.y, vMin.z);          // 5
		RX::SetVector(&vCube[6], vMin.x + rDistX, vMin.y, vMin.z + rDistZ); // 6
		RX::SetVector(&vCube[7], vMin.x, vMin.y, vMin.z + rDistZ);          // 7

		m_pVB = RXNew RX::RXVertexBufferDX9;
		NULLCHK_HEAPALLOC(m_pVB);

		if (type == CUBE_DRAW_TYPE::INDEX)
		{
			// �ε����� ���� ���� 8���� �˴ϴ�.
			m_pVB->InsertVertex(vCube[0], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[1], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[2], DXCOLOR_BLUE);
			m_pVB->InsertVertex(vCube[3], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[4], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[5], DXCOLOR_BLUE);
			m_pVB->InsertVertex(vCube[6], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[7], DXCOLOR_GREEN);

			// ===============================================
			// �ε��� �����Դϴ�.
			// ���� �ﰢ�� 2��
			m_pVB->InsertIndex(0, 1, 5);
			m_pVB->InsertIndex(0, 5, 4);
			// ===============================================
			// ���� ���� �ﰢ�� 2��
			m_pVB->InsertIndex(0, 4, 3);
			m_pVB->InsertIndex(3, 4, 7);
			// ===============================================
			// ������ ���� �ﰢ�� 2��
			m_pVB->InsertIndex(1, 2, 5);
			m_pVB->InsertIndex(2, 6, 5);
			// ===============================================
			// ���� �ﰢ�� 2��
			m_pVB->InsertIndex(0, 3, 2);
			m_pVB->InsertIndex(0, 2, 1);
			// ===============================================
			// �Ʒ��� �ﰢ�� 2��
			m_pVB->InsertIndex(4, 6, 7);
			m_pVB->InsertIndex(4, 5, 6);
			// ===============================================
			// �޸� �ﰢ�� 2��
			m_pVB->InsertIndex(3, 6, 2);
			m_pVB->InsertIndex(3, 7, 6);
			// ===============================================
			// ť��� �ﰢ���� 12�� �ֽ��ϴ�.
			m_pVB->CreateIndexBuffer(12);
		}
		else
		{
			// ===============================================
			// ���� �ﰢ�� 2��
			m_pVB->InsertVertex(vCube[0], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[1], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[5], DXCOLOR_BLUE);

			m_pVB->InsertVertex(vCube[0], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[5], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[4], DXCOLOR_BLUE);
			// ===============================================
			// ���� ���� �ﰢ�� 2��
			m_pVB->InsertVertex(vCube[0], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[4], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[3], DXCOLOR_BLUE);

			m_pVB->InsertVertex(vCube[3], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[4], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[7], DXCOLOR_BLUE);
			// ===============================================
			// ������ ���� �ﰢ�� 2��
			m_pVB->InsertVertex(vCube[1], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[2], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[5], DXCOLOR_BLUE);

			m_pVB->InsertVertex(vCube[2], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[6], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[5], DXCOLOR_BLUE);
			// ===============================================
			// ���� �ﰢ�� 2��
			m_pVB->InsertVertex(vCube[0], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[3], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[2], DXCOLOR_BLUE);

			m_pVB->InsertVertex(vCube[0], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[2], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[1], DXCOLOR_BLUE);
			// ===============================================
			// �Ʒ��� �ﰢ�� 2��
			m_pVB->InsertVertex(vCube[4], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[6], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[7], DXCOLOR_BLUE);

			m_pVB->InsertVertex(vCube[4], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[5], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[6], DXCOLOR_BLUE);
			// ===============================================
			// �޸� �ﰢ�� 2��
			m_pVB->InsertVertex(vCube[3], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[6], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[2], DXCOLOR_BLUE);

			m_pVB->InsertVertex(vCube[3], DXCOLOR_RED);
			m_pVB->InsertVertex(vCube[7], DXCOLOR_GREEN);
			m_pVB->InsertVertex(vCube[6], DXCOLOR_BLUE);
		}

		m_pVB->CreateVertexBuffer();
		return S_OK;
	}

	void RXCubeDX9::DrawCube(CUBE_DRAW_TYPE type)
	{
		if (type == CUBE_DRAW_TYPE::INDEX)
		{
			m_pVB->DrawIndexedPrimitive();
		}
		else
		{
			m_pVB->DrawPrimitive(D3DPT_TRIANGLELIST);
		}
	}

} // namespace RX end