#pragma once

class Camera;

class Image final
{
public:
	struct TagLoadedImageInfo
	{
		string key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const string& key,const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct FrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap*		mBitmap;
	float				mAlpha;			

	Vector2				mSize;			
	float				mScale;			
	float				mAngle;

	FloatRect				mRect;
	FloatRect				mRenderRect;

	TagLoadedImageInfo	mLoadInfo;		

	vector<Image::FrameRect>	mFrameInfo;
	int							mMaxFrameX;
	int							mMaxFrameY;

	bool						mIsReverseAxisX;
	bool						mIsReverseAxisY;
	bool						mIsFrameImage;

private:
	friend class ImageManager;
	Image() = delete;
	Image( ID2D1Bitmap*const bitmap,const TagLoadedImageInfo& loadinfo);
	Image( ID2D1Bitmap*const bitmap,const TagLoadedImageInfo& loadinfo,const int maxFrameX,const int maxFrameY);
	virtual ~Image();
	Image operator = (const Image& image) {}
public:
	//백버퍼 렌더
	void Render(const Vector2& position);
	void FrameRender(const Vector2& position, const int frameX, const int frameY);
	//enum class ANCHORPIVOT;
	//void SourceRender(const Vector2&position, ANCHORPIVOT pivot, Vector2 size);
	void SourceRender(const Vector2&position,Vector2 size, Vector2 frame);


	//카메라 렌더
	void Render(const Vector2& position, Camera* camera);
	void FrameRender(const Vector2& position, const int frameX, const int frameY, Camera* camera);


	//옵션 리셋
	void ResetRenderOption();

	void SetSize(const Vector2& vec) { this->mSize = vec; }
	void SetAlpha(const float alpha) { this->mAlpha = alpha; }
	void SetScale(const float scale) { this->mScale = scale; }
	void SetAngle(const float angle) { this->mAngle = angle; }
	void SetReverseX(const bool& x) { this->mIsReverseAxisX = x; }
	void SetReverseY(const bool& y) { this->mIsReverseAxisY = y; }

	FloatRect& GetRect() { return mRect; }
	FloatRect& GetRenderRect() { return mRenderRect; }

	const int GetAlpha()const{ return mAlpha; }
	const int GetMaxFrameX()const{ return mMaxFrameX; }
	const int GetMaxFrameY()const{ return mMaxFrameY; }
	const string GetKey() const { return this->mLoadInfo.key; }
	const UINT GetWidth() const{ return mBitmap->GetPixelSize().width; }
	const UINT GetHeight()const{ return mBitmap->GetPixelSize().height; }
	const Vector2 GetSize()const { return this->mSize; }
	const float GetScale()const { return this->mScale; }
	Vector2 GetFrameSize(const int& frame = 0) const { return Vector2(mFrameInfo[frame].width, mFrameInfo[frame].height); }
	const TagLoadedImageInfo& GetLoadInfo() const { return mLoadInfo; }

	bool GetIsFrameImage() { return mIsFrameImage; }
};

