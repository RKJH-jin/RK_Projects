#pragma once
#include "singletonBase.h"
#include <bitset>
#include <vector>

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase <keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	vector<int> _vKeyComendBuffer;			//키커맨드용버퍼
	SHORT _KeyBuffer;						//실제 키 버퍼
public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//키를 한 번만 눌렀다면
	bool isOnceKeyDown(int key);

	//키를 한 번만 눌렀다면 벡터저장용
	bool isOnceKeyDownV(int key);

	//키를 눌렀다가 떼면
	bool isOnceKeyUp(int key);

	//키를 계속 누르고 있으면
	bool isStayKeyDown(int key);

	//키가 토글되면(?) 
	bool isToggleKey(int key);



	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	//키벡터를 가져온다
	vector<int> getVKeyBuffer() { return _vKeyComendBuffer; }
	//키벡터의 최근인덱스에서 -num한 인덱스의 값을 반환한다.
	int getKeyBuffer(int num) { return _vKeyComendBuffer[_vKeyComendBuffer.size() - num - 1]; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	//받은 키 벡터를 모두 지운다.
	void clearVKey();

};

