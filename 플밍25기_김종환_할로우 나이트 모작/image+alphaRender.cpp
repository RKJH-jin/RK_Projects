#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,					//복사될 영역의  DC
			0,						//복사될 좌표 X
			0,						//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			hdc,		//복사해올 DC
			_imageInfo->x,
			_imageInfo->y,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사될 영역의  DC
			0,						//복사될 좌표 X
			0,						//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_transColor
		);

		AlphaBlend(
			hdc,					//복사될 영역의  DC
			_imageInfo->x,			//복사될 좌표 X
			_imageInfo->y,			//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_blendImage->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,					//복사될 영역의  DC
			_imageInfo->x,			//복사될 좌표 X
			_imageInfo->y,			//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_blendFunc
		);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,		//복사될 영역의  DC
			0,							//복사될 좌표 X
			0,							//복사될 좌표 Y
			_imageInfo->width,			//복사될 크기 (가로)
			_imageInfo->height,			//복사될 크기 (세로)
			hdc,						//복사해올 DC
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,		//복사될 영역의  DC
			0,							//복사될 좌표 X
			0,							//복사될 좌표 Y
			_imageInfo->width,			//복사될 크기 (가로)
			_imageInfo->height,			//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			0,
			0,
			_imageInfo->width,			//복사할 가로크기
			_imageInfo->height,			//복사할 세로크기
			_transColor
		);

		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->width,			//복사될 크기 (가로)
			_imageInfo->height,			//복사될 크기 (세로)
			_blendImage->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->width,			//복사할 가로크기
			_imageInfo->height,			//복사할 세로크기
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,					//복사될 영역의  DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_blendFunc
		);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			sourWidth,					//복사될 크기 (가로)
			sourHeight,					//복사될 크기 (세로)
			hdc,						//복사해올 DC
			sourX,
			sourY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			sourWidth,					//복사될 크기 (가로)
			sourHeight,					//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			sourX,
			sourY,
			sourWidth,					//복사할 가로크기
			sourHeight,					//복사할 세로크기
			_transColor
		);

		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			sourWidth,					//복사될 크기 (가로)
			sourHeight,					//복사될 크기 (세로)
			_blendImage->hMemDC,			//복사해올 DC
			sourX,
			sourY,
			sourWidth,					//복사할 가로크기
			sourHeight,					//복사할 세로크기
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			sourWidth,					//복사될 크기 (가로)
			sourHeight,					//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			sourX,
			sourY,
			sourWidth,					//복사할 가로크기
			sourHeight,					//복사할 세로크기
			_blendFunc
		);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,						//복사될 영역의  DC
			0,						//복사될 좌표 X
			0,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			hdc,						//복사해올 DC
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,						//복사될 영역의  DC
			0,						//복사될 좌표 X
			0,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->frameWidth * _imageInfo->currentFrameX,
			_imageInfo->frameHeight * _imageInfo->currentFrameY,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_transColor
		);

		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_blendImage->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->frameWidth * _imageInfo->currentFrameX,
			_imageInfo->frameHeight * _imageInfo->currentFrameY,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_blendFunc
		);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,		//복사될 영역의  DC
			0,							//복사될 좌표 X
			0,							//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			hdc,						//복사해올 DC
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,		//복사될 영역의  DC
			0,						//복사될 좌표 X
			0,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_transColor
		);

		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_blendImage->hMemDC,		//복사해올 DC
			0,
			0,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->frameWidth * _imageInfo->currentFrameX,
			_imageInfo->frameHeight * _imageInfo->currentFrameY,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_blendFunc
		);
	}
}