//#include <TestFramework.h>
#include "Mouse.h"
//#include <Renderer/Renderer.h>
//#include <Jolt/Core/Profiler.h>

Mouse::Mouse()
{
	Reset();
}

Mouse::~Mouse()
{
	Shutdown();
}

void
Mouse::Reset()
{
	mDI = nullptr;
	mMouse = nullptr;
	mMousePos.x = 0;
	mMousePos.y = 0;

	ResetMouse();
}

void Mouse::ResetMouse()
{
	memset(&mMouseState, 0, sizeof(mMouseState));
	mMousePosInitialized = false;
	memset(&mDOD, 0, sizeof(mDOD));
	mDODLength = 0;
	mTimeLeftButtonLastReleased = 0;
	mLeftButtonDoubleClicked = false;
}

bool Mouse::Initialize(HWND winHandle)// Renderer* inRenderer)
{
	// Store renderer
	//mRenderer = inRenderer;
	mWindowHandle = winHandle;

	// Create direct input interface
	if (FAILED(CoCreateInstance(CLSID_DirectInput8, nullptr, CLSCTX_INPROC_SERVER, IID_IDirectInput8W, (void**)&mDI)))
	{
		return false;
	}

	// Initialize direct input interface
	if (FAILED(mDI->Initialize((HINSTANCE)GetModuleHandle(nullptr), DIRECTINPUT_VERSION)))
	{		
		return false;
	}

	// Create Mouse device
	if (FAILED(mDI->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
	{		
		return false;
	}

	// Set cooperative level for Mouse
	SetExclusive(false);

	// Set data format
	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}

	// Create a mouse buffer
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = BUFFERSIZE;
	if (FAILED(mMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
	{
		return false;
	}

	return true;
}

void Mouse::Shutdown()
{
	if (mMouse)
	{
		mMouse->Unacquire();
		mMouse = nullptr;
	}

	mDI = nullptr;

	Reset();
}

void Mouse::Poll()
{
	// Remember last position
	POINT old_mouse_pos = mMousePos;

	// Get mouse position using the standard window call
	if (!GetCursorPos(&mMousePos))
	{
		ResetMouse();
		return;
	}

	// If we lost mouse before, we need to reset the old mouse pos to the current one
	if (!mMousePosInitialized)
	{
		old_mouse_pos = mMousePos;
		mMousePosInitialized = true;
	}

	// Convert to window space
	//if (!ScreenToClient(mRenderer->GetWindowHandle(), &mMousePos))
	//{
	//	ResetMouse();
	//	return;
	//}
	
	if (!ScreenToClient(mWindowHandle, &mMousePos))
	{
		ResetMouse();
		return;
	}
	
	// Get relative movement
	if (FAILED(mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState)))
	{
		// Mouse input was lost, reacquire
		mMouse->Acquire();

		if (FAILED(mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState)))
		{
			ResetMouse();
			return;
		}
	}

	// If we're connected through remote desktop then GetDeviceState returns faulty data for lX and lY so we need to use a fallback
	if (GetSystemMetrics(SM_REMOTESESSION))
	{
		// Just use the delta between the current and last mouse position.
		// Note that this has the disadvantage that you can no longer rotate any further if you're at the edge of the screen,
		// but unfortunately a RDP session doesn't allow capturing the mouse so there doesn't seem to be a workaround for this.
		mMouseState.lX = mMousePos.x - old_mouse_pos.x;
		mMouseState.lY = mMousePos.y - old_mouse_pos.y;
	}

	// Get the state in a buffer for checking doubleclicks
	if (FAILED(mMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mDOD, &mDODLength, 0)))
	{
		// We lost mMouse input, reacquire
		mMouse->Acquire();

		if (FAILED(mMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mDOD, &mDODLength, 0)))
		{
			// Unable to reacquire, reset button info
			mTimeLeftButtonLastReleased = 0;
			mLeftButtonDoubleClicked = false;
			return;
		}
	}

	// Check for double clicks
	for (DWORD d = 0; d < mDODLength; d++)
	{
		// Check if this means left button is pressed
		if (mDOD[d].dwOfs == DIMOFS_BUTTON0)
		{
			if (mDOD[d].dwData & 0x80)
			{
				if (mDOD[d].dwTimeStamp - mTimeLeftButtonLastReleased <= DCLICKTIME)
				{
					// This is a double click
					mTimeLeftButtonLastReleased = 0;
					mLeftButtonDoubleClicked = true;
				}
			}
			else // Remember last time button was released
				mTimeLeftButtonLastReleased = mDOD[d].dwTimeStamp;
		}
	}
}

void Mouse::HideCursor()
{
	::ShowCursor(false);
}

void Mouse::ShowCursor()
{
	::ShowCursor(true);
}

void Mouse::SetExclusive(bool inExclusive)
{
	mMouse->SetCooperativeLevel(mWindowHandle, (inExclusive ? DISCL_EXCLUSIVE : DISCL_NONEXCLUSIVE) | DISCL_FOREGROUND);
	// Set cooperative level for Mouse
	//if (FAILED(mMouse->SetCooperativeLevel(mRenderer->GetWindowHandle(), (inExclusive ? DISCL_EXCLUSIVE : DISCL_NONEXCLUSIVE) | DISCL_FOREGROUND)))
	//	Trace("Failed to set cooperative level for mouse");
}
