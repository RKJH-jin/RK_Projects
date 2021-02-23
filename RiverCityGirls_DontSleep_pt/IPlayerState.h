#pragma once
#include "gameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"

class IPlayerState: public gameNode
{
protected:
	Player* _thisPl;

	bool _isCollision;	//에너미와 충돌했는지
	float _stateTimer;	//상태가 변경되는 타이머

public:
	IPlayerState() {}
	~IPlayerState() {}

	//플레이어 링커
	void LinkPlAddress(Player* pl) { _thisPl = pl; }

	//상태마다의 동작
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

	//걷기동작
	void walkPattern();
	//기본동작 (걷기/약공/가드)
	void basePattern();

	//오브젝트가 있는지 확인
	bool checkWeapon();

	//에너미가 있는지 확인
	bool checkEnemy();

	//강공격
	void sAttack();

	//상하이동
	void lineMove(float speed);
	//좌우이동
	void crossMove(float speed);
	//사다리 이동
	void ladderMove(float speed);

	//업데이트 일시정지
	bool pauseUpdate();
	//프레임 재생 끝났는지 확인, 리버스 프레임이면 매개변수 true
	bool isEndFrame(bool reverse);
	//무기 떨어뜨리기
	void dropWeapon();
};

