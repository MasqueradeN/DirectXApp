#pragma once
#include <wrl/client.h>

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

//class Renderer;

class Mouse
{
public:
	/// Constructor
	Mouse();
	~Mouse();

	/// Initialization / shutdown
	//bool Initialize(Renderer* inWindow);
	bool Initialize(HWND winHandle);// Renderer* inWindow);
	void Shutdown();
			 
			 
	void Poll();
			 
	int	 GetX() const { return mMousePos.x; }
	int	 GetY() const { return mMousePos.y; }
	int	 GetDX() const { return mMouseState.lX; }
	int	 GetDY() const { return mMouseState.lY; }
			 
	bool IsLeftPressed() const { return (mMouseState.rgbButtons[0] & 0x80) != 0; }
	bool IsRightPressed() const { return (mMouseState.rgbButtons[1] & 0x80) != 0; }
	bool IsMiddlePressed() const { return (mMouseState.rgbButtons[2] & 0x80) != 0; }
			 
	bool IsLeftDoubleClicked() const { return mLeftButtonDoubleClicked; }
			 
	void HideCursor();
	void ShowCursor();
			 
	void SetExclusive(bool inExclusive = true);
			 
private:

	void Reset();
	void ResetMouse();

	enum
	{
		BUFFERSIZE = 64,								///< Number of keys cached
		DCLICKTIME = 300								///< Minimum time between key release and key down to make it a double click
	};

	//Renderer* mRenderer;
	HWND mWindowHandle;

	Microsoft::WRL::ComPtr<IDirectInput8> mDI;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mMouse;

	DIMOUSESTATE			mMouseState;
	bool							mMousePosInitialized = false;
	POINT							mMousePos;
	DIDEVICEOBJECTDATA				mDOD[BUFFERSIZE];
	DWORD							mDODLength;
	int								mTimeLeftButtonLastReleased;
	bool							mLeftButtonDoubleClicked;
};
