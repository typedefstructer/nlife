#include<windows.h>
#include"common_types.h"

global b32 AppRunning;

LRESULT CALLBACK Win32WindowProcedure(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;
	switch(Message)
	{
		case WM_CLOSE:
		{
			AppRunning = false;
		} break;

		default:
		{
			Result = DefWindowProc(Window, Message, WParam, LParam);
		} break
	}
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow)
{
	WNDCLASSEX WindowClass = {};
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = Win32WindowProcedure;
	WindowClass.hInstance = Instance;
	WindowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);		
	WindowClass.lpszClassName = "NLIFEWINDOWCLASS";

	RegisterClassEx(&WindowClass);

	HWND Window = CreateWindowEx(0,
								 WindowClass.lpszClassName,
								 "nlife game",
								 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								 CW_USEDEFAULT,
								 CW_USEDEFAULT,
								 CW_USEDEFAULT,
								 CW_USEDEFAULT,
								 0,
								 0,
								 Instance,
								 0);

	AppRunning = true;
	MSG Message;	
	while(AppRunning)
	{
		while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	
	return 0;
}
