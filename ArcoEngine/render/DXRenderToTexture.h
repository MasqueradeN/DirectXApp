#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilView;

class DXRenderToTexture
{
public:
	DXRenderToTexture(void);
	~DXRenderToTexture(void);

	bool Initialize(ID3D11Device *device,
		unsigned int width, unsigned int height);

	void SetRenderTarget(
		ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthStencilView);
	void ClearRenderTarget(
		ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthStencilView,
		float red, float green, float blue);
	ID3D11ShaderResourceView* GetShaderResourceView() { return m_RTTshaderResourceView; }

private:
	ID3D11Texture2D* m_RTTTexture2D;
	ID3D11RenderTargetView* m_RTTTargetView;
	ID3D11ShaderResourceView* m_RTTshaderResourceView;

};
