#include "stdafx.h"
#include "ToolObject.h"
#include "Character.h"

ToolObject::ToolObject()
{
	CreateObject(this);
	//트랜스 폼 컴포넌트와 기본 설정
	{
		_transform = AddComponent<TransformC>();

		_transform->SetPosition(Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 100));

		_transform->SetPivot(Vector2(HANDEDNESS_RIGHT, 0));

		_transform->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	}

	//이미지세팅
	_toolType = TOOLTYPE::NONE;
	_isRender = true;
	AddComponent<ImageC>();
	GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	GetTransform()->SetPosition(_transform->GetPosition());
}

HRESULT ToolObject::init()
{
	return S_OK;
}

void ToolObject::release()
{
}

void ToolObject::update()
{
	_transform->SetPosition(Vector2(_charecter->GetTransform()->GetPosition()));
}

void ToolObject::render()
{
	GameObject::Render();

}

void ToolObject::MouseEnter()
{
}

void ToolObject::MouseStay()
{
}

void ToolObject::MouseExit()
{
}



void ToolObject::SetToolType(TOOLTYPE type)
{
	_toolType = type;
	_isActive = true;


	switch (_toolType)
	{
	case TOOLTYPE::NONE:
		_isActive = false;
		break;
	case TOOLTYPE::BACON:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("bacon"));
		break;
	case TOOLTYPE::BOX:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("box"));
		break;
	case TOOLTYPE::GRAYBRICK:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("brick"));
		break;
	case TOOLTYPE::REDBRICK:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("brickRed"));
		break;
	case TOOLTYPE::CABBAGE:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("cabbage"));
		break;
	case TOOLTYPE::DOCUMENT:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("document"));
		break;
	case TOOLTYPE::DRIVER:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("driver"));
		break;
	case TOOLTYPE::MOP:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("mop"));
		break;
	case TOOLTYPE::POTATO:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("patato"));
		break;
	case TOOLTYPE::REBAR:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("rebar"));
		break;
	case TOOLTYPE::SOUP:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("rebar"));
		break;
	case TOOLTYPE::SOUPGREEN:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("soupGreen"));

		break;
	case TOOLTYPE::SPATULA:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("spatula"));
		break;
	case TOOLTYPE::SYRIGNE:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("syringe"));
		break;
	case TOOLTYPE::TRAY:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("tray"));
        _key = "식판";
		break;
	case TOOLTYPE::TRAYDIRTY:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trayDirty"));
		break;
	case TOOLTYPE::WOODCUT:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("woodCut"));
		break;
	case TOOLTYPE::TRASH:
		GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trash"));
		break;
	case TOOLTYPE::END:
		break;
	default:
		break;
	}
}

void ToolObject::setLinkCharacter(Character * character)
{
	_charecter = character;
}
