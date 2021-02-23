#pragma once
#include "singletonBase.h"

class gameNode;

class cameraManager : public singletonBase <cameraManager>
{
private:
	//Camera
	RECT mapRc, screenRc;				//맵과 화면 렉트				(loopRender등 인자값에 필요 시 사용)
	float targetX, targetY;				//카메라가 목표하는 타겟 좌표	(보통은 캐릭터의 중점 좌표)
	float centerX, centerY;				//카메라가 비추는 중점 좌표	(예외 처리된 실제 카메라의 좌표)
	float drawLeft, drawTop;			//카메라가 그려질 곳			(보통은 0, 0)
	float xOffset, yOffset;				//카메라 중점의 오프셋		(쉐이킹 등을 위한 카메라 오프셋)

	float cameraXSize, cameraYSize;		//카메라의 중점 영역 크기		(클 수록 부드러운 움직임을 함.)
	float screenXSize, screenYSize;		//화면 가로 세로 크기			(보통은 WINSIZEX, WINSIZEY 크기)

	image* map;							//게임의 전체 맵 이미지		(카메라가 비출 수 있는 영역)
	float mapXSize, mapYSize;			//맵 가로 세로 크기			(보통은 map의 width, height 크기)
	float magnification;				//스크린에 비출 배율			(보통은 1)
	float magnificationOffset;			//스크린에 비출 추가 배율		(보통은 0)
	bool isAdjustMagnificiation;		//배율을 설정하고 있는지
	float goalMag;						//목표 배율
	float plusMag;						//추가 배율
	bool isZoomIn;						//확대인지 축소인지

	//Shake
	int shakeTime;						//흔드는 지속 시간
	int shakeTimer;						//흔드는 시간 재는 타이머
	int shakeInterval;					//흔드는 시간 간격

	float perTime;						//시간 당 흔드는 점진도
	float shakeAngle;					//그래프의 각도

	int xShaking;						//흔들리는 x 강도
	int yShaking;						//흔들리는 y 강도
	int shakeStrength;					//점점 세게인지 점점 작게인지 그대로인지
	bool isShaking;						//흔들림 여부

public:
	//======================== Camera Render ========================
	void render(HDC hdc, image* img);

	//======================== Camera Getter ========================

	float GetX() { return centerX; }
	float GetY() { return centerY; }
	float GetTargetX() { return targetX; }
	float GetTargetY() { return targetY; }
	float GetLeft() { return drawLeft; }
	float GetTop() { return drawTop; }
	float GetCameraXSize() { return cameraXSize; }
	float GetCameraYSize() { return cameraYSize; }
	float GetScreenXSize() { return screenXSize; }
	float GetScreenYSize() { return screenYSize; }
	float GetMapXSize() { return mapXSize; }
	float GetMapYSize() { return mapYSize; }
	RECT GetMapRect() { return mapRc; }
	RECT GetScreenRect() { return screenRc; }
	float GetMagnificiation() { return magnification; }

	//======================== Camera private Function ========================

private:
	//카메라 움직임
	void Move();

	//Set Map 설정
	void Setting();

public:
	cameraManager() {}
	~cameraManager() {}
	//카메라 초기화
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//======================== Camera Setter ========================
public:

	//*this, map 이미지 파일
	void SetMap(gameNode & _gameNode, image * _img);

	//*this, map x크기, map y크기
	void SetMap(gameNode & _gameNode, int _x, int _y);

	//카메라의 중점 x좌표, 카메라의 중점 y좌표. (보통은 캐릭터의 x, y 좌표를 대입.)
	void SetPos(float _x, float _y);

	//카메라의 중점 x좌표, 카메라의 중점 y좌표, 카메라 영역의 x크기, 카메라 영역의 y크기, 카메라 속도
	void SetPos(float _x, float _y, float _cameraXSize, float _cameraYSize, float _speed);

	//화면 크기 설정 (기본은 WINSIZEX, WINSYZEY)
	void SetScreenSize(int _x, int _y) { screenXSize = _x; screenYSize = _y; }

	//카메라를 그릴 위치 설정 (LEFT, TOP 기준이며, 기본은 0, 0)
	void SetDrawPos(int _x, int _y) { drawLeft = _x; drawTop = _y; }

	//======================== Camera Zoom ========================

	//배율 설정 (보통은 1)
	void SetMagnification(float mag) { magnification = mag; }

	//배율이 mag가 될 때까지 plus씩 변화시킨다.
	void SetMagnification(float mag, float plus);

	//배율 Offset 설정
	void SetMagnificationOffset(float offset) { magnificationOffset = offset; }

	//배율 Offset 추가
	void PlusMagnification() { magnification += magnificationOffset; }


	//======================== Camera Shake ========================
public:
	//지속 시간, 시간 간격, 흔들릴 x세기, 흔들릴 y세기, 점점 작게(-1) 혹은 그대로 (0) 혹은 점점 세게(+1), 점점 작게+자동 보정(-2)
	void Shake(int _time, int _interval, float _xShaking, float _yShaking, int _strength = -2);
};


/*
	◈ ============================== 뚜모리 카메라 안내서 ============================== ◈

		┏────────────────────────────────────────────────────────────────────────┐
		│	Created By : 뚜모리						Version : 3.0				 │
		│	Reporting Date : 2020.12.08				Last Update : 2020.01.04	 │
		│																		 │
		│	Function : SetMap, SetPos, Shake, MapRender, MiniMapRender(X)		 │
		│																		 │
		│			♡		Thanks for Using this Camera!		♡				 │
		└────────────────────────────────────────────────────────────────────────┘

	이 카메라를 사용하기 위해서는 init에서 SetMap(), update에서 SetPos() 두 함수를 호출해야 합니다.
	또한, 카메라의 추가적인 기능으로는 카메라 흔들림 함수 Shake()가 있습니다.


	◈ ========================  카메라를 사용하는 방법입니다. ======================== ◈

	1.	가장 먼저, gameNode.cpp와 gameNode.h를 이 폴더 파일에서 그대로 복사 붙여넣기! 해주세요.


	2.  tagCamera : 카메라 헤더 파일을 등록하고, 멤버 변수로 카메라 객체 생성하기!

			이 카메라는 헤더 파일 안에 클래스로 만들어져 있습니다.
			우선, playGround.h에 #include "Camera.h"를 해 카메라 헤더 파일을 포함시키고,
			playGround.h의 멤버 변수에 tagCamera camera; 를 선언 해 카메라 객체를 만들어 줍니다.


	3.  SetMap() :  카메라가 보여줄 화면의 전체 영역을 설정하는 함수 호출하기!

			카메라를 사용하기 위해서는 카메라가 비출 수 있는 맵의 전체 영역 크기를 설정해 주어야 합니다.
			playGround.cpp 의 init() 영역의 가장 맨 위 gameNode::init(); 아래에 camera.SetMap(); 함수를 호출합니다.
			이는 gameNode::init() 함수보다는 아래에 있어야 합니다. SetMap 함수에서 gameNode의 backDC의 크기를 재지정하기 때문입니다.

			SetMap 함수로 카메라가 비출 수 있는 영역의 크기를 설정하기 때문에, 그 크기는 보통 전체 맵.bmp 이미지 파일의 크기와 같습니다.
			SetMap 함수의 오버로드는 두 가지이며, 이 때 인자값은 [gameNode]와, [맵의 이미지 파일] 또는 [그 배경 맵의 사이즈]입니다.
			카메라에게 비출 전체 영역을 알려주기 위해 맵의 이미지 파일을 등록할 수도 있고, 그 width와 height 크기를 직접 입력할 수도 있습니다.

		[1번 : 맵의 이미지 파일을 등록하는 방식]
			매개변수 : SetMap(gameNode _gameNode, image* _img) == (게임 노드, 맵의 이미지 파일)

			ex.1) camera.SetMap(*this, IMAGEMANAGER->addImage("map", "image/map.bmp", 3200, 1800, false, RGB(255, 0, 255)));
			배경이 되는 이미지를 이 함수에서 바로 추가하는 형태입니다. addImage를 깜빡해도 터지지 않아 안전합니다.

			ex.2) camera.SetMap(*this, IMAGEMANAGER->findImage("map");
			이 경우에는, SetMap 함수 호출보다 위에 먼저 addImage가 되어 있어야 합니다. addImage를 깜빡하고 findImage하면 터집니다.

			ex.3) camera.SetMap(*this, map);
			마찬가지로, SetMap 함수 호출보다 위에 먼저 addImage가 되어 있어야 하며, image* map은 어떤 맵 이미지를 가리키고 있어야 합니다.


		[2번 : 맵의 사이즈를 직접 수동으로 입력하는 방식]
			매개변수 : SetMap(gameNode _gameNode, int _x, int _y) == (게임 노드, 맵의 가로 크기, 맵의 세로 크기)

			ex.1) camera.SetMap(*this, 3200, 1800);
			map의 가로 세로 크기를 직접 입력하는 방식입니다. 이미지 파일이 없어도 가능하므로 이미지 파일이 없을 경우, 이 방식이 더 간편할 수 있습니다.


	4.  SetPos() : 카메라의 중점 좌표를 설정하는 함수! 실시간으로 갱신되어야 하므로 update에 쓰며, 보통 캐릭터의 x, y 좌표를 씁니다!

			이제 playGround.cpp 의 update 영역에서 camera.SetPos(); 함수를 호출합니다.
			함수의 위치는 player의 x, y가 갱신되는 곳 바로 아래에 써주는 걸 추천하지만, CPU는 빠르기 때문에 순서에 크게 영향 받지는 않습니다.

			인자값은 카메라의 중점 좌표가 될 x, y입니다. 따라서 보통은 캐릭터의 x, y좌표를 입력합니다.
			예를 들어, 카메라가 캐릭터를 곧장 쫓아갈 때 가장 일반적인 입력은 camera.SetPos(player.x, player.y);가 될 것이며,
			캐릭터보다 좀 더 위를 비추길 원할 때는 camera.SetPos(player.x, player.y - 200); 등과 같은 형태가 될 것입니다.

			오버로드는 두 가지이며, 두 카메라는 작동 방식이 다릅니다.

			1번 오버로드는, 인자값으로 x, y 중점 좌표만 받으며, 카메라가 그 좌표를 바로 쫓아갑니다.

			2번 오버로드는 인자값으로 x, y 중점좌표와 카메라가 쫓는 영역과 쫓는 스피드를 받으며,
			입력받은 캐릭터 좌표가 그 영역을 벗어나면, 그제서야 속도만큼의 빠르기로 쫓아갑니다.

			1번은 카메라는 해당 좌표를 바로 바로 쫓아가 빠르고, 2번 카메라는 더 자연스럽고 부드러운 움직임을 줄 수 있습니다.


		[1번 : 카메라가 바로 쫓아가는 방식]
		매개변수 : SetPos(float _x, float _y) == (카메라의 중점 x좌표, 카메라의 중점 y좌표)

			ex.1) camera.SetPos(player.x, player.y);
			이 경우 카메라가 캐릭터의 중점을 바로 쫓아 갑니다.

			ex.2) camera.SetPos(player.x, player.y - 200);
			이 경우 카메라가 캐릭터보다 조금 위를 비추기 때문에, 캐릭터가 화면의 약간 아래 쪽에 있게 그려집니다.


		[2번 : 카메라가 영역을 벗어나면 쫓아가는 방식]
		매개변수 : SetPos(float _x, float _y, float _cameraXSize, float _cameraYSize, int _speed)
					 == (카메라의 중점 x좌표, 카메라의 중점 y좌표, 카메라의 x 영역 크기, 카메라의 y 영역 크기, 카메라가 따라갈 속도)

			ex.1) camera.SetPos(player.x, player.y, 200, 250, player.speed / 2);
			이 카메라는 캐릭터가 영역을 지나가면 입력한 스피드만큼씩 천천히 쫓아가 좀 더 부드러워 보입니다.
			이 때 cameraXSize, cameraYSize 등이 클 수록 좀 더 기다렸다가 쫓아가며, 작을 수록 바로 쫓아갑니다.
			하지만 _cameraXSize, _cameraYSize에 0, 0을 입력한다 해도, 1번 카메라와 동작 방식이 조금 다릅니다.
			x, y를 바로 대입하는 방식이 아닌, 사용자가 입력한 _speed만큼 쫓아가기 때문에 좀 더 부드럽습니다.


	5. render() : 렌더 영역에서 이 카메라의 중점 부분을 그리라고 바꿔 줍니다!
		playGround.cpp의 render 영역의 최하단부의 건들지 말라는 부분을 바꿔줍니다.


	6.  모든 과정이 끝났습니다! 이제 카메라를 사용할 수 있습니다. >ㅅ<!
		카메라 사용에 어려움이 있으면 뚜모리에게 도움을 요청하세요...☆★

			※ TIP : 참고로 카메라를 사용할 때는, 캐릭터가 오른쪽이나 아래쪽 끝으로 갈 때,
			화면 끝(WINSIZEX, WINSIZEY)에 도달하지 못하게 하는 예외 처리를 하면 안 되고,
			맵 끝에 도달하지 못하게 하는 예외 처리를 해야 합니다.

			예를 들어, 오른쪽으로 이동할 때 화면 끝에 도달하지 못하게 막던 조건문이 다음과 같았다면,
			if (player.x + player.rcXsize < WINSIZEX && KEYMANAGER->isStayKeyDown(VK_RIGHT)) player.x += speed;

			다음과 같은 방식으로 바꿔 주어야 합니다.
			if (player.x + player.rcXsize < _camera.GetMapXSize() && KEYMANAGER->isStayKeyDown(VK_RIGHT)) player.x += speed;

			이런 처리를 바꾸어 주지 않으면, 캐릭터가 WINSIZEX 화면을 넘어가질 못해, 카메라가 작동되고 있는지 확인조차 할 수 없습니다.
			또한, init에서 SetMap을 할 때 입력했던 map 크기 만큼의 이미지를 실제로 render 해 주어야 빈 화면 없이 모든 화면이 맵으로 차 있을 것입니다.



	◈ ======================== 2. TIP : 카메라를 기준으로 상대 좌표를 쓰고 싶을 때! ======================== ◈

	HPbar, Item창 등과 같은 UI, 즉 map 위에 위치하지 않고, 카메라를 기준으로 한 상대 좌표를 써야 하는 것들은 render 부분에 해당 위치를 쓸 때,
	(0, 0) 절대 좌표를 기준으로 한 위치가 아닌, 카메라의 중점(camera.x, camera.y)을 에 대한 상대 좌표를 기준으로 위치를 입력해야 합니다.

	카메라 기준 CENTER :			(backDC, camera.GetX(), camera.GetY());
		ex) (backDC, camera.GetX() + 200, camera.GetY() - 100); 이 경우 카메라 중점을 기준으로 +200, -100 위치에 해당 객체를 그립니다.

	카메라 기준 LEFT TOP :		(backDC, camera.GetX() - camera.GetScreenXSize() / 2 , camera.GetY() - camera.GetScreenYSize() / 2);
	카메라 기준 LEFT BOTTOM :	(backDC, camera.GetX() - camera.GetScreenXSize() / 2 , camera.GetY() + camera.GetScreenYSize() / 2);
	카메라 기준 RIGHT TOP :		(backDC, camera.GetX() + camera.GetScreenXSize() / 2 , camera.GetY() - camera.GetScreenYSize() / 2);
	카메라 기준 RIGHT BOTTOM :	(backDC, camera.GetX() + camera.GetScreenXSize() / 2 , camera.GetY() + camera.GetScreenYSize() / 2);



	◈ ======================== 3. 카메라의 Shake 기능을 사용하는 방법입니다. ======================== ◈

	1.  우선 위의 6가지 절차를 따라서 카메라를 설정 해 줍니다.

	2.  update 영역에서, 사용하고 싶은 순간에 camera.Shaking(); 함수를 호출합니다.

		쉐이크 종류는 4가지이며, 점점 작게(-1), 그대로(0), 점점 크게(+1), 점점 작게 자동 보정(-2)이 있습니다.
		마지막 인자값에 쉐이크 종류를 입력하며, 입력하지 않을 시 자동 보정(-2)으로 설정되어 있습니다.

		[쉐이크 함수]
		매개변수 : Shake(int _time, int _interval, float _xShaking, float _yShaking, int _strength = -2)
					== (흔드는 지속 시간, 흔드는 시간 간격, 흔들릴 x크기, 흔들릴 y크기, 시간에 따른 점진 세기)

			ex.1) if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) camera.Shaking(100, 2, 15, 20, -2);
			엔터를 누를 경우, 카메라를 100초 동안 2초의 간격으로 x로 15, y로 20만큼 점점 작게 자동 보정하며 흔듭니다.

			ex.2) if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) camera.Shaking(30, 8, 0, 70, 1);
			엔터를 누를 경우, 카메라를 50초 동안 8초의 간격으로 x로 0, y로만 70만큼 점점 세게 흔듭니다.

			이 경우 ex.1은 ex.2보다 더 오래 흔들리며, 더 빠르게 흔들고, x, y로 흔들립니다.
			ex.2는 ex.1보다 더 짧게 흔들리며, 더 느리게 흔들고, y로만 흔들립니다.


	◈ ======================== 뚜모리 카메라를 사용 해 주셔서 감사합니다...☆★ ======================== ◈

*/
