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
#include "PCH.h"
#include "RXMainDX9.h"

extern IDirect3DDevice9* g_pD3DDevice9 = nullptr;
extern HRESULT           g_DXResult    = S_OK;

namespace RX
{

	RXMain_DX9::RXMain_DX9()
	{
		m_bLostDevice = false;
		m_bMSAA       = false;
		m_pD3D9       = nullptr;
		m_pD3DDevice9 = nullptr;
		m_clearColor  = DXCOLOR_BLACK;
		m_dwBehavior  = 0;
	}

	RXMain_DX9::~RXMain_DX9()
	{

	}

	HRESULT RXMain_DX9::InitMain()
	{
		RXMain::InitMain();

		if (FAILED(InitD3D9()))
		{			
			RXERRLOG_EFAIL_RETURN("D3D9 �ʱ�ȭ ����!");
		}

		return S_OK;
	}

	HRESULT RXMain_DX9::InitD3D9()
	{
		// DirectX9 ��ü�� �����մϴ�.
		// �������̽� �����Ϳ� �ν���ȭ�� ��ü�� ��ȯ���ݴϴ�.
		m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
		NULLCHK_EFAIL_RETURN(m_pD3D9, "DirectX9 ��ü ���� ����!");
		RXLOG(false, "DirectX9 ��ü ���� ����!");
		
		// ====================================================================================
		// ���� ����̽� ������ ���� ������ �������ݴϴ�.
		// �Ϲ������� Present Parameters�� �ٿ��� PP��� �����մϴ�.
		D3DPRESENT_PARAMETERS D3DPP;
		::ZeroMemory(&D3DPP, sizeof(D3DPP));

		// ====================================================================================
		// ���� ����̽� ������ �������� �����մϴ�.
		VerifyDevice(&D3DPP);

		// ====================================================================================
		// ������ ������ ������ ������ ä���ݴϴ�.
		//
		// ���� ���ٽ� ���� ������ �����մϴ�.
		// D3DFMT_D24S8�� ���� ���� 24��Ʈ, ���ٽ� ���� 8��Ʈ�� ���մϴ�.
		D3DPP.EnableAutoDepthStencil = true;
		D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;

		// ������ �ø����� �� ���� ȿ���� �����մϴ�.
		// �ʹݿ��� D3DSWAPEFFECT_DISCARD�� ���� �����մϴ�.
		D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;

		// Ư���� �÷��׸� �����մϴ�.
		// ���� ����� �÷��װ� ������ 0���� �����մϴ�.
		D3DPP.Flags = 0;

		// ���α׷� â ������ �����մϴ�.
		// ���α׷� â �ڵ�� â ��� ���θ� �������ָ� �˴ϴ�.
		// ���߿� ��ü ȭ�鵵 �����ϰ� ������ �ʹݿ��� â ��常 ����մϴ�.
		D3DPP.hDeviceWindow = m_hMainWnd;
		D3DPP.Windowed      = !m_bFullScreen;
		
		// ====================================================================================

		HRESULT hDXResult = S_OK;

		// ���� ����̽� ������ ���� ������ ���������Ƿ� ���� ����̽��� �������ݴϴ�.
		hDXResult = m_pD3D9->CreateDevice(
			D3DADAPTER_DEFAULT,     // ����͸� ���ϴµ� ����� ������� �����ϸ� �˴ϴ�.
			D3DDEVTYPE_HAL,         // HAL Device�� ����ϰڴٴ� ���Դϴ�.
			D3DPP.hDeviceWindow,    // ���� ����̽��� Ÿ�� ���α׷� â�� �ǹ��մϴ�.
			m_dwBehavior,           // ���� ó���� �׷��� ī�忡�� �ñ�ٴ� ���Դϴ�.
			&D3DPP,                 // ���� ����̽� ������ ���� ������ �Ѱ��ݴϴ�.
			&m_pD3DDevice9);        // ���� ����̽��� ��ü �����͸� ���� �������̽� �������Դϴ�.
	
		DXERR_HANDLER(hDXResult);
		NULLCHK_EFAIL_RETURN(m_pD3DDevice9, "DirectX9 ���� ����̽� ���� ����!");
		g_pD3DDevice9 = m_pD3DDevice9;

		RXLOG(false, "DirectX9 ���� ����̽� ���� ����!");
		return S_OK;
	}

	HRESULT RXMain_DX9::DriveMain()
	{
		MSG msg;
		::ZeroMemory(&msg, sizeof(msg));

		bool m_bDriveFailure = false;

		DWORD nextGameTime    = ::timeGetTime();
		INT32 updateCallCount = 0;
		FLOAT rRenderingInterpolation = 0.0f;

		for ( ; ; )
		{
			// �ܺο����� ������ ���� ��Ʈ���� �����մϴ�.
			if (m_routineState == ROUTINE_STATE::EXIT)
			{
				m_msgCode = 0;
				break;
			}

			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					m_routineState = ROUTINE_STATE::EXIT;
					m_msgCode = msg.wParam;
					break;
				}

				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				updateCallCount = 0;

				// ������Ʈ ��ƾ�� FPS�� ������ �޽��ϴ�.
				// 25 ������ ���ָ� �����ϴ�.
				// (1 / UPDATE_FRAME_PER_SECOND) ������ �����ϹǷ�
				// �ƹ��� ���� �ϵ����� �ص� �ʴ� 25�� �����Ǿ��ֽ��ϴ�.
				// �ݸ鿡 �ƹ��� ���� �ϵ����� �ص� ������Ʈ�� MAX_FRAMESKIP��ŭ �� �ڿ�
				// �������ϹǷ� ��� ���� ���� �ӵ��� ����˴ϴ�.
				while ( (::timeGetTime() > nextGameTime) &&
					    (updateCallCount < MAX_FRAMESKIP) )
				{
					if (m_bLostDevice == false)
					{
						Update();
					}

					nextGameTime += FRAME_SKIP_TIME; // 1000 / 25 = 40 => 0.04���� ����
					++updateCallCount;

					//RXDEBUGLOG("������Ʈ ȣ�� �� : %d", updateCallCount);
				}

				// ������ �ϵ��� ���� ���� ���̰� ���մϴ�.
				// �������� �����ϴ� �κ��Դϴ�.
				// ���������̼��� 0.0 ~ 1.0 ���̷� �ɴϴ�.
				rRenderingInterpolation =
					float(::timeGetTime() + FRAME_SKIP_TIME - nextGameTime) / float(FRAME_SKIP_TIME);
				//RXDEBUGLOG("������ ������ : %.2f", rRenderingInterpolation);				
				Render(rRenderingInterpolation);

				// �������� �Ϸ��ϸ� ������ ī��Ʈ�� 1���� �˴ϴ�.
				// �������� ���� ������ �ʿ��ϹǷ� ������ ������ �˴ϴ�.
				m_frame.UpdateFrame();

				if (m_routineState == ROUTINE_STATE::FAILURE)
				{
					m_msgCode = 0;
					m_bDriveFailure = true;
					break;
				}
			}
		}

		if (m_bDriveFailure)
		{
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT RXMain_DX9::Release()
	{
		m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::RELEASE)].func();

		SAFE_RELEASE(m_pD3DDevice9);
		SAFE_RELEASE(m_pD3D9);

		RXMain::Release();
		return S_OK;
	}

	HRESULT RXMain_DX9::ResizeResolution(INT32 clientWidth, INT32 clientHeight)
	{
		RXMain::ResizeResolution(clientWidth, clientHeight);
		OnLostDevice();
		OnResetDevice();
		return S_OK;
	}

	// ���� ����̽��� �����ϱ� ���� �������ִ� �Լ��Դϴ�.
	// �����ϴ� ������ ������ �����ϴ�.
	//
	// 1. �׷��� ī���� ��� �ɷ� ����(����� ȣȯ)
	// 2. �ϵ���� ������ �������� ����
	// 3. MSAA ����
	// 4. ���� ó�� ��� ����(���̴�)
	HRESULT RXMain_DX9::VerifyDevice(D3DPRESENT_PARAMETERS* pD3DPP)
	{
		// ====================================================================================
		// �׷��� ī���� ��� �ɷ��� �����մϴ�.
		D3DDISPLAYMODE mainDisplayMode;
		::ZeroMemory(&mainDisplayMode, sizeof(mainDisplayMode));

		// �׷��� ī���� ��� ������ �����ɴϴ�.
		if (FAILED(m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mainDisplayMode)))
		{
			RXERRLOG_EFAIL_RETURN("�׷��� ī���� ��� ���� ȹ�� ����!");
		}

		// �ĸ� ������ ������ �����մϴ�.
		// �������� 0�� �־ 1�� �νĵ����� �������� ���� 1�� �����մϴ�.
		pD3DPP->BackBufferCount = 1;

		// �ĸ� ���� ������ �����մϴ�.
		// ������� ����, �����Դϴ�.
		// ��ü ȭ���� ���� ���÷��� ��� ������ �������ݴϴ�.
		if (m_bFullScreen == false)
		{
			pD3DPP->BackBufferWidth  = getClientWidth();
			pD3DPP->BackBufferHeight = getClientHeight();
		}

		// �ĸ� ������ ������ �������ݴϴ�.
		pD3DPP->BackBufferFormat = mainDisplayMode.Format;

		// �ĸ� ������ �ֻ����� �����մϴ�.
		// â ��带 ����� ���� D3DPRESENT_RATE_DEFAULT�� �����ϸ� �˴ϴ�.
		if (m_bFullScreen == false)
		{
			pD3DPP->FullScreen_RefreshRateInHz = D3DPRESENT_INTERVAL_DEFAULT;
		}

		// �ĸ� ������ ������ �ø��� ������ �����մϴ�.
		pD3DPP->PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // �⺻�� ��������

		// ��ü ȭ������ ��ȯ�� ���� ó���Դϴ�.
		if (m_bFullScreen)
		{
			bool bResult = false;

			// ��ü ȭ������ ��ȯ�� �� ��� ������ ��� ������ �����ɴϴ�.
			// ���� �׷��� ī�尡 �����ϴ� �ػ󵵸� ���մϴ�.
			// ���� ��� ���� ����� �ػ󵵴� 1920 X 1080������
			// �׷��� ī��� 800 X 600�� �����մϴ�. �̷� �� ����Դϴ�.
			INT32 adapterCount = m_pD3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT, mainDisplayMode.Format);
			for (INT32 i = 0; i < adapterCount; ++i)
			{
				D3DDISPLAYMODE subDisplayMode;
				::ZeroMemory(&subDisplayMode, sizeof(subDisplayMode));

				// ���ϴ� �ػ� �Ǵ� ���İ� ȣȯ�� �Ǵ��� �����մϴ�.
				HRESULT hDXResult = m_pD3D9->EnumAdapterModes(D3DADAPTER_DEFAULT,
					mainDisplayMode.Format, i, &subDisplayMode);
				DXERR_HANDLER(hDXResult);
	
				// ���� �ػ󵵿� ��ü ȭ�� �ػ󵵸� ���մϴ�.
				if ( (subDisplayMode.Width == mainDisplayMode.Width) &&
					 (subDisplayMode.Height == mainDisplayMode.Height) &&
					 (subDisplayMode.RefreshRate >= mainDisplayMode.RefreshRate) )
				{
					pD3DPP->BackBufferWidth            = subDisplayMode.Width;
					pD3DPP->BackBufferHeight           = subDisplayMode.Height;
					pD3DPP->FullScreen_RefreshRateInHz = subDisplayMode.RefreshRate;
					bResult = true;
					break;
				}
			}

			if (bResult == false)
			{
				RXERRLOG_EFAIL_RETURN("��ü ȭ���� �� ���� �׷��� ī�尡 �ػ� �Ǵ� ������ �������� ����!");
			}
		}

		// ====================================================================================
		// �ϵ���� ������ �������� �����մϴ�.
		if (FAILED(m_pD3D9->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			pD3DPP->BackBufferFormat, pD3DPP->BackBufferFormat, !m_bFullScreen)))
		{
			RXERRLOG_EFAIL_RETURN("�ϵ���� ������ �������� ����!");
		}

		// ====================================================================================
		// MSAA(Multisample AntiAliasing)�� �����մϴ�.
		// AA�� ���� ����� ������ ���� �⺻���� �� MSAA�Դϴ�.
		// 2, 4, 8, 16�� �����մϴ�.
		if (m_bMSAA)
		{
			DWORD dwMSAAQuality = 0;
			INT32 MSAATable[4] =
			{
				D3DMULTISAMPLE_16_SAMPLES,
				D3DMULTISAMPLE_8_SAMPLES,
				D3DMULTISAMPLE_4_SAMPLES,
				D3DMULTISAMPLE_2_SAMPLES,
			};

			bool bResult = false;
			for (INT32 i = 0; i < 4; ++i)
			{
				D3DMULTISAMPLE_TYPE type = static_cast<D3DMULTISAMPLE_TYPE>(MSAATable[i]);

				if (SUCCEEDED(m_pD3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_HAL, mainDisplayMode.Format, !m_bFullScreen, type, &dwMSAAQuality)))
				{
					pD3DPP->MultiSampleType = type;
					pD3DPP->MultiSampleQuality = dwMSAAQuality - 1;
					bResult = true;
					break;
				}
			}

			if (bResult == false)
			{
				pD3DPP->MultiSampleType    = D3DMULTISAMPLE_NONE;
				pD3DPP->MultiSampleQuality = 0;
				RXERRLOG_EFAIL_RETURN("MSAA�� �������� �����Ƿ� 0���� ������!");
			}
		}
		else
		{
			// ��Ƽ ���ø� ������ �����մϴ�.
			// MSAA(MultiSample AntiAliasing)��� �մϴ�.
			// �ʹݿ��� ����� ���� �����Ƿ� 0���� �����մϴ�.
			pD3DPP->MultiSampleType    = D3DMULTISAMPLE_NONE;
			pD3DPP->MultiSampleQuality = 0;
		}

		// ====================================================================================
		// ���� ó�� ����� �����մϴ�.
		D3DCAPS9 D3DCaps9;
		::ZeroMemory(&D3DCaps9, sizeof(D3DCaps9));

		// �׷��� ī���� �ɷ� ������ �����ɴϴ�.
		m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &D3DCaps9);

		// �׷��� ī�尡 TL, ���� ���̴� 1.0, �ȼ� ���̴� 1.0�� �������� ������
		// ���� ó�� ����� ����Ʈ���� ���� ó���� �����մϴ�.
		if ( (D3DCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ||
			 (D3DCaps9.VertexShaderVersion < D3DVS_VERSION(1, 0)) ||
			 (D3DCaps9.PixelShaderVersion < D3DPS_VERSION(1, 0)))
		{
			m_dwBehavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			m_dwBehavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		return S_OK;
	}

	HRESULT RXMain_DX9::ToggleFullScreenMode(bool bFullScreen)
	{
		RXMain::ToggleFullScreenMode(bFullScreen);
		OnLostDevice();
		OnResetDevice();
		return S_OK;
	}

	HRESULT RXMain_DX9::Update()
	{
		RXMain::Update();
		return S_OK;
	}

	HRESULT RXMain_DX9::Render(FLOAT rInterpolation)
	{
		// ���� ����̽��� ������ ���� �������մϴ�.
		if (m_bLostDevice == false)
		{
			BeginRender();

			if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::RENDER)].func()))
			{
				RXERRLOG_EFAIL_RETURN("���� ���� ����!");
			}

			EndRender();
		}

		NULLCHK(m_pD3DDevice9);
		HRESULT hDXReuslt = m_pD3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);

		// �ν�Ʈ ����̽��� ���� �߻��� �� �����Ƿ� ���� ���� �ڵ鷯�� ���� �ʽ��ϴ�.
		if (hDXReuslt == D3DERR_DEVICELOST)
		{
			RXERRLOG("���� ����̽� �ս� �߻�!");
			m_bLostDevice = true;
			Sleep(100); // ���� ����̽��� �սǵǾ��ٸ� ��� CPU�� Ǯ���ݴϴ�.
		}

		// ���� ����̽��� �սǵǾ��ٸ� ó�����ݴϴ�.
		// ������ ����� �ð��� �ֱ� ���� m_bLostDevice�� �̿��մϴ�.
		if (m_bLostDevice)
		{
			// ���� ����̽��� ��� ����� �� �ִ��� Ȯ���մϴ�.
			if (FAILED(hDXReuslt = m_pD3DDevice9->TestCooperativeLevel()))
			{
				// ���� ����̽��� ������ �սǵǾ ������ �� ���� ��Ȳ�Դϴ�.
				// �̷� ��쿡�� ���α׷��� ������ؾ� �մϴ�.
				if (hDXReuslt == D3DERR_DEVICELOST)
				{
					RXERRLOG_EFAIL_RETURN("���� ����̽��� ������ �սǵǾ����ϴ�!");
				}
				// ���� ����̽��� ������ �� �ִ� ��Ȳ�Դϴ�.
				// ���� ����̽��� �����Ϸ��� ���� ����̽��� ���õ�
				// ��� ��ü���� ���¸� �ν�Ʈ ���·� ������ �մϴ�.
				else if (hDXReuslt == D3DERR_DEVICENOTRESET)
				{
					OnLostDevice();
					OnResetDevice();
				}
			}
			else
			{
				// ���� ����̽��� ����� �� �ִٸ�
				// ���� ����̽� �ս� ���¸� �ʱ�ȭ���ݴϴ�.
				m_bLostDevice = false;
			}
		}

		return S_OK;
	}

	HRESULT RXMain_DX9::BeginRender()
	{
		m_pD3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_clearColor, 1.0f, 0);
		m_pD3DDevice9->BeginScene();
		return S_OK;
	}

	HRESULT RXMain_DX9::EndRender()
	{
		m_pD3DDevice9->EndScene();
		return S_OK;
	}

	HRESULT RXMain_DX9::OnLostDevice()
	{
		if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::LOSTDEVICE)].func()))
		{
			RXERRLOG_EFAIL_RETURN("���� �ν�Ʈ ����̽� ����!");
		}

		RXLOG(false, "�ν�Ʈ ����̽�!");
		return S_OK;
	}

	HRESULT RXMain_DX9::OnResetDevice()
	{
		D3DPRESENT_PARAMETERS D3DPP;
		::ZeroMemory(&D3DPP, sizeof(D3DPP));

		VerifyDevice(&D3DPP);

		D3DPP.EnableAutoDepthStencil = true;
		D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;
		D3DPP.SwapEffect             = D3DSWAPEFFECT_DISCARD;
		D3DPP.Flags                  = 0;
		D3DPP.hDeviceWindow          = m_hMainWnd;
		D3DPP.Windowed               = !m_bFullScreen;

		m_pD3DDevice9->Reset(&D3DPP);

		if (FAILED(m_subFunc[static_cast<INT32>(SUBFUNC_TYPE::RESETDEVICE)].func()))
		{
			RXERRLOG_EFAIL_RETURN("���� ���� ����̽� ����!");
		}

		Sleep(100);

		RXLOG(false, "���� ����̽�!");
		return S_OK;
	}

} // namespace RX end