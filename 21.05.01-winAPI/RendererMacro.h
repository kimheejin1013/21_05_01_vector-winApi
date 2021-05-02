#pragma once


inline RECT MakeRect(int x, int y, int width, int height)
{
	RECT rect = { x, y, x + width, y + height };

	return rect;

}

inline RECT MakeRectCenter(int x, int y, int width, int height)
{
	RECT rect = { x - (width/2), y - (height/2), 
				  x + (width/2), y + (height/2)};

	return rect;
}


//	Overloading
inline void DrawRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);

}

inline void DrawRect(HDC hdc, const RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

inline void DrawCircle(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void DrawCircleCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2),
				 x + (width / 2), y + (height / 2));
}