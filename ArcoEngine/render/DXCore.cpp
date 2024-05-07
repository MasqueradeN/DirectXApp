#include <d3d11.h>
//#include <d3dx11.h>
//#include <dxerr.h>

#include "DXCore.h"


DXCore::DXCore(void)
	: mpD3DDevice(0)
	, mpD3DDeviceContext(0)
	, mpSwapChain(0)
	, mpRenderTargetView(0)
	, mpDepthStencil(0)
	, mpDepthStencilView(0)
{
}

DXCore::~DXCore(void)
{
}

HRESULT DXCore::Initialize(HWND &windowhandler,
	unsigned int width, unsigned int height)
{
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	sd.OutputWindow = windowhandler;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	hr = D3D11CreateDeviceAndSwapChain(
		0, D3D_DRIVER_TYPE_HARDWARE, 0,
		createDeviceFlags, 0, 0,
		D3D11_SDK_VERSION,
		&sd, &mpSwapChain,
		&mpD3DDevice,
		&featureLevel,
		&mpD3DDeviceContext);

	if (FAILED(hr)) { return S_FALSE; } // no device
	if (featureLevel != D3D_FEATURE_LEVEL_11_0) { return S_FALSE; } // no directx 11

	if (FAILED(Initialize3DEnviroment(width, height))) {
		return hr;
	}

	return hr;
}

HRESULT DXCore::Initialize3DEnviroment(unsigned int width, unsigned int height)
{
	HRESULT hr = S_OK;

	ID3D11Texture2D *pBackBuffer;
	hr = mpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr)) { return hr; }

	hr = mpD3DDevice->CreateRenderTargetView(pBackBuffer, 0, &mpRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr)) { return hr; }

	// Crea la textura del depth buffer
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	hr = mpD3DDevice->CreateTexture2D(&descDepth, 0, &mpDepthStencil);
	if (FAILED(hr)) { return hr; }

	// Crea la "view" del depth buffer.
	hr = mpD3DDevice->CreateDepthStencilView(mpDepthStencil, 0, &mpDepthStencilView);
	if (FAILED(hr)) { return hr; }

	mpD3DDeviceContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);

	// Crea el viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mpD3DDeviceContext->RSSetViewports(1, &vp);



	return hr;
}

void DXCore::ClearColor(const float *color)
{
	mpD3DDeviceContext->ClearRenderTargetView(
		mpRenderTargetView, color);
	mpD3DDeviceContext->ClearDepthStencilView(
		mpDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DXCore::Present()
{
	mpSwapChain->Present(0, 0);
}


HRESULT DXCore::Close()
{
	if (mpRenderTargetView) { mpRenderTargetView->Release(); }
	if (mpDepthStencil) { mpDepthStencil->Release(); }
	if (mpDepthStencilView) { mpDepthStencilView->Release(); }
	if (mpSwapChain) { mpSwapChain->Release(); }
	if (mpD3DDeviceContext) { mpD3DDeviceContext->Release(); }
	if (mpD3DDevice) { mpD3DDevice->Release(); }

	return S_OK;
}