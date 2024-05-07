#pragma once
#include <windows.h>

#define WIN32_LEAN_AND_MEAN

class WinApplication
{
public:
	WinApplication(void);
	virtual ~WinApplication(void);
	
	HINSTANCE &GetAppInstance()		{ return appInstance;	}
	HWND &GetAppHwnd()						{ return appWindow;		}

protected:
	virtual void GetWindowDims( long &width, long &height )		{ width = 680; height = 680; }
	virtual LPCWSTR GetWinTitle()															{ return L"Arcos Engine"; }

	virtual bool AppPreBegin()	{ return true; }
	virtual bool AppBegin()			{ return true; }
	virtual bool AppUpdate()		{ return true; }
	virtual bool AppEnd()				{ return true; }

	virtual bool Paint( HWND AppHwnd, WPARAM Wparam, LPARAM Lparam )			{ return false; }
	virtual bool SysCommand( HWND AppHwnd, WPARAM Wparam, LPARAM Lparam );
	
	virtual bool ProcessMessage( UINT msg, WPARAM Wparam, LPARAM Lparam )		{ return false; }

	void CloseWindow();

private:
	HRESULT InitWindow();
	int InternalWinMain(HINSTANCE hInstance);

	friend int WINAPI _tWinMain( HINSTANCE, HINSTANCE, TCHAR *, int );
	static LRESULT CALLBACK WndProc( HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

private:
	static WinApplication *pApp;
	HINSTANCE		appInstance;
	HWND			appWindow;
	const TCHAR		*CLASSNAME;

};
