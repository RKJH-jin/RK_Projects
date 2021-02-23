#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	//size = getDistance(0, 0, _imageInfo->width, _imageInfo->height); // 0, 0부터(이미지가 그려지기 시작하는 위치)부터 이미지 중점까지의 거리

	HDC hWDC = GetDC(_hWnd);

	HDC destDC = CreateCompatibleDC(hWDC);
	HBITMAP hBitResult = CreateCompatibleBitmap(hWDC, size, size);
	HBITMAP destHOBit = (HBITMAP)SelectObject(destDC, hBitResult);

	HBRUSH backBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBackBrush = (HBRUSH)SelectObject(destDC, backBrush);
	PatBlt(destDC, 0, 0, size, size, PATCOPY);
	DeleteObject(SelectObject(destDC, oldBackBrush));

	float cosine = cosf(angle);
	float sine = sinf(angle);

	SetGraphicsMode(destDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = sine;
	xform.eM21 = -sine;
	xform.eM22 = cosine;
	xform.eDx = size / 2;
	xform.eDy = size / 2;

	SetWorldTransform(destDC, &xform);

	cosf(angle)* (-size / 2) + sinf(angle) * (-size / 2);
	-sinf(angle) * (-size / 2) + cosf(angle) * (-size / 2);

	BitBlt(destDC, -_imageInfo->width / 2, -_imageInfo->height / 2, size, size, _imageInfo->hMemDC, 0, 0, SRCCOPY);

	SelectObject(destDC, destHOBit);
	DeleteObject(destDC);


	static HDC hTempMemDC; // 회전한 비트맵을 선택할 메모리DC
	HBITMAP hTempBitmap, hOldBitmap; // 회전한 비트맵을 저장할, 비트맵 핸들

	if (!hTempMemDC) hTempMemDC = CreateCompatibleDC(hdc);

	hOldBitmap = (HBITMAP)SelectObject(hTempMemDC, hBitResult);

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의  DC
			centerX - size / 2,						//복사될 좌표 X
			centerY - size / 2,						//복사될 좌표 Y
			size,					//복사될 크기 (가로)
			size,					//복사될 크기 (세로)
			hTempMemDC,		//복사해올 DC
			0, 0,					//복사해올 좌표 X, Y
			size,		//복사할 가로크기
			size,		//복사할 세로크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,					//복사할 DC
			centerX - size / 2,					//복사할 좌표 X (left)
			centerY - size / 2,					//복사할 좌표 Y (top)
			size,					//복사할 크기
			size,
			hTempMemDC,				//복사될 DC
			0, 0,					//복사될 기준점 (left, top)
			SRCCOPY);				//변형없이 복사할거임
	}

	SelectObject(hTempMemDC, hOldBitmap);
	DeleteObject(hBitResult);
}

void image::rotateRender2(HDC hdc, float centerX, float centerY, float angle)
{
	HDC hWDC = GetDC(_hWnd);

	HDC destDC = CreateCompatibleDC(hWDC);
	HBITMAP hBitResult = CreateCompatibleBitmap(hWDC, size, size);
	HBITMAP destHOBit = (HBITMAP)SelectObject(destDC, hBitResult);

	POINT pt[3];
	float dist = getDistance(0, 0, _imageInfo->width / 2, _imageInfo->height / 2);
	float baseAngle[3];
	float temp = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[0] = PI - temp;
	baseAngle[1] = temp;
	baseAngle[2] = PI + temp;

	for (int i = 0; i < 3; ++i)
	{
		pt[i].x = (size / 2 + cosf(baseAngle[i] + angle) * dist);
		pt[i].y = (size / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_trans)
	{
		BitBlt(destDC, 0, 0, size, size, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(destDC, hBrush);
		ExtFloodFill(destDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(destDC, pt, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - size / 2,
			centerY - size / 2,
			size,
			size,
			destDC,
			0,
			0,
			size,
			size,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, pt, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}

}
