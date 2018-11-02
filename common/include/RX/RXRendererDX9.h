/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-10-15
 *
 * <���� ����>
 * DirectX9 �������Դϴ�.
 * ���� ����̽��� �����ؼ� �������� �ٽ��Դϴ�.
 *
 ====================================================================================*/
#ifndef RXRENDERERDX9_H__
#define RXRENDERERDX9_H__

#include "common.h"
#include "RXVertexBufferDX9.h"
#include "RXIndexBufferDX9.h"

namespace RX
{

	class DLL_DEFINE RXRendererDX9
	{
		PHOENIX_SINGLETON(RXRendererDX9);
	public:
		void Init();
		void ResetD3DPP(); // ������ �ʿ� ���� �⺻ ������ �����մϴ�.
		void ResetDrawCallCount()
		{
			m_drawCallCnt = 0;
		}

		// ���ҽ��� �޸�Ǯ�� D3DPOOL_DEFAULT�� �͸� �����մϴ�.
		// �� ���� ���ҽ��� �������� �ʽ��ϴ�.
		void ArrangeVideoMemory();

		// ������ ���¸� �����մϴ�.
		void DefaultRenderState();
		void AdjustRenderState(D3DRENDERSTATETYPE state, DWORD dwValue);

		// ����Ʈ�� �����մϴ�.
		void AdjustViewport(INT32 x, INT32 y, INT32 width, INT32 height);

		// ���� ������� �����̽��� ���Ϸ� �����մϴ�. (��ũ���� ���, ���� ����...)
		void SaveBackBufferToFile(const CHAR* szFile, D3DXIMAGE_FILEFORMAT fileFormat = D3DXIFF_JPG);

		HRESULT CreateDevice();
		HRESULT BeginRender();
		HRESULT EndRender();
		HRESULT Present();
		HRESULT Release();
		HRESULT VerifyDevice(D3DPRESENT_PARAMETERS* pD3DPP);
		
		// ====================================================================================
		// ���� ����
		void ApplyWorldMatrix(const D3DXMATRIXA16& matWorld);
		void ApplyViewMatrix(const D3DXMATRIXA16& matView);
		void ApplyProjectionMatrix(const D3DXMATRIXA16& matProjection);

		void CopyWorldMatrix(D3DXMATRIXA16* pMatWorld);
		void CopyViewMatrix(D3DXMATRIXA16* pMatView);
		void CopyProjectionMatrix(D3DXMATRIXA16* pMatProjection);

		void DefaultProjectionMatrix();

		HRESULT DrawPrimitive(D3DPRIMITIVETYPE primitiveType,
			const RXVertexBufferDX9& vertexBuffer);
		HRESULT DrawIdxedPrimitive(const RXVertexBufferDX9& vertexBuffer,
			const RXIndexBufferDX9& IndexBuffer);
		HRESULT DrawDXMesh(const LPD3DXMESH pMesh);

		// ====================================================================================
		// ���� ����̽� ���¿� ���� ó�� �Լ�
		HRESULT OnLostDevice();
		HRESULT OnResetDevice();
		HRESULT OnRecreateDevice();

		bool IsLostDevice() const noexcept
		{
			return (m_bLostDevice == true);
		}

		// ====================================================================================
		// Getter
		IDirect3D9* getD3D9() const noexcept
		{
			return m_pD3D9;
		}

		IDirect3DDevice9* getD3DDevice9() const noexcept
		{
			return m_pD3DDevice9;
		}

		// ====================================================================================
		// Setter
		void setClearColor(D3DCOLOR clearColor)
		{
			m_clearColor = clearColor;
		}

		void setLostDevice(bool bLostDevice)
		{
			m_bLostDevice = bLostDevice;
		}

	private:
		INT32                  m_drawCallCnt; // �����Ӵ� ������ �Լ� ȣ�� Ƚ���Դϴ�.
		INT32		           m_adapterIdx;  // ���� ����͸� ���� �̴ϴ�.
		bool                   m_bLostDevice; // ���� ����̽� �ս� �����Դϴ�.
		bool                   m_bMSAA;       // ��Ƽ ���ø�(��Ƽ�����¡) ��� �����Դϴ�.
		bool		           m_bVSync;      // ��������ȭ �����Դϴ�.
		DWORD                  m_dwBehavior;  // ���� ó�� ����Դϴ�.
		RECT                   m_rtScissor;   // ������ �������� ����(����Ʈ�� �ƴ� Ŭ����)
		IDirect3D9*            m_pD3D9;       // D3D9 ��ü�Դϴ�.
		IDirect3DDevice9*      m_pD3DDevice9; // D3D9 ���� ����̽��Դϴ�.
		D3DPRESENT_PARAMETERS* m_pD3DPP;      // D3D9 ���� ����̽��� �����Դϴ�.
		D3DVIEWPORT9           m_viewport9;   // ����� �����̽��� ����Ʈ�Դϴ�.
		D3DCOLOR               m_clearColor;  // ����� �����̽��� Ŭ���� �����Դϴ�.
	};

} // namespace RX end
#endif