#pragma once

/****************************************************************************
## ImageRenderer ##
*****************************************************************************/
class ImageManager final 
{
public:
	static ImageManager* GetInstance()
	{
		static ImageManager istance;
		return &istance;
	}

private:
	typedef map<string, class Image*>::iterator ImageIter; 
private:
	map<string, class Image*> mImageList;

	class IWICImagingFactory* mWicFactory;
public:
	ImageManager();
	virtual ~ImageManager();

	class Image* AddImage(const string& key, const wstring& file);
	class Image* AddFrameImage(const string& key,const wstring& file,const int maxFrameX,const int maxFrameY);
	class Image* FindImage(const string& key);

private:
	ID2D1Bitmap* CreateD2DBitmapFromFile(const wstring& file);
	void DeleteAll();

};

#define _ImageManager ImageManager::Get()