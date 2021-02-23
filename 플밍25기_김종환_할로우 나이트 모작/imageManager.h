#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>
#include <vector>

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;


private:
	mapImageList _mImageList;
	vector<image*>				_vRotateImage;
	vector<image*>::iterator	_viRotateImage;


public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//단일 이미지
	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);

	//프레임 이미지
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);
	BOOL deleteAll();

	//일반 랜더
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//배율 랜더
	void adjRender(string strKey, HDC hdc, int destX, int destY, int adjWidth, int adjHeight);

	//알파 랜더
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	
	void rotateRender(string strKey, HDC hdc, float destX, float destY, float angle);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
};

