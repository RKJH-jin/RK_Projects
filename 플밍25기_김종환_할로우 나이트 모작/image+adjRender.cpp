#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::adjRender(HDC hdc, int destX, int destY, int adjWidth, int adjHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의  DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			adjWidth,				//복사될 크기 (가로)
			adjHeight,				//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 좌표 X, Y
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_transColor
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(
			hdc,					//복사할 DC
			destX,					//복사할 좌표 X (left)
			destY,					//복사할 좌표 Y (top)
			adjWidth,				//조절할 width
			adjHeight,				//조절할 height
			_imageInfo->hMemDC,		//복사될 DC
			0, 0,					//복사될 기준점 (left, top)
			_imageInfo->width,		//이미지 크기
			_imageInfo->height,
			SRCCOPY);				//변형없이 복사할거임
	}
}

void image::adjFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			adjWidth,					//복사될 크기 (가로)
			adjHeight,					//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_transColor
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc,
			destX,
			destY,
			adjWidth,
			adjHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			SRCCOPY
		);
	}
}



