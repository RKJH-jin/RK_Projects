#include "stdafx.h"
#include "cameraManager.h"
#include "gameNode.h"

/*====================================================================
	카메라 초기화
====================================================================*/
HRESULT cameraManager::init()
{
	targetX = targetY = 0;		//카메라 타겟 좌표
	centerX = centerY = 0;		//카메라 중점 좌표
	xOffset = yOffset = 0;		//카메라 중점 오프셋
	drawLeft = drawTop = 0;		//카메라를 그릴 위치
	mapXSize = mapYSize = 0;	//맵의 크기

	screenXSize = WINSIZEX;		//화면의 X 크기
	screenYSize = WINSIZEY;		//화면의 Y 크기

	shakeTime = shakeInterval = 0;	//타이머
	perTime = shakeAngle = 0;		//점진도와 각도
	isShaking = false;				//흔들림 여부

	magnification = 1;				//배율
	magnificationOffset = 0;		//추가 배율
	isAdjustMagnificiation = false; //배율을 설정하고 있는지


	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{

}

void cameraManager::render()
{
}

/*====================================================================
		mapDC와 UI를 back DC에 렌더한다.
====================================================================*/
void cameraManager::render(HDC hdc, image* img)
{
	img->render(hdc, drawLeft, drawTop, screenXSize, screenYSize,
		centerX - screenXSize / 2 / magnification, centerY - screenYSize / 2 / magnification,
		screenXSize / magnification, screenYSize / magnification);

	UI_M->render(hdc);
}

/*====================================================================
		카메라 움직임
====================================================================*/
void cameraManager::Move()
{

	if (magnification < 1)
	{
		magnification = 1;
		magnificationOffset = 0;
	}

	PlusMagnification();

	//배율 조정을 명령했을 경우 배율을 조정한다.
	if (isAdjustMagnificiation)
	{
		if (isZoomIn)	//줌인 확대
		{
			if (magnification < goalMag) magnificationOffset = plusMag;
			else
			{
				magnification = goalMag;
				magnificationOffset = 0;
				isAdjustMagnificiation = false;
			}
		}
		else
		{				//줌아웃 축소
			if (magnification > goalMag) magnificationOffset = -plusMag;
			else
			{
				magnification = goalMag;
				magnificationOffset = 0;
				isAdjustMagnificiation = false;
			}
		}
	}

	//쉐이킹을 명령했을 경우 카메라를 흔든다.
	if (isShaking)
	{
		if (--shakeTimer < 0)	//Timer가 0이 되면 쉐이크를 종료한다.
		{
			xOffset = 0;			//Offset을 0으로 초기화
			yOffset = 0;			//Offset을 0으로 초기화
			shakeAngle = 0;			//그래프의 각도를 0으로 초기화
			isShaking = false;		//흔들지 않는다.
			return;
		}

		//시간 간격마다 shakeAngle을 바꾼다.
		if (shakeTimer % shakeInterval == 0)
		{
			shakeAngle = RND->getFloat(PI * 2);

			//선택한 보정 방법에 따라 시간에 따른 보정을 달리 한다.
			if (shakeStrength == -1 || shakeStrength == -2) perTime = shakeTimer;	//점점 작게
			else if (shakeStrength == 0) perTime = shakeTime;						//그대로
			else if (shakeStrength == 1) perTime = (shakeTime - shakeTimer);		//점점 세게
		}

		//점점 작게 + 자동 보정을 택한 경우, 부드러운 처리를 위해, 초반에는 Strength 보다 작게 흔든다.
		if (shakeStrength == -2 && shakeTimer > shakeTime * 0.7f)
		{
			xOffset = cosf(shakeAngle) * xShaking * (shakeTime - shakeTimer) / shakeTime;
			yOffset = sinf(shakeAngle) * yShaking * (shakeTime - shakeTimer) / shakeTime;
		}
		else	//그 외의 경우 선택한 시간에 따른 진폭 보정을 한다.
		{
			xOffset = cosf(shakeAngle) * xShaking * perTime / shakeTime;
			yOffset = sinf(shakeAngle) * yShaking * perTime / shakeTime;
		}

		centerX += xOffset;
		centerY += yOffset;
	}
}

/*====================================================================
		카메라 설정
====================================================================*/
void cameraManager::Setting()
{
	centerX = centerY = 0;		//카메라 중점 좌표
	xOffset = yOffset = 0;		//카메라 중점 오프셋
	drawLeft = drawTop = 0;		//카메라를 그릴 위치
	mapXSize = mapYSize = 0;	//맵의 크기

	screenXSize = WINSIZEX;		//화면의 X 크기
	screenYSize = WINSIZEY;		//화면의 Y 크기
}

/*====================================================================
		이미지로 맵 크기 설정
====================================================================*/
void cameraManager::SetMap(gameNode & _gameNode, image * _img)
{
	Setting();						//초기화
	map = _img;						//배경 이미지
	mapXSize = map->getWidth();		//배경 x크기
	mapYSize = map->getHeight();	//배경 y크기
	_gameNode.gameNode::setBackBuffer(screenXSize, screenYSize);
	_gameNode.gameNode::setMapBuffer(mapXSize, mapYSize);
	mapRc = RectMake(0, 0, mapXSize, mapYSize);
}

/*====================================================================
		입력한 값으로 맵 크기 설정
====================================================================*/
void cameraManager::SetMap(gameNode & _gameNode, int _x, int _y)
{
	Setting();			//초기화
	mapXSize = _x;		//배경 x크기
	mapYSize = _y;		//배경 y크기
	_gameNode.gameNode::setBackBuffer(screenXSize, screenYSize);
	_gameNode.gameNode::setMapBuffer(mapXSize, mapYSize);
	mapRc = RectMake(0, 0, mapXSize, mapYSize);
}

/*====================================================================
		카메라 중점 위치 설정 (공장 따라 감)
====================================================================*/
void cameraManager::SetPos(float _x, float _y)
{
	//카메라가 입력한 좌표를 곧장 따라간다.
	targetX = _x + xOffset;
	targetY = _y + yOffset;

	//카메라가 맵 끝을 벗어나지 않게 예외 처리를 한다.
	if (targetX <= 0 + screenXSize / 2) targetX = screenXSize / 2;
	if (targetY <= 0 + screenYSize / 2) targetY = screenYSize / 2;
	if (targetX >= mapXSize - screenXSize / 2) targetX = mapXSize - screenXSize / 2;
	if (targetY >= mapYSize - screenYSize / 2) targetY = mapYSize - screenYSize / 2;

	//카메라가 입력한 좌표를 곧장 따라간다.
	centerX = _x + xOffset;
	centerY = _y + yOffset;

	Move();		//카메라 쉐이킹 등 카메라의 움직임을 호출한다.

	//카메라가 맵 끝을 벗어나지 않게 예외 처리를 한다.
	if (centerX <= 0 + screenXSize / 2) centerX = screenXSize / 2;
	if (centerY <= 0 + screenYSize / 2) centerY = screenYSize / 2;
	if (centerX >= mapXSize - screenXSize / 2) centerX = mapXSize - screenXSize / 2;
	if (centerY >= mapYSize - screenYSize / 2) centerY = mapYSize - screenYSize / 2;
	screenRc = RectMakeCenter(centerX, centerY, screenXSize, screenYSize);
}

/*====================================================================
		카메라 중점 위치 설정 (입력한 속도로 따라 감)
====================================================================*/
void cameraManager::SetPos(float _x, float _y, float _cameraXSize, float _cameraYSize, float _speed)
{
	if (_speed < 1) _speed = 1;		//속도는 1이상으로 한다.

	int revisionXSpeed = 0;			//카메라가 못 따라가면 보정 속도를 추가한다.
	int revisionYSpeed = 0;			//카메라가 못 따라가면 보정 속도를 추가한다.
	if (abs(centerX - _x) > screenXSize / 16.0f) revisionXSpeed = abs(centerX - _x) / 100.0f;
	if (abs(centerY - _y) > screenYSize / 16.0f) revisionYSpeed = abs(centerY - _y) / 100.0f;

	Move();		//카메라 쉐이킹 등 카메라의 움직임을 호출한다.

	//카메라가 입력한 좌표를 곧장 따라간다.
	targetX = _x + xOffset;
	targetY = _y + yOffset;

	//카메라가 맵 끝을 벗어나지 않게 예외 처리를 한다.
	if (targetX <= 0 + screenXSize / 2) targetX = screenXSize / 2;
	if (targetY <= 0 + screenYSize / 2) targetY = screenYSize / 2;
	if (targetX >= mapXSize - screenXSize / 2) targetX = mapXSize - screenXSize / 2;
	if (targetY >= mapYSize - screenYSize / 2) targetY = mapYSize - screenYSize / 2;

	//카메라가 입력한 좌표를 _speed의 속도로 따라간다.
	if (centerX <= _x - xOffset - _cameraXSize / 2) centerX += _speed + revisionXSpeed;
	if (centerX >= _x + xOffset + _cameraXSize / 2) centerX -= _speed + revisionXSpeed;
	if (centerY <= _y - yOffset - _cameraYSize / 2) centerY += _speed + revisionYSpeed;
	if (centerY >= _y + yOffset + _cameraYSize / 2) centerY -= _speed + revisionYSpeed;

	//카메라가 맵 끝을 벗어나지 않게 예외 처리를 한다.
	if (centerX <= 0 + screenXSize / 2) centerX = screenXSize / 2;
	if (centerY <= 0 + screenYSize / 2) centerY = screenYSize / 2;
	if (centerX >= mapXSize - screenXSize / 2) centerX = mapXSize - screenXSize / 2;
	if (centerY >= mapYSize - screenYSize / 2) centerY = mapYSize - screenYSize / 2;
}

/*====================================================================
		배율을 설정한다.
====================================================================*/
void cameraManager::SetMagnification(float mag, float plus)
{
	if (mag < 1) mag = 1;
	goalMag = mag;
	if (goalMag > magnification) isZoomIn = true;
	else isZoomIn = false;
	plusMag = abs(plus);
	isAdjustMagnificiation = true;
}

/*====================================================================
		흔들림 연출
====================================================================*/
void cameraManager::Shake(int _time, int _interval, float _xShaking, float _yShaking, int _strength)
{
	if (_interval < 1) _interval = 1;	//간격은 최소 1 이상
	xShaking = _xShaking;				//가로로 흔드는 세기
	yShaking = _yShaking;				//세로로 흔드는 세기
	shakeInterval = _interval;			//흔드는 시간 간격
	shakeTime = _time;					//흔드는 지속 시간
	shakeTimer = _time;					//흔드는 시간 타이머
	shakeStrength = _strength;			//점점 작게 흔들리는지 그대로인지 세게인지
	isShaking = true;					//흔들리게 한다
}