#pragma once
#include "animation.h"
#define MAGENTA RGB(255,0,255)

class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//리소스 파일로부터
		LOAD_FILE,		//이미지 파일로부터
		LOAD_EMPTY,		//빈 비트맵 이미지를 만들수도 있고
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	//리소스를 불러올때 사용할 ID값
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;			//앵글 먹여야하니까 중점 좌표는 float으로
		float y;
		int width;			//이미지 전체 가로크기
		int height;			//이미지 전체 세로크기
		int currentFrameX;	//현재 가로 프레임 번호(0부터 시작)
		int currentFrameY;	//현재 세로 프레임 번호(0부터 시작)
		int maxFrameX;		//총 몇 장인지
		int maxFrameY;		//총 몇 장인지
		int frameWidth;		//한 프레임 당 가로크기
		int frameHeight;	//한 프레임 당 세로크기
		BYTE loadType;	//이미지 불러올 타입

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;	
	CHAR*			_fileName;		//파일 이름
	BOOL			_trans;			//특정 픽셀값을 제거할지 유무
	COLORREF		_transColor;	//제거할 픽셀값

	BLENDFUNCTION	_blendFunc;		//알파 블렌드에 관한 함수
	LPIMAGE_INFO	_blendImage;	//알파 블렌드 먹일 이미지

public:

	image();
	~image();

	HRESULT init(int width, int height, bool alpha = false);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	HRESULT init(const char* fileName, int width, int height, 
		int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	void release();
	void setTransColor(BOOL trans, COLORREF transColor);

	BLENDFUNCTION getBlendFunc() { return _blendFunc; }


	/*====================================================================
								상위 좌측 기준 렌더
	====================================================================*/

	//렌더 함수 (0,0)에 그림.
	void render(HDC hdc);

	//자른 크기 렌더1 (DC, 그려질 X(left), 그려질Y(top), 가져올X(left) 가져올Y(top), 가져올 가로, 가져올 세로
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//자른 크기 렌더2 (DC, 그려질 X(left), 그려질Y(top), 가져올X(left) 가져올Y(top), 가져올 가로, 가져올 세로, 알파
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int alpha);

	//자른 크기 렌더3 (DC, 왼쪽 X, 위쪽 Y, 그려질 크기, 가져올 X, 가져올 Y, 가져올 가로, 가져올 세로 )
	void render(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH);

	//루프 렌더 (DC, 영역 RC, 오프셋 X, 오프셋 Y)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);


	/*====================================================================
							중점 기준 일반 렌더
	====================================================================*/
	//중점 렌더 (DC, 중점 X, 중점 Y)
	void render(HDC hdc, int destX, int destY);

	//알파 렌더 (DC, 중점 X, 중점 Y, 알파)
	void render(HDC hdc, int destX, int destY, int alpha);

	//비율 렌더 (DC, 중점 X, 중점 Y, 비율 X, 비율 Y)
	void render(HDC hdc, int destX, int destY, float ratioX, float ratioY);

	/*====================================================================
							중점 기준 프레임 렌더
	====================================================================*/
	//프레임 렌더 (DC, 중점 X, 중점 Y, 프레임 X, 프레임 Y)
	void frameRender(HDC hdc, int destX, int destY, int frameX, int frameY);

	//프레임 알파 렌더 (DC, 중점 X, 중점 Y, 프레임 X, 프레임 Y, 알파)
	void frameRender(HDC hdc, int destX, int destY, int frameX, int frameY, int alpha);


	/*====================================================================
							중점 기준 애니 렌더
	====================================================================*/
	//애니 렌더 (DC, 중점 X, 중점 Y, 애니)
	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	//애니 알파 렌더 (DC, 중점 X, 중점 Y, 애니, 알파)
	void aniRender(HDC hdc, int destX, int destY, animation* ani, int alpha);


	// =================== 그 외 ===================

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//===========================================
	// ## 이미지 관련 접근자, 설정자 ##
	//===========================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { if (_imageInfo->frameWidth == 0) return _imageInfo->width;
								else return _imageInfo->frameWidth; }

	inline int getFrameHeight() { if (_imageInfo->frameHeight == 0) return _imageInfo->height;
								else return _imageInfo->frameHeight; }
};

