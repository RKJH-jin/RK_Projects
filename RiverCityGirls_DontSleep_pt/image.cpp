#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}

image::~image()
{
}

HRESULT image::init(int width, int height, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	if (alpha)
	{
		//알파블렌드 설정
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//특정 칼라값을 날릴지 여부

	_transColor = transColor;	//그 날릴 칼라값
	if (alpha)
	{
		//알파블렌드 설정
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값

	if (alpha)
	{
		//알파블렌드 설정
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값


	if (alpha)
	{
		//알파블렌드 설정
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);

	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값
}

/*====================================================================
	Left Top을 기준으로 0, 0에 그리는 렌더. 배경 등을 그릴 때 사용한다.
====================================================================*/
void image::render(HDC hdc)
{
	render(hdc, _imageInfo->width / 2, _imageInfo->height / 2);
}

/*====================================================================
	이미지를 잘라서 Left Top을 기준으로 렌더. (Loop Render에서 사용)
====================================================================*/
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의  DC
			destX, destY,			//복사될 좌표
			sourW, sourH,			//복사될 크기
			_imageInfo->hMemDC,		//복사해올 DC
			sourX, sourY,			//복사해올 좌표
			sourW, sourH,			//복사할 크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,					//복사할 DC
			destX, destY,			//복사될 좌표 Y
			sourW, sourH,			//복사할 크기
			_imageInfo->hMemDC,		//복사될 DC
			sourX, sourY,			//복사될 기준점
			SRCCOPY);				//변형없이 복사할거임
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int alpha)
{
	//실제 이미지 소스에 알파블렌드를 적용 시켜주는 함수 BYTE == 투명도 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth,
			sourHeight, _blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth,
			sourHeight, _blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight, _blendFunc);
	}
}

/*====================================================================
	이미지를 잘라서 Left Top을 기준으로 렌더. (Camera Map에서 사용)
====================================================================*/
void image::render(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//복사될 영역의  DC
			destX, destY,			//복사될 좌표
			destW, destH,			//복사될 크기
			_imageInfo->hMemDC,		//복사해 올 DC
			sourX, sourY,			//복사해 올 좌표
			sourW, sourH,			//복사할 세로크기
			_transColor				//변환할 색상
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);

		StretchBlt(
			hdc,					//복사될 영역의 DC
			destX, destY,			//복사될 좌표
			destW, destH,			//복사될 크기
			_imageInfo->hMemDC,		//복사해 올 DC
			sourX, sourY,			//복사해 올 좌표
			sourW, sourH,			//복사할 크기
			SRCCOPY);				//변형 없이 복사할거임
	}
}
/*====================================================================
	중점 기준으로 그려질 위치를 정하는 렌더.
====================================================================*/

//일반 렌더
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,											//복사될 영역의  DC
			destX - _imageInfo->width / 2, destY - _imageInfo->height / 2,	//복사될 X, Y 좌표
			_imageInfo->width, _imageInfo->height,						//복사될 가로, 세로 크기
			_imageInfo->hMemDC,											//복사해올 DC
			0, 0,														//복사해올 좌표 X, Y
			_imageInfo->width, _imageInfo->height,						//복사할 가로, 세로 크기
			_transColor													//변환할 색깔
		);
	}
	else
	{
		BitBlt(hdc,															//복사할 DC
			destX - _imageInfo->width / 2, destY - _imageInfo->height / 2,	//복사될 X, Y 좌표
			_imageInfo->width, _imageInfo->height,							//복사될 가로, 세로 크기
			_imageInfo->hMemDC,												//복사될 DC
			0, 0,															//복사해 올 X, Y 좌표
			SRCCOPY);														//변형 없이 복사할거임
	}
}

//알파 렌더
void image::render(HDC hdc, int destX, int destY, int alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX - _imageInfo->width / 2, destY - _imageInfo->height / 2, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		AlphaBlend(hdc, destX - _imageInfo->width / 2, destY - _imageInfo->height / 2, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX - _imageInfo->width / 2, destY - _imageInfo->height / 2, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//비율 렌더
void image::render(HDC hdc, int destX, int destY, float ratioX, float ratioY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//복사될 영역의  DC
			destX - _imageInfo->width / 2,		//복사될 좌표 X
			destY - _imageInfo->height / 2,		//복사될 좌표 Y
			_imageInfo->width * ratioX,			//복사할 가로크기
			_imageInfo->height * ratioY,		//복사할 세로크기
			_imageInfo->hMemDC,					//복사해올 DC
			0, 0,								//복사해올 좌표 X, Y
			_imageInfo->width,					//복사할 가로크기
			_imageInfo->height,					//복사할 세로크기
			_transColor
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);

		StretchBlt(hdc,							//복사할 DC
			destX - _imageInfo->width / 2,		//복사될 좌표 X
			destY - _imageInfo->height / 2,		//복사될 좌표 Y
			_imageInfo->width * ratioX,			//복사할 가로크기
			_imageInfo->height * ratioY,		//복사할 세로크기
			_imageInfo->hMemDC,					//복사될 DC
			0, 0,								//복사해올 좌표 X, Y
			_imageInfo->width,					//복사할 가로크기
			_imageInfo->height,					//복사할 세로크기
			SRCCOPY);							//변형없이 복사할거임
	}
}

/*====================================================================
	중점 기준으로 프레임을 그리는 프레임 렌더
====================================================================*/

//일반 렌더
void image::frameRender(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	_imageInfo->currentFrameX = frameX;
	_imageInfo->currentFrameY = frameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,			//복사될 영역의  DC
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,	//복사될 좌표
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
		BitBlt(hdc,									//복사할 DC
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,	//복사될 좌표
			_imageInfo->frameWidth,					//복사할 크기
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,						//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 기준점 (left, top)
			SRCCOPY);								//변형없이 복사할거임
	}
}

//알파 렌더
void image::frameRender(HDC hdc, int destX, int destY, int frameX, int frameY, int alpha)
{
	_imageInfo->currentFrameX = frameX;
	_imageInfo->currentFrameY = frameY;

	//실제 이미지 소스에 알파블렌드를 적용 시켜주는 함수 BYTE == 투명도 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight / 2, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight / 2, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight / 2, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

/*====================================================================
	중점 기준으로 애니메이션을 그리는 애니 렌더
====================================================================*/

//일반 렌더
void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX - ani->getFrameWidth() / 2, destY - ani->getFrameWidth() / 2,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

//알파 렌더
void image::aniRender(HDC hdc, int destX, int destY, animation * ani, int alpha)
{
	render(hdc, destX - ani->getFrameWidth() / 2, destY - ani->getFrameWidth() / 2,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}


/*====================================================================
	렉트의 Left Top을 기준으로 한 루프 렌더
====================================================================*/
void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//범위를 구하자
	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//그려와야할 영역만큼을 구해줌
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//그려올 영역 구해줌
		sourHeight = rcSour.bottom - rcSour.top;

		//다시 뿌려야할 영역을 세팅해서 렌더로 뿌릴 예정임.
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//그려와야할 영역만큼을 구해줌
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}
