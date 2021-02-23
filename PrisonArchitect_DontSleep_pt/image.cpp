#include "stdafx.h"
#include "Image.h"
#include "CameraManager.h"

/********************************************************************************
## Image ## 
@@ ID2D1Bitmap* bitmap : ImageManager에서 생성된 비트맵
@@ TagLoadImageInfo loadinfo : 이미지 정보(키값,파일 경로) 

프레임이미지가 아닌 이미지 클래스 생성
*********************************************************************************/
Image::Image(ID2D1Bitmap * const bitmap, const TagLoadedImageInfo & loadinfo)
	:mBitmap(bitmap),mLoadInfo(loadinfo),mScale(1.f),mAlpha(1.f),mAngle(0.f),mMaxFrameX(1),mMaxFrameY(1)
{
	this->mSize.x = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.y = (float)this->mBitmap->GetPixelSize().height;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.x;
	rc.height = mSize.y;
	this->mFrameInfo.push_back(rc);
	this->ResetRenderOption();
}
/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager에서 생성된 비트맵
@@ TagLoadImageInfo loadinfo : 이미지 정보(키값,파일 경로)
@@ int maxFrameX : 가로 프레임 수 
@@ int maxFrameY : 세로 프레임 수 

프레임 이미지 클래스 생성
*********************************************************************************/
Image::Image( ID2D1Bitmap *const bitmap, const TagLoadedImageInfo & loadinfo, const int  maxFrameX, const int  maxFrameY)
	:mBitmap(bitmap),mLoadInfo(loadinfo),mMaxFrameX(maxFrameX),mMaxFrameY(maxFrameY), mScale(1.f), mAlpha(1.f), mAngle(0.f)
{
	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	this->mSize.y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.x / (float)this->mMaxFrameX;
	float frameY = mSize.y / (float)this->mMaxFrameY;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
	for (int i = 0; i < maxFrameX; ++i)
	{
		rc.x = (float)i * (frameX);
		rc.y = (float)j * (frameY);
		rc.width = frameX;
		rc.height = frameY;
		this->mFrameInfo.push_back(rc);
	}
	}

	this->ResetRenderOption();
}
/********************************************************************************
## ~Image ##
비트맵 해제
*********************************************************************************/
Image::~Image()
{
	NEW_SAFE_RELEASE(mBitmap);
}
/********************************************************************************
## PerfeactRender ##
*********************************************************************************/
void Image::Render(const Vector2& position)
{
	Vector2 size = mSize * mScale;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.x, size.y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::FrameRender(const Vector2& position, const int frameX, const int frameY)
{
	//프레임이 최대 프레임을 벗어났다면 그리지 않는다. 
	if (frameX >= this->mMaxFrameX || frameY >= this->mMaxFrameY || frameX < 0 || frameY < 0)
	{
		ResetRenderOption();
		return;
	}

	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;

	//사이즈 = 사이즈 * 스케일
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}
/********************************************************************************
## SourceRender ##
*********************************************************************************/
void Image::SourceRender(const Vector2 & position, Vector2 InputSize, Vector2 frameIndex) //CenterBottom
{
	//현재 프레임인덱스 
	int frame = frameIndex.y* mMaxFrameX + frameIndex.x;

	//사이즈 = 사이즈 * 스케일
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x+ mFrameInfo[frame].width/2 - InputSize.x/2,
		(float)mFrameInfo[frame].y + mFrameInfo[frame].height- InputSize.y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width/2 + InputSize.x/2),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}


/********************************************************************************
## Camera Render Function ##
*********************************************************************************/
void Image::Render(const Vector2 & position, Camera* camera)
{
	//렌더할 좌표, 크기, 각도, 불투명도
	Vector2 renderPos = position;				//그릴 위치
	Vector2 renderSize = mSize * mScale;		//그릴 크기
	float renderScale = mScale;					//그릴 배율
	float renderAngle = mAngle;					//그릴 각도
	float renderAlpha = mAlpha;					//그릴 불투명도

	mRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//카메라에 따른 설정
	if (camera)
	{
		//카메라 상대 좌표
		renderPos = camera->GetRelativePos(renderPos);

		//카메라 배율
		renderSize = renderSize * camera->_zoom;
		//renderScale *= camera->_zoom;

		//카메라 각도
		renderAngle += camera->_angle;

		//카메라 불투명도
		renderAlpha *= camera->_alpha;
	}


	renderSize = renderSize * renderScale;

	//렌더링 이미지 렉트 생성
	mRenderRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//카메라 뷰포트 렉트 생성
	FloatRect viewRc = camera->_viewRc;


	//스케일 행렬을 만들어준다.
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, renderScale, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	Vector2 offset(0, 0);

	//가로로 뒤집을 것인가
	if (mIsReverseAxisX)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(-renderScale, renderScale);
		offset.x = renderSize.x;
	}

	//세로로 뒤집을 것인가
	if (mIsReverseAxisY)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, -renderScale);
		offset.y = renderSize.y;
	}

	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(renderAngle, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(renderPos.x - renderSize.x / 2.f + offset.x, renderPos.y - renderSize.y / 2.f + offset.y);
	//그릴 영역을 설정한다.
	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, renderSize.x, renderSize.y);

	_D2DRenderer->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);

	//렌더링 요청
	_D2DRenderer->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, renderAlpha);
#if true // Debug

	//디버깅용 렉트 렌더
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRenderer::GetInstance()->DrawRectangle(mRenderRect, D2DRenderer::DefaultBrush::Blue, 1.0f);
	}

#endif // Debug

	ResetRenderOption();

}

/********************************************************************************
## Camera Frame Render Function ##
*********************************************************************************/
void Image::FrameRender(const Vector2 & position, const int frameX, const int frameY, Camera * camera)
{
	//프레임이 최대 프레임을 벗어났다면 그리지 않는다. 
	if (frameX >= this->mMaxFrameX || frameY >= this->mMaxFrameY || frameX < 0 || frameY < 0)
	{
		ResetRenderOption();
		return;
	}
	
	//현재 프레임 인덱스 
	int frame = frameY * mMaxFrameX + frameX;

	//렌더할 좌표, 크기, 각도, 불투명도
	Vector2 renderPos = position;				//그릴 위치
	Vector2 renderSize = mSize;					//그릴 크기
	float renderScale = mScale;					//그릴 배율
	float renderAngle = mAngle;					//그릴 각도
	float renderAlpha = mAlpha;					//그릴 불투명도

	mRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//카메라에 따른 설정
	
	if (camera)
	{
		//카메라 상대 좌표
		renderPos = camera->GetRelativePos(renderPos);

		//카메라 배율에 따른 크기
		renderSize = renderSize * camera->_zoom;
		//renderScale *= camera->_zoom;

		//카메라 각도
		renderAngle += camera->_angle;

		//카메라 불투명도
		renderAlpha *= camera->_alpha;
	}

	renderSize = renderSize * renderScale;

	//렌더링 이미지 렉트 생성
	mRenderRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//카메라 뷰포트 렉트 생성
	FloatRect viewRc = camera->_viewRc;

#pragma region 클리핑
	

	//클리핑 영역 - 윈도우 창
	if (mRenderRect.left > WINSIZEX || mRenderRect.right < 0.f ||
		mRenderRect.top > WINSIZEY || mRenderRect.bottom < 0.f)
	{
		ResetRenderOption();
		return;
	}

	//클리핑 영역 - 카메라 뷰포트
	if (camera)
	{
		if (mRenderRect.left > viewRc.right || mRenderRect.right < viewRc.left ||
			mRenderRect.top > viewRc.bottom || mRenderRect.bottom < viewRc.top)
		{
			ResetRenderOption();
			return;
		}
	}
#pragma endregion

	//스케일 행렬을 만들어준다.
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, renderScale, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	Vector2 offset(0, 0);

	//가로로 뒤집을 것인가
	if (mIsReverseAxisX)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(-renderScale, renderScale);
		offset.x = renderSize.x;
	}

	//세로로 뒤집을 것인가
	if (mIsReverseAxisY)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, -renderScale);
		offset.y = renderSize.y;
	}

	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(renderAngle, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(renderPos.x - renderSize.x / 2.f + offset.x, renderPos.y - renderSize.y / 2.f + offset.y);

	//그릴 영역 세팅
	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, renderSize.x, renderSize.y);

	//소스에서 가져올 영역 세팅
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));

	_D2DRenderer->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	_D2DRenderer->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, renderAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);


#if true // Debug

	//디버깅용 렉트 렌더
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRenderer::GetInstance()->DrawRectangle(mRenderRect, D2DRenderer::DefaultBrush::Blue, 1.0f);
	}

#endif // Debug

	ResetRenderOption();

}

/********************************************************************************
## ResetRenderOption ##
이미지 클래스 렌더 관련 옵션들 전부 초기화
*********************************************************************************/
void Image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mAngle = 0.f;
	if (mFrameInfo.size() <= 1)
	{
		this->mSize.x = (float)mBitmap->GetPixelSize().width;
		this->mSize.y = (float)mBitmap->GetPixelSize().height;
	}
	else
	{
		this->mSize.x = mFrameInfo[0].width;
		this->mSize.y = mFrameInfo[0].height;
	}
	this->mIsReverseAxisX = this->mIsReverseAxisY = false;
}
