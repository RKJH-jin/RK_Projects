#pragma once
class Image;

class Camera
{
public:	//다 짜고 나면 private으로 바꿀 예정

	FloatRect _screenRc;	//카메라 스크린 영역
	FloatRect _viewRc;		//카메라 뷰포트 영역

	Vector2 _pos;			//카메라 중점 위치
	Vector2 _size;			//카메라 크기

	float _zoom;			//배율 (scale)
	float _alpha;			//투명도
	float _angle;			//각도 (rotation)

	bool _isActive;			//활성화 여부

	float _minZoom;			//최소 배율
	float _maxZoom;			//최대 배율

public:

	Camera();
	~Camera() {}

	HRESULT Init();
	void Release();
	void Update();
	void Render(Image* img, Vector2 pos); //안 써도 됨

	//게터
	float GetScale() { return _zoom; }
	float GetAlpha() { return _alpha; }
	FloatRect GetViewRect() { return _viewRc; }

	//세터
	void SetViewRect(FloatRect rc);
	void SetPos(Vector2 pos);
	void SetZoom(float scale);
	void SetAlpha(float alpha);
	void SetAngle(float angle);
	void SetActive(bool active);

	Vector2 GetRelativePos(Vector2 pos);
	FloatRect GetRelativePos(FloatRect & rc);
	Vector2 GetAbsolutePos(Vector2 pos);
	FloatRect GetAbsolutePos(FloatRect & rc);

	//함수

	void FillRectangle(FloatRect &rect, _In_ ID2D1Brush *brush);
	
};

class CameraManager
{

public:
	static CameraManager* GetInstance()
	{
		static CameraManager istance;
		return &istance;
	}

private:
	typedef vector<Camera*> vCamera;

	vCamera _vCamera;

public:
	
	vCamera& GetVCamera() { return _vCamera; }

	Camera* GetMainCamera() { return _vCamera[0]; }

	//함수
	void CreateCamera(FloatRect rc);
	
};

