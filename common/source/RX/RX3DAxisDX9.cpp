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
#include "PCH.h"
#include "RX3DAxisDX9.h"

namespace RX
{

	RX3DAxisDX9::~RX3DAxisDX9()
	{
		SAFE_DELTE(m_pVB);
	}

	HRESULT RX3DAxisDX9::CreateAxis(FLOAT rDist)
	{
		m_pVB = RXNew RX::RXVertexBufferDX9;
		NULLCHK_HEAPALLOC(m_pVB);

		// X���Դϴ�.
		m_pVB->InsertVertex(-rDist, 0.0f, 0.0f, DXCOLOR_RED);
		m_pVB->InsertVertex(rDist, 0.0f, 0.0f, DXCOLOR_RED);

		// Y���Դϴ�.
		m_pVB->InsertVertex(0.0f, -rDist, 0.0f, DXCOLOR_GREEN);
		m_pVB->InsertVertex(0.0f, rDist, 0.0f, DXCOLOR_GREEN);

		// Z���Դϴ�.
		m_pVB->InsertVertex(0.0f, 0.0f, -rDist, DXCOLOR_BLUE);
		m_pVB->InsertVertex(0.0f, 0.0f, rDist, DXCOLOR_BLUE);

		m_pVB->setFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		m_pVB->CreateVertexBuffer();

		return S_OK;
	}

	void RX3DAxisDX9::DrawAxis()
	{
		m_pVB->DrawPrimitive(D3DPT_LINELIST);
	}


} // namespace RX end