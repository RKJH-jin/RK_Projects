#include "stdafx.h"
#include "Player.h"
//외부
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "ItemObj.h"
#include "Object.h"
#include "pet.h"
#include "Enemy.h"

//상태
#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerClimb.h"
#include "playerClimbTop.h"
#include "playerPick.h"
#include "playerGrab.h"
#include "playerGuard.h"
#include "playerRoll.h"
#include "playerHit.h"
#include "playerStun.h"
#include "playerStand.h"
#include "playerDown.h"
#include "playerDead.h"
#include "playerThrow.h"
#include "playerStomp.h"
#include "playerCombo1.h"
#include "playerCombo2.h"
#include "playerCombo3.h"
#include "playerSAttack.h"
#include "playerDashAttack.h"
#include "playerDashSAttack.h"
#include "playerJumpAttack.h"
#include "playerSAttackDown.h"

#include "Weapon.h"
//초기화
HRESULT Player::init()
{
	/*====================================================================
		플래이어의 오브젝트 초기화와 기본 설정을 합니다.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wait"), vector3(WINSIZEX / 4, 0, WINSIZEY / 2 + 250));
	_shadow.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("shadow"), vector3(WINSIZEX / 4, 0, WINSIZEY / 2 + 250));
	//기본 변수 초기화
	{
		_obj.ani = new animation;
		_info.jumpPower = 0;
		_info.speed = 4.f;
		_info.hasMember = false;
		_info.hasWeapon = false;
		_info.isImmune = false;
		_info.isAttack = false;
		_info.isHit = false;
		_info.isDead = false;
		_info.isControl = true;
		_info.isConDest = true;
		_info.isSky = false;
		_info.isClimb = false;
		_info.isRestart = false;
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
		_info.goalState = GOALPOS::PLAYER;

		_info.hp = _info.maxHP = 100;
		_info.force = 10;
		_info.LV = 1;
		_info.exp = 0;
		_info.coin = 10;
		_info.hitCount = 3;

		_info.frameTimer = TIME_M->getWorldTime();
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		_info.immuneTimer = 0;

		_pet.init();
	}

	//상태패턴 등록
	{
		_idle = new playerIdle;
		_wait = new playerWait;
		_walk = new playerWalk;
		_run = new playerRun;
		_jump = new playerJump;
		_stick = new playerStick;
		_climb = new playerClimb;
		_climbTop = new playerClimbTop;
		_pick = new playerPick;

		_grab = new playerGrab;
		_guard = new playerGuard;
		_roll = new playerRoll;
		_hit = new playerHit;
		_stun = new playerStun;
		_stand = new playerStand;
		_down = new playerDown;
		_dead = new playerDead;

		_throw = new playerThrow;
		_stomp = new playerStomp;
		_combo1 = new playerCombo1;
		_combo2 = new playerCombo2;
		_combo3 = new playerCombo3;

		_sAttack = new playerSAttack;
		_dashAttack = new playerDashAttack;
		_dashSAttack = new playerDashSAttack;
		_jumpAttack = new playerJumpAttack;
		_SAttackDown = new playerSAttackDown;
	}
	setState(PL_STATE::WAIT);


	//인벤추가
	UI_M->setLinkPlayer(this);
	UI_M->addPhone("inven");

	return S_OK;
}

void Player::release()
{
}

//업뎃 순서 중요함★ 상태->중력->키입력
void Player::update()
{
	//엔딩유아이가 실행중이면 컨트롤을 막는다.
	//if (UI_M->findUI("endingUI")->_isActive)_info.isControl = false;

	_pet.update(vector3(_obj.pos.x, _obj.pos.y, _obj.pos.z));
	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;

	//상태업데이트
	_IState->UpdateState();

	//중력작용
	gravity();

	//키입력
	keyInput();

	//맞기
	hit();
	//무기 업뎃
	if (_info.attackObj != NULL)weaponUpdate();
	//아이템 상호작용
	checkItem();

	//오브젝트 업뎃
	_obj.update();
	_obj.shadowUpdate();

	//애니 프레임 업뎃
	if (_info.rendType == RENDERTYPE::ANI_RENDER) _obj.ani->frameUpdate(TIME_M->getElapsedTime() * 7);

	//프레임업뎃
	playFrame();

	if (KEY_M->isOnceKeyDown(VK_NUMPAD0))
	{
		cout << "그림자 LT X: " << _obj.shadow.LT.x << endl;
		cout << "그림자 LT Y: " << _obj.shadow.LT.y << endl;
		cout << "그림자 LT Z: " << _obj.shadow.LT.z << endl;

		cout << "그림자 pos X: " << _obj.shadow.pos.x << endl;
		cout << "그림자 pos Y: " << _obj.shadow.pos.y << endl;
		cout << "그림자 pos Z: " << _obj.shadow.pos.z << endl;

		cout << "캐릭터 X: " << _obj.pos.x << endl;
		cout << "캐릭터 Y: " << _obj.pos.y << endl;
		cout << "캐릭터 Z: " << _obj.pos.z << endl;
		if (_platform != nullptr)
		{
			cout << "플랫폼 X: " << _platform->bottomPlane[0].getEnd().x << endl;
			cout << "플랫폼 Y: " << _platform->bottomPlane[0].getEnd().y << endl;
			cout << "플랫폼 Z: " << _platform->bottomPlane[0].getEnd().z << endl;
		}
		else cout << "NULL" << endl;
	}
	_colM->destructObject();
	_shadow.pos = _obj.pos;
}

//렌더
void Player::render()
{
	/*====================================================================
		Z-ORDER에 따라 알파 프레임 렌더 시킵니다.
	====================================================================*/
	_pet.render(getMapDC());
	//플래이어 오브젝트 렌더

	if (_platform)
	{ _shadow.pos.y = _platform->pos.y-70;

	if (_info.isSky)
	{

		if (KEY_M->isStayKeyDown(VK_LEFT) || KEY_M->isStayKeyDown(VK_RIGHT))
		{
			 _shadow.pos.y = 20;

		}

	}



	}
	else _shadow.pos.y = 20;

	//_shadow.alpha = ((int)_shadow.pos.y - 21) % 255;
	_shadow.alpha = (unsigned int)(255 - abs(_obj.pos.y - _shadow.pos.y));
	

	ZORDER_M->renderObject(getMapDC(), &_shadow, RENDERTYPE::RENDER);
	ZORDER_M->renderObject(getMapDC(), &_obj, _info.rendType);
	

	//무기를 가지고 있을 때(던져버렸을때 던져지는 무기를 렌더)
	if (!_info.hasWeapon)
	{
		//오브젝트참조를 잃지 않았고, 렌더상태라면
		if (_info.attackObj != NULL && _info.attackObj->isRender)
			ZORDER_M->renderObject(getMapDC(), _info.attackObj, RENDERTYPE::FRAME_RENDER);
	}

	vector3 shadowPos = _obj.pos;

	RECT shadow = RectMakeCenter(shadowPos.x, shadowPos.z+shadowPos.y, _obj.shadow.width, _obj.shadow.height*2);



	//디버깅 시 렉트 렌더
	if (KEY_M->isToggleKey(VK_SHIFT))
	{
		Rectangle(getMapDC(), shadow);

		//Rectangle(getMapDC(), _obj.shadow.rc);

		//Rectangle(getMapDC(), _obj.shadow.rc);
	//	if (_info.isAttack) Rectangle(getMapDC(), _info.attackRc);
	}

}

//상태 지정
void Player::setState(PL_STATE state)
{
	if (_info.state == state)return;	//같은 상태면 변경하지 않는다.
	_info.preState = _info.state;		//변경 전 현재 상태를 저장한다.
	_info.state = state;				//현재 상태를 변경한다.

	//상태를 빠져나온다
	if (_IState != NULL) _IState->ExitState();

	//상태를 변경한다
	switch (_info.state)
	{
		//기본동작
	case PL_STATE::IDLE:	    _IState = _idle;		 break;
	case PL_STATE::WAIT:	    _IState = _wait;		 break;
	case PL_STATE::WALK:	    _IState = _walk;		 break;
	case PL_STATE::RUN:		    _IState = _run;			 break;
	case PL_STATE::JUMP:		_IState = _jump;		 break;
	case PL_STATE::STICK:	    _IState = _stick;		 break;
	case PL_STATE::CLIMB:      _IState = _climb;		 break;
	case PL_STATE::CLIMBTOP:   _IState = _climbTop;		 break;
	case PL_STATE::PICK:      _IState = _pick;			 break;
		//가드 및 피격
	case PL_STATE::GRAB:       _IState = _grab;			 break;
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::ROLL:       _IState = _roll;			 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:		_IState = _stand;		 break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// 공격
	case PL_STATE::THROW:	    _IState = _throw;		 break;
	case PL_STATE::STOMP:	    _IState = _stomp;		 break;
	case PL_STATE::COMBO1:	    _IState = _combo1;		 break;
	case PL_STATE::COMBO2:	    _IState = _combo2;		 break;
	case PL_STATE::COMBO3:	    _IState = _combo3;		 break;
	case PL_STATE::SATTACK:     _IState = _sAttack;		 break;
	case PL_STATE::DASHATTACK:  _IState = _dashAttack;	 break;
	case PL_STATE::DASHSATTACK: _IState = _dashSAttack;  break;
	case PL_STATE::JUMPATTACK:  _IState = _jumpAttack;	 break;
	case PL_STATE::SATTACKDOWN: _IState = _SAttackDown;  break;
	default: break;
	}

	//상태에 링크하고 진입한다.
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}

//같은 줄 유무
bool Player::isRange(GameObject obj)
{
	//위치 차이가 15미만이면
	if (abs(_obj.pos.z - obj.pos.z) < 40) return true;
	return false;
}

//같은 줄 유무
bool Player::isRange(GameObject obj, float value)
{
	//위치 차이가 값 미만이면
	if (abs(_obj.pos.z - obj.pos.z) < value) return true;
	return false;
}

//무기업뎃
void Player::weaponUpdate()
{
	if (!_info.attackObj) return;

	switch (_info.goalState)
	{
	case GOALPOS::PLAYER:
		break;
	case GOALPOS::WINOUT:
		//골로 이동하다가 화면골에 가면 골상태를 바닥으로 변경
		if (moveAttackObj())
		{
			if (_info.dest == DIRECTION::RIGHT) _info.attackGoal.x -= 30;
			if (_info.dest == DIRECTION::LEFT) _info.attackGoal.x += 30;
			_info.attackGoal.y = 0;
			_info.goalState = GOALPOS::FLOOR;
		}
		break;
	case GOALPOS::FLOOR:
		if (moveAttackObj())
		{
			_info.attackObj->isActive = true;
			_info.attackObj->isRender = true;
			_info.goalState = GOALPOS::PLAYER;
			_objectM->pushWeapon(WEAPON_TYPE::BAT, vector3(_info.attackGoal.x, _info.attackGoal.y, _info.attackGoal.z));
			_info.attackObj = NULL;
		}
		break;
	}
}

bool Player::moveAttackObj()
{
	_info.attackObj->pos.x += cosf(getAngle(_info.attackObj->pos.x, 0, _info.attackGoal.x, 0)) * 6.0f;

	_info.attackObj->pos.z -= sinf(getAngle(0, _info.attackObj->pos.z, 0, _info.attackGoal.z)) * 6.0f;

	_info.attackObj->pos.y -= sinf(getAngle(0, _info.attackObj->pos.y, 0, _info.attackGoal.y)) * 6.0f;

	//공격 렉트를 어택 오브젝트의 위치에 맞춤.
	_info.attackRc = RectMakeCenter(_info.attackObj->pos.x,
		_info.attackObj->pos.z + _info.attackObj->pos.y,
		_info.attackObj->size.x + 200, _info.attackObj->size.z + 100);

	if (getDistance(_info.attackObj->pos.x, _info.attackObj->pos.z + _info.attackObj->pos.y,
		_info.attackGoal.x, _info.attackGoal.z + _info.attackGoal.y) < 5)
	{
		_info.attackObj->pos.x = _info.attackGoal.x;
		_info.attackObj->pos.y = _info.attackGoal.y;
		_info.attackObj->pos.z = _info.attackGoal.z;
		return true;
	}
	return false;
}

void Player::hit()
{
	//이뮨타이머 갱신
	if (!_info.isImmune)
		_info.immuneTimer = TIME_M->getWorldTime();

	//이뮨상태라면 4초후에 돌아가기
	if (_info.isImmune && TIME_M->getWorldTime() - _info.immuneTimer > 4.f)
	{
		_info.isImmune = false;
		_obj.alpha = 255;
	}

	//플레이어가 죽었으면 죽음처리
	if (_info.hp <= 0)setState(PL_STATE::DEAD);

	//죽은게 아닐때 기절이 아닐때
	if (_info.state != PL_STATE::DEAD && !_info.isImmune && _info.state != PL_STATE::STUN)
	{
		//가드상태가 아닐때 
		if (_info.state != PL_STATE::GUARD)
		{
			for (int i = 0; i != _enemyM->getVEnemy().size(); i++)
			{
				if (_enemyM->getVEnemy()[i]->getInfo().isAttack)
				{
					RECT temp;
					if (IntersectRect(&temp, &_obj.rc, &_enemyM->getVEnemy()[i]->getInfo().rcAttack)
						&& isRange(_enemyM->getVEnemy()[i]->getRefObj()))
					{
						_info.hp -= _enemyM->getVEnemy()[i]->getInfo().attack;
						if (_info.hitCount >= 4)
						{
							//맞은 수 초기화
							_info.hitCount = 0;
							if (_info.hp <= 10)setState(PL_STATE::STUN);
							if (_info.hp > 10)setState(PL_STATE::DOWN);
						}
						else setState(PL_STATE::HIT);
						break;
					}
				}
			}


		}

	}
	//체력이 0보다 작아지면 0으로 고정
	if (_info.hp <= 0)_info.hp = 0;
}

//스테이지가 바뀔 때마다 초기화시키는 함수
void Player::stageInit()
{
	/*====================================================================
		스테이지가 바뀔 때마다 초기화시키는 함수입니다.
	====================================================================*/
	switch (_stageM->getCurStage()) // 현재 스테이지는?
	{
	case STAGETYPE::EASY: // 현재 스테이지가 이지면
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // 이전 스테이지가 노말이였으면
		{
			_obj.setPosX(1445);
			_obj.setPosY(0);
			_obj.setPosZ(420);
		}
		break;
	case STAGETYPE::NORMAL:  // 현재 스테이지가 노말이면
		if (_stageM->getPreStage() == STAGETYPE::EASY) // 이전 스테이지가 노말이였으면
		{
			_obj.setPosX(180);
			_obj.setPosY(0);
			_obj.setPosZ(700);
		}
		else if (_stageM->getPreStage() == STAGETYPE::HARD) // 이전 스테이지가 하드이였으면
		{
			_obj.setPosX(2645);
			_obj.setPosY(0);
			_obj.setPosZ(670);
		}
		break;
	case STAGETYPE::HARD: // 현재 스테이지가 하드면
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // 이전 스테이지가 노말이였으면
		{
			_obj.setPosX(270);
			_obj.setPosY(0);
			_obj.setPosZ(480);
		}
		else if (_stageM->getPreStage() == STAGETYPE::BOSS) // 이전 스테이지가 보스였으면
		{
			_obj.setPosX(2070);
			_obj.setPosY(0);
			_obj.setPosZ(1370);
		}
		break;
	case STAGETYPE::BOSS: // 현재 스테이지가 보스면
		if (_stageM->getPreStage() == STAGETYPE::HARD) // 이전 스테이지가 하드이였으면
		{
			_obj.setPosX(450);
			_obj.setPosY(0);
			_obj.setPosZ(880);
		}
		break;
	default:
		break;
	}

	/*====================================================================
		링크 : 에너미매니저, 오브젝트 매니저와 링크합니다.
	====================================================================*/
	_enemyM = _stageM->getStage()->getEnemyM();
	_objectM = _stageM->getStage()->getObjectM();
}

//이미지 변경
void Player::changeImg(string imgName, bool reverse)
{
	//이미지를 바꾼다.
	_obj.img = IMG_M->findImage(imgName);

	//방향과 리버스 여부 따른 프레임 x 인덱스 설정
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		if (!reverse)_obj.imgIndex.x = 0;
		else if (reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX();
		_obj.imgIndex.y = 0;
		break;

	case DIRECTION::RIGHT:
		if (!reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX();
		else if (reverse)_obj.imgIndex.x = 0;
		_obj.imgIndex.y = 1;
		break;
	}

	//프레임 시간 갱신하여 바로 프레임 변경
	_info.frameTimer = TIME_M->getWorldTime();

}

//프레임 연산
void Player::setFrame(FRAMETYPE frameType, float frameInterval)
{
	//프레임 y 번호 설정
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}
	if (_info.state == PL_STATE::CLIMB || _info.state == PL_STATE::CLIMBTOP)
		_obj.imgIndex.y = 0;
	//프레임 y 번호 세팅
	_obj.img->setFrameY((int)_info.dest);

	//프레임 실행 시간 설정
	if (TIME_M->getWorldTime() - _info.frameTimer > frameInterval)
	{
		//시간 갱신
		_info.frameTimer = TIME_M->getWorldTime();
		switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if (frameType != FRAMETYPE::REVERSELOOP && frameType != FRAMETYPE::REVERSEONCE) ++_obj.imgIndex.x;
			else --_obj.imgIndex.x;


			break;
		case DIRECTION::RIGHT:
			if (frameType != FRAMETYPE::REVERSELOOP&& frameType != FRAMETYPE::REVERSEONCE) --_obj.imgIndex.x;
			else  ++_obj.imgIndex.x;
			break;
		}
	}

	//프레임 x 번호 조절
	switch (frameType)
	{
	case FRAMETYPE::ONCE://한 번 재생
	{
		//왼쪽의 경우 x인덱스가 0번부터~ 끝번까지 프레임이 다 되면 끝번호로 프레임번호 고정
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		//오른쪽의 경우 x인덱스가 끝번부터 0번까지 프레임이 다 되면 0번으로 프레임 번호 고정
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0;
		}

	}
	break;
	case FRAMETYPE::LOOP://무한 재생
	{
		//왼쪽의 경우 x인덱스가 0번부터~ 끝번까지 프레임이 다 되면 끝번호로 프레임번호 0번으로 갱신
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//오른쪽의 경우 x인덱스가 끝번부터 0번까지 프레임이 다 되면 0번으로 프레임 번호 끝번호로 갱신
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
	}
	break;
	case FRAMETYPE::REVERSEONCE://반대 한번 재생
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0; return;
		}
	}
	break;
	case FRAMETYPE::REVERSELOOP://반대 무한 재생
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();

	}
	break;
	}

}

//프레임 실행
void Player::playFrame()
{
	switch (_info.state)
	{
		//무한재생 (일반 속도)
	case PL_STATE::WAIT:

		setFrame(FRAMETYPE::LOOP, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//반대 무한재생 (빨리)
	case PL_STATE::RUN:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL*0.35);
		break;
		//반대 무한재생
	case PL_STATE::STUN:
	case PL_STATE::IDLE:	case PL_STATE::WALK:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL);
		break;

		//한번 (천천히)
	case PL_STATE::PICK:	case PL_STATE::GRAB:
	case PL_STATE::STICK:	case PL_STATE::HIT:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 3);
	case PL_STATE::CLIMBTOP:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 5);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//한번 (일반 속도)
	case PL_STATE::JUMP:
	case PL_STATE::ROLL:
	case PL_STATE::STAND:
	case PL_STATE::DOWN:	case PL_STATE::DEAD:
	case PL_STATE::THROW:
	case PL_STATE::COMBO1:	case PL_STATE::COMBO2:
	case PL_STATE::COMBO3:	case PL_STATE::SATTACK:
	case PL_STATE::DASHSATTACK:
	case PL_STATE::JUMPATTACK:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//반대 한번재생 (일반 속도)
	case PL_STATE::STOMP:
	case PL_STATE::DASHATTACK:	case PL_STATE::SATTACKDOWN:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//반대 한번재생 (빨리)
	case PL_STATE::GUARD:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL*0.4);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//애니랜더
	case PL_STATE::CLIMB:
		_info.rendType = RENDERTYPE::ANI_RENDER;
		_obj.ani->setFPS(1);
		break;
	}

}

//좌표이동
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//그림자만 일단 한번 업데이트 (충돌처리를 위한 거! 건드리면 안됨!)
	_obj.shadowUpdate();

	//충돌처리 
	_colM->playerObjectCollision();

	//그림자 아래로 안 떨어지도록 예외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//최종 렉트 갱신
	_obj.update();
}

//좌표설정
void Player::setPos(float x, float z, float y)
{
	_obj.pos.x = x;
	_obj.pos.z = z;
	_obj.pos.y = y;

	//그림자만 일단 한번 업데이트 (충돌처리를 위한거! 건드리면 안됨!)
	_obj.shadowUpdate();

	//충돌처리 
	_colM->playerObjectCollision();

	//그림자 아래로 안 떨어지도록 예외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//최종 렉트 갱신
	_obj.update();
}

//아이템이랑 상호작용
void Player::checkItem()
{
	RECT temp;
	for (int i = 0; i != _objectM->getVObject().size(); i++)
	{
		//활성화 상태일때
		if (_objectM->getVObject()[i]->getObj()->isActive)
		{
			// 충돌한다면
			if (IntersectRect(&temp, &_obj.rc, &_objectM->getVObject()[i]->getRefObj().rc))
			{
				if (_objectM->getVObject()[i]->getObj()->weaponType == WEAPON_TYPE::NONE)
				{
					switch (_objectM->getVObject()[i]->getInfo().type)
					{
						//소지금 올려줌
					case ITEM_TYPE::MONEY:
					case ITEM_TYPE::COIN:
						_objectM->getVObject()[i]->getObj()->isActive = false;
						_info.coin += _objectM->getVObject()[i]->getInfo().value;
						_objectM->popObject(i);
						if (i == _objectM->getVObject().size())return;
						break;
						//체력회복
					case ITEM_TYPE::MEAT:
					case ITEM_TYPE::APPLE:
					case ITEM_TYPE::HEN:
					case ITEM_TYPE::CHILI:
					{
						if (_info.hp < _info.maxHP)
						{
							_info.hp += _objectM->getVObject()[i]->getInfo().value;
							_objectM->popObject(i);
							if (_info.hp > _info.maxHP)_info.hp = _info.maxHP;
							if (i == _objectM->getVObject().size())return;
						}
					}
					break;
					}
				}
			}
		}
	}

	//체력수치 보정
	if (_info.hp > _info.maxHP)
	{
		_info.hp = _info.maxHP;
	}
}


//중력작용
void Player::gravity()
{
	if (_info.isSky) _info.jumpPower -= GRAVITY;
	if (_obj.pos.y >= 0 && _info.isSky)
	{
		setState(PL_STATE::IDLE);
		//걷거나 뛰고있었고, 키를 계속 누르고있으면 그 상태 그대로돌아오기
		if (_info.preState == PL_STATE::WALK || _info.preState == PL_STATE::RUN)
		{
			if (_info.dest == DIRECTION::LEFT && KEY_M->isStayKeyDown(VK_LEFT))setState(_info.preState);
			if (_info.dest == DIRECTION::RIGHT && KEY_M->isStayKeyDown(VK_RIGHT))setState(_info.preState);
		}
		_info.isSky = false;
		_info.isAttack = false;
		_platform = nullptr;
	}
	if (_obj.pos.y > 0) _info.jumpPower = 0;
	movePos(0, 0, _info.jumpPower);
}

//키입력
void Player::keyInput()
{
	//키조작을 못하는 상태라면 리턴
	if (!_info.isControl) return;

	//인벤토리창 열기
	if (UI_M->findUI("inven")->_isActive && KEY_M->isOnceKeyDown('I')) UI_M->findUI("inven")->setActive(false);
	if (!UI_M->findUI("inven")->_isActive && KEY_M->isOnceKeyDown('I')) UI_M->findUI("inven")->setActive(true);


	//공격키받기(커맨드를위해)
	if (KEY_M->isOnceKeyDownV('D'));

	//사다리오르기
	if (_info.isClimb && (GetAsyncKeyState(VK_UP) & 0x8000)) setState(PL_STATE::CLIMB);

	//점프
	if (KEY_M->isOnceKeyDownV('A') && !_info.isSky)
	{
		//이전상태 저장
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWER;
		movePos(0, 0, JUMPPOWER);
		//점프파워가 - 면 점프상태로 전환
		if (_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}
	//구르기
	if (KEY_M->isOnceKeyDownV('W') && !_info.isSky)
	{
		//이전상태 저장
		_info.preState = _info.state;
		setState(PL_STATE::ROLL);
	}

	//방향조작을 못하는 상태라면 리턴
	if (!_info.isConDest) return;

	//왼
	if (KEY_M->isOnceKeyDownV(VK_LEFT) || KEY_M->isStayKeyDown(VK_LEFT))
	{
		_info.moveDest = MOVE_DIRECTION::LEFT;
		_info.dest = DIRECTION::LEFT;
	}
	//오
	if (KEY_M->isOnceKeyDownV(VK_RIGHT) || KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
	}
	//위
	if (KEY_M->isOnceKeyDownV(VK_UP) || KEY_M->isStayKeyDown(VK_UP))_info.moveDest = MOVE_DIRECTION::UP;
	//아래
	if (KEY_M->isOnceKeyDownV(VK_DOWN) || KEY_M->isStayKeyDown(VK_DOWN))_info.moveDest = MOVE_DIRECTION::DOWN;


	//키커맨드 
	if (!_info.isSky && KEY_M->getVKeyBuffer().size() >= 3)
	{
		//바라보는 방향키+ ↓ + d 커맨드 공격
		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_RIGHT && _info.dest == DIRECTION::RIGHT)
			setState(PL_STATE::SATTACKDOWN);

		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_LEFT && _info.dest == DIRECTION::LEFT)
			setState(PL_STATE::SATTACKDOWN);

	}
}
