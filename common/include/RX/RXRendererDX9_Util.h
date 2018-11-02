/*====================================================================================
*
* Copyright (C) Ruvendix. All Rights Reserved.
*
* <�ۼ� ��¥>
* 2018-10-16
*
* <���� ����>
* DirectX9 �������� ���� �Լ��Դϴ�.
*
====================================================================================*/
#ifndef RXRENDERERDX9_UTILITY_H__
#define RXRENDERERDX9_UTILITY_H__

namespace RX
{

	INT32        CalcPrimitiveCount(D3DPRIMITIVETYPE primitiveType, INT32 vertexCnt);
	INT32        FindAdapterIndex(const HWND hWnd);
	bool         AdjustFullScreenInfo(INT32 adapterIdx, D3DPRESENT_PARAMETERS* pD3DPP,
		                             const D3DDISPLAYMODE& mainDisplayMode);
	bool         AdjustMSAAInfo(INT32 adapterIdx, D3DPRESENT_PARAMETERS* pD3DPP);
	bool         AdjustDepthStencilInfo(INT32 adapterIdx, D3DPRESENT_PARAMETERS* pD3DPP,
	                                   INT32 depthBits, INT32 stencilBits);
	bool         CheckAvailableAllDXT(INT32 adapterIdx, D3DFORMAT surfaceFormat);
	const TCHAR* ConvertD3DFORMATToString(D3DFORMAT surfaceFormat);
	const TCHAR* ConvertD3DXIMAGE_FILEFORMATToString(D3DXIMAGE_FILEFORMAT fileFormat);
	void         PrintD3DPresentParameters(const D3DPRESENT_PARAMETERS& D3DPP);

} // namespace RX end

#endif