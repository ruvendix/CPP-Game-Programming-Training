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

namespace RX
{

	class DLL_DEFINE RXMain_DX9 : public RXMain
	{
	public:
		RXMain_DX9();
		virtual ~RXMain_DX9();

		virtual HRESULT InitMain()     override;
		virtual HRESULT InitD3D9();
		virtual HRESULT DriveMain() override;
		virtual HRESULT Release()   override;
		virtual HRESULT ResizeResolution(INT32 clientWidth, INT32 clientHeight) override;
		virtual HRESULT ToggleFullScreenMode(bool bFullScreen = false) override;

		// ====================================================================================
		// ���� ����
		virtual HRESULT Update();
		HRESULT Render(FLOAT rInterpolation);

		// ====================================================================================
		// ���� ����̽� ���¿� ���� ó�� �Լ�
		HRESULT OnLostDevice();
		HRESULT OnResetDevice();
		HRESULT OnRecreateDevice();
	};

} // namespace RX end

#endif