#include "stdafx.h"
#include <vector>

HINSTANCE	_hInstance;
HWND		_hWnd;

struct Croc
{
	RECT rect;
	COLORREF color;
	bool isClick;
};



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

	RECT winRect = RECT{ 50,50,800,600 };
	AdjustWindowRect(&winRect, WS_CAPTION | WS_SYSMENU, false);

	SetWindowPos(_hWnd, NULL, winRect.left, winRect.right, 
				(winRect.right - winRect.left), 
				(winRect.bottom - winRect.top), 
				SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(_hWnd, cmdShow);

	UpdateWindow(_hWnd);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);

		DispatchMessage(&message);
	}
	return message.wParam;

	
}

// static = 전역 (단 하나만 존재)
static RECT PlayerRect;
static POINT MousePoint;
static COLORREF RectColor;

#define GET_X_LPARAM(lParam) ((int)(short)LOWORD(lParam))
#define GET_Y_LPARAM(lParam) ((int)(short)HIWORD(lParam))

#define WHITE				(COLORREF(RGB(255,255,255)))
#define BLACK				(COLORREF(RGB(0,0,0)))
#define RED					(COLORREF(RGB(255,0,0)))
#define GREEN				(COLORREF(RGB(0, 255,0)))
#define BLUE				(COLORREF(RGB(0,0,255)))
#define MAGENTAR			(COLORREF(RGB(255,0,255)))
#define MAKE_COLOR(r,g,b)	(COLORREF(RGB(r,g,b)))



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	switch (iMessage)
	{
	case WM_CREATE: // 윈도우 생성 시 한번만 호출
	{
		PlayerRect = MakeRect(50, 0, 100, 150);
	

	} break;

	case WM_KEYDOWN: // 아무 키를 눌렀을 때
	{
		switch (wParam)
		{
		case VK_LEFT:
			PlayerRect.left -= 5;
			PlayerRect.right -= 5;
			
			// 그리는 작업을 다시 부탁
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_RIGHT:
			PlayerRect.left += 5;
			PlayerRect.right += 5;

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_UP:
			PlayerRect.top -= 5;
			PlayerRect.bottom -= 5;

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_DOWN:
			PlayerRect.top += 5;
			PlayerRect.bottom += 5;

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		default:
			break;
		}
	}break;

	case WM_MOUSEMOVE:
	{

		MousePoint.x = GET_X_LPARAM(lParam);
		MousePoint.y = GET_Y_LPARAM(lParam);
	}break;

	case WM_LBUTTONDOWN: // 마우스좌클릭
	{
		
		if (PlayerRect.left <= MousePoint.x && PlayerRect.top <= MousePoint.y &&
			PlayerRect.right >= MousePoint.x && PlayerRect.bottom )
		{
			RectColor = MAKE_COLOR(rand() % 256, rand() % 256, rand() % 256);
			PlayerRect = MakeRectCenter(rand() % 701, rand() % 502, 100, 100);
		}

#pragma region 플레이어 렉트가 화면 밖으로 안나가게 하는 공식
		/*PlayerRect = MakeRectCenter(MousePoint.x, MousePoint.y, 100, 100);

		if (PlayerRect.left < 0 && PlayerRect.top < 0)
		PlayerRect = MakeRectCenter(50, 50, 100, 100);

		else if (PlayerRect.right > 750 && PlayerRect.top < 0)
			PlayerRect = MakeRectCenter(700, 50, 100, 100);
		
		else if (PlayerRect.left < 0 && PlayerRect.bottom > 550)
			PlayerRect = MakeRectCenter(50, 500, 100, 100);
		
		else if (PlayerRect.right > 750 && PlayerRect.bottom > 550)
			PlayerRect = MakeRectCenter(700, 500, 100, 100);


		else if (PlayerRect.left < 0)
			PlayerRect = MakeRectCenter(50, MousePoint.y, 100, 100);

		else if (PlayerRect.top < 0)
			PlayerRect = MakeRectCenter(MousePoint.x, 50, 100, 100);

		else if (PlayerRect.right > 750)
			PlayerRect = MakeRectCenter(700, MousePoint.y, 100, 100);

		else if (PlayerRect.bottom > 550)
			PlayerRect = MakeRectCenter(MousePoint.x, 500, 100, 100);*/

#pragma endregion


		InvalidateRect(hWnd, NULL, TRUE);

	}break;

	case WM_LBUTTONUP:
	{
		
	}break;

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
	
	HBRUSH hBrush = CreateSolidBrush(RectColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	SelectObject(hdc, hBrush);
	DrawRect(hdc, PlayerRect);



	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);


	EndPaint(_hWnd, &ps);

}

