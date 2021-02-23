#pragma once
#include "singletonBase.h"
#include <bitset>

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();
	//Ű�� �� �� ������
	bool isOnceKeyDown(int key);
	//Ű�� �����ٰ� ����
	bool isOnceKeyUp(int key);
	//Ű�� ��� ������ ������
	bool isStayKeyDown(int key);
	//Ű�� ��۵Ǹ�
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};
