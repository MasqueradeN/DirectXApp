#include "Mouse.h"

Mouse::Mouse()
{
	Reset();
}

Mouse::~Mouse()
{
	Shutdown();
}

bool Mouse::Initialize(HWND winhandle)
{
	mWindowHandle = winhandle;
	if (FAILED(CoCreateInstance(CLSID_DirectInput8, nullptr, CLSCTX_INPROC_SERVER, IID_IDirectInput8W, (void**)&mDI)))
	{
		return false;
	}
	if (FAILED(mDI->Initialize((HINSTANCE)GetModuleHandle(nullptr), DIRECTINPUT_VERSION)))
	{
		return false;
	}
	if (FAILED(mDI->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
	{
		return false;
	}
	SetExclusive(false);

	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = BUFFERSIZE;
	if (FAILED(mMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph)))	return false;

	return true;
}

void Mouse::Shutdown()
{

}

void Mouse::Poll()
{
    POINT old_mouse_pos = mMousePos;
    if (!GetCursorPos(&mMousePos))
    {
        ResetMouse();
        return;
    }
    if (!mMousePosInitialized)
    {
        old_mouse_pos = mMousePos;
        mMousePosInitialized = true;
    }
    if (!ScreenToClient(mWindowHandle, &mMousePos))
    {
        ResetMouse();
        return;
    }
    if (FAILED(mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState)))
    {
        mMouse->Acquire();

        if (FAILED(mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState)))
        {
            ResetMouse();
            return;
        }
    }
    if (GetSystemMetrics(SM_REMOTESESSION))
    {
        mMouseState.lX = mMousePos.x - old_mouse_pos.x;
        mMouseState.lY = mMousePos.y - old_mouse_pos.y;
    }
    if (FAILED(mMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mDOD, &mDODLength, 0)))
    {
        mMouse->Acquire();

        if (FAILED(mMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mDOD, &mDODLength, 0)))
        {
            mTimeLeftButtonLastReleased = 0;
            mLeftButtonDoubleClicked = false;
            return;
        }
    }
    for (DWORD d = 0; d < mDODLength; d++)
    {
        if (mDOD[d].dwOfs == DIMOFS_BUTTON0)
        {
            if (mDOD[d].dwData & 0x80)
            {
                if (mDOD[d].dwTimeStamp - mTimeLeftButtonLastReleased <= DCLICKTIME)
                {
                    mTimeLeftButtonLastReleased = 0;
                    mLeftButtonDoubleClicked = true;
                }
            }
            else
                mTimeLeftButtonLastReleased = mDOD[d].dwTimeStamp;
        }
    }
}

void Mouse::SetExclusive(bool inExclusive)
{
}

void Mouse::Reset()
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
