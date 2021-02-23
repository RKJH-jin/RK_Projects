#include "stdafx.h"
#include "Character.h"
#include "MapToolScene.h"
#include "MapManager.h"
Character::Character()
{
	//상태초기화
	_info.goalState = GOALSTATE::NONE;
	_info.btState = BTSTATE::NONE;

	//방향에 따른 프레임 설정
	_info.frameX[0] = 0;	//앞
	_info.frameX[1] = 2;	//옆
	_info.frameX[2] = 1;	//뒤
	_info.frameX[4] = 3;	//잠

	//트랜스 폼 컴포넌트와 기본 설정
	{
		_transform = AddComponent<TransformC>();
		_transform->SetPosition(Vector2(WINSIZEX / 2, WINSIZEY / 2)); // 640 360 10, 5.?
		_transform->SetDirection(DIRECTION::FRONT);

		_transform->SetSize(Vector2(50, 60));
		_transform->SetCamera(CAMERAMANAGER->GetVCamera()[0]);

		_info.moveSpeed = 4.f * DATAMANAGER->GetInfo().gameSpeed;
		_info.actSpeed = 1.f * DATAMANAGER->GetInfo().gameSpeed;
	}
	GameObject::SetActive(true);

	_info.toolObject = new ToolObject();


}

HRESULT Character::init()
{
	return S_OK;
}

void Character::release()
{
}

void Character::update()
{
	GameObject::Update();

	_info.moveSpeed = 4.f * DATAMANAGER->GetInfo().gameSpeed;	//*전체속도 를 곱해줘서 이동속도와 액션속도가 바뀔거같음. 
	_info.actSpeed = 1.f * DATAMANAGER->GetInfo().gameSpeed;	//*전체속도 액션속도로 팔움직이고 그런거 하지않을까.. 항상 전체속도 곱해주는것 매우 중요!!

	_transform->Update();

	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) _transform->Translate(Vector2(RND->getFromFloatTo(-_info.moveSpeed, _info.moveSpeed), RND->getFromFloatTo(-_info.moveSpeed, _info.moveSpeed)));


	//방향에따른 렌더관련
	if (_info.toolObject != NULL && _transform->GetDirection() == DIRECTION::BACK)_info.toolObject->SetRender(false);
	if (_info.toolObject != NULL && _transform->GetDirection() != DIRECTION::BACK)_info.toolObject->SetRender(true);

	if (_torso->GetTransform()->GetDirection() == DIRECTION::RIGHT) _torso->GetComponent<ImageC>()->SetReverese(true, false);
	_torso->GetComponent<ImageC>()->SetFrame(Vector2(_info.frameX[(int)_transform->GetDirection()], 0));

	if (_info.toolObject != nullptr)
		_info.toolObject->GetTransform()->SetPosition(Vector2(_info.leftHand->GetTransform()->GetPosition().x, _info.leftHand->GetTransform()->GetPosition().y));

}

void Character::render()
{

}

Character * Character::MouseEnter()
{
	return this;
}

Character * Character::MouseStay()
{
	return this;
}

Character * Character::MouseExit()
{
	return this;
}

void Character::CreateHands()
{
	//신체 부위 - 손

	//오른손 초기화
	_info.rightHand = CreateObject(this);
	_info.rightHand->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("hand"));
	_info.rightHand->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	_info.rightHand->GetTransform()->SetPivot(Vector2(-HANDOFFSETX, -HANDOFFSETY));

	//왼손 초기화
	_info.leftHand = CreateObject(this);
	_info.leftHand->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("hand"));
	_info.leftHand->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	_info.leftHand->GetTransform()->SetPivot(Vector2(HANDOFFSETX, -HANDOFFSETY));

	_info.toolObject->SetParent(_info.leftHand);
	_info.toolObject->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y));
}
void Character::initHands()
{
	_info.rightHand->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x - HANDOFFSETX, _transform->GetPosition().y - HANDOFFSETY));
	_info.leftHand->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x + HANDOFFSETX, _transform->GetPosition().y - HANDOFFSETY));
	_info.toolObject->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y));
}


void Character::SetPrisonerRandomName()
{
	string temp = " ";
	int random = RND->getInt(25);
	//int random = 0;
	switch (random)
	{
	case 0:		temp += "양 쌤";
		_description = _description + "\n코딩 교육마로 수많은\n학생들이 눈물 흘리게 한 흉악범.";
		break;
	case 1:		temp += "순우 쌤";
		_description = _description + "\n보충 수업을 해주셨으나\n사용하진 않았다 쟌넨...";
		break;
	case 2:		temp += "김ㅇ희";
		_description = _description + "\n상습 탈주범 이따찌의 후예.\n나뭇잎 마을의 수치...";
		break;
	case 3:		temp += "김ㅇ호";
		_description = _description + "\n초콜릿을 나만 안 준다고 했다...\n깁미쪼꼬렛또!!!!!";
		break;
	case 4:		temp += "김ㅇ균";		break;
	case 5:		temp += "김ㅇ현";		break;
	case 6:		temp += "김ㅇ준";		break;
	case 7:		temp += "김ㅇ윤";		break;
	case 8:		temp += "박ㅇ몽";
		_description = _description + "\n바크나몽!\n두두둥장!";
		break;
	case 9:		temp += "박ㅇ훈";		break;
	case 10:	temp += "박ㅇ욱";		break;
	case 11:	temp += "박ㅇ산";		break;
	case 12:	temp += "박ㅇ호";
		_description = _description + "\n전에 나 무섭다 그랬다...\n밥을 잘 챙겨 줘서 눌러 앉았다.";
		break;
	case 13:	temp += "서ㅇ한";
		_description = _description + "\n생각해봐도 반장은 잘못이 없다.\n누명 쓰고 들어온 듯...";
		break;
	case 14:	temp += "송ㅇ훈";		break;
	case 15:	temp += "심ㅇ찬";		break;
	case 16:	temp += "이ㅇ우";		break;
	case 17:	temp += "이ㅇ태";		break;
	case 18:	temp += "이ㅇ종";		break;
	case 19:	temp += "이ㅇ선";		break;
	case 20:	temp += "장ㅇ수";		break;
	case 21:	temp += "장ㅇ혁";		break;
	case 22:	temp += "조ㅇ혁";		break;
	case 23:	temp += "조ㅇ정";
		_description = _description + "\n붓싼피바다\n현정조...";
		break;
	case 24:	temp += "하ㅇ호";		break;
	default: break;
	}

	_name = _name + temp;

}

void Character::SetPeopleRandomName()
{
	string temp = " ";
	int random = RND->getInt(5);
	switch (random)
	{
	case 0:		temp += "김ㅇ환";
		_description = _description + "\n딴딴한 것을 좋아해서\n수석을 모으는 게 취미이다.";
		break;
	case 1:		temp += "신ㅇ민";
		_description = _description + "\n베스트 드라이버다.\n속도광이긴 한데 운전을 잘 한다.";
		break;
	case 2:		temp += "신ㅇ현";
		_description = _description + "\n참을 인을 잘 쓴다.\n바다와 같은 마음을 가졌다.";
		break;
	case 3:		temp += "정ㅇ원";
		_description = _description + "\n항상 존댓말 하시고 공손하시다.\n저한테 말 놔도 돼요큐ㅠㅠ";
		break;
	case 4:		temp += "최ㅇ호";
		_description = _description + "\n최근에 미용실에 다녀왔다.\n고로 자기 관리를 잘 한다.";
		break;
	default: break;
	}
	_name = _name + temp;
}

bool Character::GetIsInArea(string name)
{
	TileAttribute* area = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);

	if (area)	//지역이 있다면
	{
		if (area->GetIsInArea(_transform->GetIndex())) return true;
		else return false;
	}
	return false;	//지역 자체가 없다.
}
