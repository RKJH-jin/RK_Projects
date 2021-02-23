#include "stdafx.h"
#include "StuffObject.h"
#include "stdafx.h"
#include "StuffObject.h"

StuffObject::StuffObject(STUFFTTYPE stuffType)
{
	_useCount = 3;

	//트랜스 폼 컴포넌트와 기본 설정
	{
		_transform = AddComponent<TransformC>();
		_transform->SetPosition(Vector2(WINSIZEX / 2 + RND->getInt(500), WINSIZEY / 2));

		_transform->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	}

	//이미지세팅
	_stuffType = stuffType;
	CreateObject(this);


	switch (_stuffType)
	{
	case STUFFTTYPE::COOKBACON:
		_name = "요리 중인 베이컨";
		_description = "요리 중인 베이컨.";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("baconCook")); break;

		break;
	case STUFFTTYPE::FOODBACON:
		_name = "요리 된 베이컨";
		_description = "맛있는 냄새가 나는 베이컨.";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("baconFood")); break;
		break;
	case STUFFTTYPE::BACONS:
		_name = "베이컨 꾸러미";
		_description = "신선한 베이컨";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("bacons")); break;
		break;
	case STUFFTTYPE::BOX:
		_name = "상자";
		_description = "재료가 든 상자";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("box")); break;
		break;
	case STUFFTTYPE::GRAYBRICKS:
		_name = "회벽돌";
		_description = "회색 벽돌들";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("bricks")); break;
		break;
	case STUFFTTYPE::REDBRICKS:
		_name = "적벽돌";
		_description = "적색 벽돌들";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("brickReds")); break;
		break;
	case STUFFTTYPE::CABBAGES:
		_name = "양배추 꾸러미";
		_description = "신선한 양배추";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("cabbages")); break;
		break;
	case STUFFTTYPE::REBARS:
		_name = "철근들";
		_description = "공사에 쓰이는 철근";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("rebars")); break;
		break;
	case STUFFTTYPE::SOUPGREENS:
		_name = "요리된 양배추 수프";
		_description = "맛있는 양배추 수프";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("soupGreens")); break;
		break;
	case STUFFTTYPE::SOUPS:
		_name = "요리된 감자 수프";
		_description = "맛있는 감자 수프";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("soups")); break;
		break;
	case STUFFTTYPE::TRAYS:
		_name = "깨끗한 식판";
		_description = "깨끗하게 닦인 식판들";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trays")); break;
		break;
	case STUFFTTYPE::TRAYDIRTYS:
		_name = "더러운 식판";
		_description = "사용하고 난 더러운 식판들";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trayDirtys")); break;
		break;
	case STUFFTTYPE::WOODCUTS:
		_name = "목재들";
		_description = "뭉친 목재들";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("woodCuts")); break;
		break;
	case STUFFTTYPE::CAR:
		_name = "차";
		_description = "이동 차량";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("car")); break;
		break;
	case STUFFTTYPE::TRASH:
		_name = "쓰레기";
		_description = "쓰레기";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trash")); break;
		break;
	case STUFFTTYPE::POTATOS:
		_name = "감자 꾸러미";
		_description = "신선한 감자들";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("patatos")); break;
		break;
	case STUFFTTYPE::END:
		break;
	default:
		break;
	}

	GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	GetTransform()->SetPosition(_transform->GetPosition());
}

HRESULT StuffObject::init()
{
	return S_OK;
}

void StuffObject::release()
{
}

void StuffObject::update()
{
}

void StuffObject::render()
{
	GameObject::Render();
	//갯수만큼 렌더
	GetComponent<ImageC>()->SetFrame(Vector2(_useCount - 1, 0));
	//최대치를 넘어가면 최대치이미지로 고정
	if (_useCount >= 3)
		GetComponent<ImageC>()->SetFrame(Vector2(GetComponent<ImageC>()->GetImage()->GetMaxFrameX() - 1, 0));

}

void StuffObject::MouseEnter()
{
}

void StuffObject::MouseStay()
{
}

void StuffObject::MouseExit()
{
}
