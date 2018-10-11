/*====================================================================================
 *
 * Copyright (C) Ruvendix. All Rights Reserved.
 *
 * <�ۼ� ��¥>
 * 2018-08-12
 *
 * <���� ����>
 * _tWinMain()�� �ھ� ���� ��ƾ�Դϴ�.
 * �ܺ� ������Ʈ���� ����ϸ� ���ϰ� ���α׷����� �� �� �ֽ��ϴ�.
 * ���� Ŭ���̵� �����ϹǷ� �����ο� ������ �����մϴ�.
 * DirectX9 ���� �ھ� ���� ��ƾ�Դϴ�.
 *
 ====================================================================================*/
#ifndef RXMAINDX9_H_
#define RXMAINDX9_H_

#include "RXMain.h"
#include "RXFrame.h"

namespace RX
{

	class DLL_DEFINE RXMain_DX9 : public RXMain
	{
	public:
		RXMain_DX9();
		virtual ~RXMain_DX9();

		virtual HRESULT InitMain()  override;
		virtual HRESULT InitD3D9();
		virtual HRESULT DriveMain() override;
		virtual HRESULT Release()   override;
		virtual void    ToggleFullScreenMode(bool bFullScreen = false) override;

		HRESULT VerifyDevice(D3DPRESENT_PARAMETERS* pD3DPP);

		// ====================================================================================
		// ���� ����
		virtual HRESULT Update();
		HRESULT Render(FLOAT rInterpolation);
		HRESULT BeginRender();
		HRESULT EndRender();

		// ====================================================================================
		// �ν�Ʈ ����̽�, ���� ����̽�
		HRESULT OnLostDevice();
		HRESULT OnResetDevice();

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

	protected:
		// ====================================================================================
		// �⺻ ����
		bool                 m_bLostDevice;
		bool                 m_bMSAA;      // ��Ƽ ���ø�(��Ƽ �����¡) ��� �����Դϴ�.
		DWORD                m_dwBehavior; // ���� ó�� ����Դϴ�.
		IDirect3D9*          m_pD3D9;
		IDirect3DDevice9*    m_pD3DDevice9;
		D3DCOLOR             m_clearColor;
		RXFrame              m_frame;
	};

} // namespace RX end

#endif