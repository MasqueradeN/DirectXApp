#ifndef DXCORE_H
#define DXCORE_H

struct ID3D11Device;
struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilView;

class DXCore
{
public:
	DXCore(void);
	virtual ~DXCore(void);

	HRESULT Initialize(HWND &windowhandler, 
		unsigned int width, unsigned int height);

	HRESULT Close();	


	ID3D11Device *Get3DDevice()										{ return mpD3DDevice;	}
	ID3D11DeviceContext *GetDeviceContext()				{ return mpD3DDeviceContext; }
	IDXGISwapChain *GetSwapChain()								{ return mpSwapChain;	}
	ID3D11RenderTargetView *GetRenderTargetView()	{ return mpRenderTargetView;	}
	ID3D11DepthStencilView *GetDepthStencilView()	{ return mpDepthStencilView;	}

	HRESULT Initialize3DEnviroment(unsigned int width, unsigned int height);

	void ClearColor(const float *color);
	void Present();

private:

	ID3D11Device						*mpD3DDevice;
	ID3D11DeviceContext			*mpD3DDeviceContext;
	IDXGISwapChain					*mpSwapChain;
	ID3D11RenderTargetView	*mpRenderTargetView;

	ID3D11Texture2D					*mpDepthStencil;
	ID3D11DepthStencilView	*mpDepthStencilView; 

	ULONG                   m_LastFrameRate;   

	bool                    m_bLostDevice;      
	bool                    m_bActive;          

	ULONG                   m_nViewX;           
	ULONG                   m_nViewY;           
	ULONG                   m_nViewWidth;       
	ULONG                   m_nViewHeight;      

	POINT                   m_OldCursorPos;
};

#endif
