#include <d3d11.h>
#include "DXRenderToTexture.h"


DXRenderToTexture::DXRenderToTexture(void)
{
}

DXRenderToTexture::~DXRenderToTexture(void) 
{
	if (m_RTTshaderResourceView) {
		m_RTTshaderResourceView->Release();
		m_RTTshaderResourceView = 0;
	}

	if (m_RTTTargetView) {
		m_RTTTargetView->Release();
		m_RTTTargetView = 0;
	}

	if (m_RTTTexture2D) {
		m_RTTTexture2D->Release();
		m_RTTTexture2D = 0;
	}
}

bool DXRenderToTexture::Initialize(ID3D11Device *device,
	unsigned int width, unsigned int height)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	HRESULT result;
	result = device->CreateTexture2D(&textureDesc, NULL, &m_RTTTexture2D);
	if (FAILED(result)) {
		return false;
	}

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	result = device->CreateRenderTargetView(
		m_RTTTexture2D, &renderTargetViewDesc, &m_RTTTargetView);
	if (FAILED(result)) {
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	result = device->CreateShaderResourceView(
		m_RTTTexture2D, &shaderResourceViewDesc, &m_RTTshaderResourceView);
	if (FAILED(result)) {
		return false;
	}

	return true;
}

void DXRenderToTexture::SetRenderTarget(
	ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthStencilView)
{
	deviceContext->OMSetRenderTargets(1, &m_RTTTargetView, depthStencilView);
}

void DXRenderToTexture::ClearRenderTarget(
	ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthStencilView,
	float red, float green, float blue)
{
	float color[4] = { red, green, blue, 1.f };
	deviceContext->ClearRenderTargetView(m_RTTTargetView, color);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}


