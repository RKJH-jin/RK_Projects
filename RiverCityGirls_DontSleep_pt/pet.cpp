#include "stdafx.h"
#include "pet.h"
#define PETSPEED 3.f

HRESULT pet::init()
{
	//애니관련
	_obj.init(OBJECT_GROUP::OBJECT, IMG_M->findImage("pet"), vector3(WINSIZEX/2, 0, WINSIZEY / 2));
	_obj.ani = new animation;
	_obj.ani->setDefPlayFrame(false, true);
	_obj.ani->setFPS(1);
	_obj.ani->init(_obj.img->getWidth(), _obj.img->getHeight(), _obj.img->getFrameWidth(), _obj.img->getFrameHeight());
	
	//======================================
	_xOffset = 60;
	_yOffset = -200;
	_obj.pos.y = _yOffset;
	_obj.ani->start();
	_speed = PETSPEED;
	return S_OK;
}

void pet::release()
{
}

void pet::update(vector3 pos)
{
	//프레임업뎃
	_obj.ani->frameUpdate(TIME_M->getElapsedTime()*7);
	//무한재생 (원래 이거없어도 됭하는데;;)
	if(!_obj.ani->isPlay())_obj.ani->start();

	
	//==================================
	//펫이 일정 거리 이상 멀어지면 보정 속도를 추가한다.
	int revisionXSpeed = 0;
	int revisionYSpeed = 0;
	if (abs(pos.x - _obj.pos.x) > WINSIZEX / 4) revisionXSpeed = abs(pos.x - _obj.pos.x) / 30;
	if (abs(pos.y - _obj.pos.z) > WINSIZEY / 4) revisionYSpeed = abs(pos.z - _obj.pos.z) / 30;
	if (abs(pos.y - _obj.pos.y) > WINSIZEY / 4) revisionYSpeed = abs(pos.y - _obj.pos.y) / 30;
	
	//x값보정
	if (_obj.pos.x > pos.x +_xOffset) --_obj.pos.x;
	if (_obj.pos.x < pos.x - _xOffset) ++_obj.pos.x;

	//z값 보정
	if (_obj.pos.z > pos.z) --_obj.pos.z;
	if (_obj.pos.z < pos.z) ++_obj.pos.z;

	//y값보정
	if (_obj.pos.y > pos.y + _yOffset)--_obj.pos.y;
	if (_obj.pos.y < pos.y + _yOffset)++_obj.pos.y;



	if (_obj.pos.x < pos.x - _xOffset) _obj.pos.x += _speed + revisionXSpeed;
	if (_obj.pos.x > pos.x + _xOffset) _obj.pos.x -= _speed + revisionXSpeed;

	_obj.update();

}

void pet::render(HDC hdc)
{
	ZORDER_M->renderObject(hdc, &_obj, RENDERTYPE::ANI_RENDER);
}
