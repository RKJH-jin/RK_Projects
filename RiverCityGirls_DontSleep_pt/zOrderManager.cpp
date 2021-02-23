#include "stdafx.h"
#include "zOrderManager.h"
#include "GameObject.h"
#include "gameNode.h"

HRESULT zOrderManager::init()
{
	return S_OK;
}

void zOrderManager::release()
{
	_vZorder.clear();
}

void zOrderManager::update()
{
}

/*====================================================================
		늘 Zorder 에 따라 정렬하고 렌더 한 후, 벡터를 비운다.
====================================================================*/
void zOrderManager::render()
{
	// 벡터가 비었으면 return한다.
	if (_vZorder.empty()) return;

	//벡터의 원소를 처음부터 끝까지 정렬한다.
	sortVector(0, _vZorder.size() - 1);

	//SHIFT 토글 키를 누르면 디버깅용 Rect를 그린다.
	if (KEY_M->isToggleKey(VK_SHIFT))
	{
		for (int i = 0; i < _vZorder.size(); i++)Rectangle(_vZorder[i].hdc, _vZorder[i].rc);
	}

	//그림자가 있으면 렌더한다.
	for (int i = 0; i < _vZorder.size(); i++)
	{
		if (_vZorder[i].isShadow)
		{
				IMG_M->findImage("shadow")->render(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.z, (((int)_vZorder[i].pos.y - 1) % 255));	//실제 비율 영향으로 바꾸기
		}
	}

	//이미지를 렌더한다.
	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].renderType)
		{
			case RENDERTYPE::RENDER:
				_vZorder[i].img->render(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.y + _vZorder[i].pos.z - _vZorder[i].img->getFrameHeight() / 2, _vZorder[i].alpha);
			break;
			case RENDERTYPE::FRAME_RENDER:
				_vZorder[i].img->frameRender(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.y + _vZorder[i].pos.z - _vZorder[i].img->getFrameHeight() / 2, _vZorder[i].imgIndex.x, _vZorder[i].imgIndex.y, _vZorder[i].alpha);
				break;
			case RENDERTYPE::ANI_RENDER:
				_vZorder[i].img->aniRender(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.y + _vZorder[i].pos.z - _vZorder[i].img->getFrameHeight() / 2, _vZorder[i].ani, _vZorder[i].alpha);
			break;
		}
	}

	//벡터를 비운다.
	_vZorder.clear();
}

/*====================================================================
		해당 오브젝트를 벡터에 넣어 렌더하게 만든다.
====================================================================*/
void zOrderManager::renderObject(HDC hdc, GameObject* go, RENDERTYPE renderType)
{
	tagZorder zOrder;
	zOrder.hdc = hdc;
	zOrder.img = go->img;
	zOrder.isShadow = go->isShadow;

	zOrder.pos = go->pos;
	zOrder.size = go->size;
	zOrder.rc = go->rc;
	zOrder.alpha = go->alpha;

	zOrder.renderType = renderType;
	zOrder.imgIndex = go->imgIndex;
	zOrder.ani = go->ani;


	_vZorder.push_back(zOrder);

}

/*====================================================================
		벡터를 정렬한다.
====================================================================*/
void zOrderManager::sortVector(int s, int e)
{
	if (s >= e) return;

	float pivot = _vZorder[s].pos.z - _vZorder[s].pos.y;
	int left = s;
	int right = e;

	while (left <= right)
	{
		//left와 pivot을 비교, left가 작으면 ++
		while (_vZorder[left].pos.z - _vZorder[left].pos.y < pivot) ++left;

		//right와 pivot을 비교, left가 크면 --
		while (_vZorder[right].pos.z - _vZorder[right].pos.y > pivot) --right;

		//left와 right 둘을 스왑해 정렬해 나간다.
		if (left <= right)
		{
			swap(_vZorder[left], _vZorder[right]);
			++left; --right;
		}
	}

	//재귀함수로 좌우를 끝까지 퀵 정렬한다.
	sortVector(s, right);
	sortVector(left, e);
}
