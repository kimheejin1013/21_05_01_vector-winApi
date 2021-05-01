#include "stdafx.h"

HINSTANCE	_hInstance;
HWND		_hWnd;

#define ApplicationName L"Windows API Example"
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void DrawRect(HDC hdc, int x, int y, int width, int height);

void Render();


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrecINstane,
					LPSTR IpszCmdParam, int cmdShow)

{
	MSG message;
	WNDCLASS wc;

	UNREFERENCED_PARAMETER(IpszCmdParam);

	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = ApplicationName;
	wc.lpszMenuName = nullptr;


	if (!RegisterClass(&wc)) return FALSE;
	// false 랑 FALSE 차이x c언어에서 bool이 없어서 그럼

	_hInstance = hInstance;



	_hWnd = CreateWindow(
		ApplicationName,
		ApplicationName,
		WS_OVERLAPPEDWINDOW,
		50,
		50,
		800,
		600,
		nullptr, nullptr, hInstance, nullptr);

	if (!_hWnd) return FALSE;

	ShowWindow(_hWnd, cmdShow);

	UpdateWindow(_hWnd);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);

		DispatchMessage(&message);
	}
	return message.wParam;

	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_PAINT:
	{
		Render();
	}break;

	case WM_CLOSE: case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}

void Render()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(_hWnd, &ps);
	
	Rectangle(hdc, 50, 50, 150, 100);

	Ellipse(hdc, 50, 100, 75, 125);
	Ellipse(hdc, 125, 100, 150, 125);

	EndPaint(_hWnd, &ps);

}

void DrawRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}