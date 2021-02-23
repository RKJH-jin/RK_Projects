#pragma once
#include "animation.h"

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
		BYTE loadType;		//이미지 불러올 타입

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

	BLENDFUNCTION	_blendFunc;		//알파 블렌드 함수
	LPIMAGE_INFO	_blendImage;	//알파 블렌드에 쓸 이미지
private:
	float size;
	
public:

	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, int width, int height, 
		int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	

	void release();
	void setTransColor(BOOL trans, COLORREF transColor);
	

	void render(HDC hdc);
	//렌더함수(뿌릴DC, left, top)
	void render(HDC hdc, int destX, int destY);
	//렌더함수(뿌릴DC, 그려질 X(left), 그려질Y(top), 가져올X(left) 가져올Y(top), 가로, 세로 크기 (가져올) 
	void render(HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight);
	
	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY);
	
	//알파 블렌드 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY, BYTE alpha);


	//랜더함수(뿌릴DC, left, top, 이미지 size Width, 이미지 size Height, 조절할 Width, 조절할 Height) - 사이즈 조절 랜더
	void adjRender(HDC hdc, int destX, int destY, int adjWidth, int adjHeight);

	//프레임 랜더 사이즈 조절
	void adjFrameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY, int adjWidth, int adjHeight);

	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateRender2(HDC hdc, float centerX, float centerY, float angle);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void alphaAniRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	

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

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	inline void setWidth(int width) { _imageInfo->width = width; }
	inline void setHeight(int height) { _imageInfo->height = height; }
};

