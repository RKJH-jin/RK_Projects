#pragma once


/*====================================================================
							선형 보간 유틸
====================================================================*/
class Interpolation
{
private:
	vector3* _pos;
	float _startX, _startY;
	float _endX, _endY;

	float _angle;
	float _travelRange;
	float _worldTimeCount;
	float _time;

	bool _isMoving;

public:
	Interpolation();
	~Interpolation() {};

	//업데이트
	void update();
	
	//n초 동안 x,y를 향해 움직임
	void moveTo(vector3* pos, float endX, float endY, float time);

	//움직이는 중
	void moving();

	//Getter
	bool getIsMoving() { return _isMoving; }

};

