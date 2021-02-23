#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
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
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,						//복사할 DC
			destX,						//복사할 좌표 X (left)
			destY,						//복사할 좌표 Y (top)
			_imageInfo->frameWidth,			//복사할 크기
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 기준점 (left, top)
			SRCCOPY);					//변형없이 복사할거임
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
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
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,						//복사할 DC
			destX,						//복사할 좌표 X (left)
			destY,						//복사할 좌표 Y (top)
			_imageInfo->frameWidth,		//복사할 크기
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 기준점 (left, top)
			SRCCOPY);					//변형없이 복사할거임
	}
}