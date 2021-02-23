#pragma once
class timer
{
private:
	float _timeScale;			//총 경과시간
	float _timeElapsed;			//Tick (밀리세컨)

	__int64 _curTime;			//현재 시간
	__int64 _lastTime;			//마지막 시간
	__int64 _periodFrequency;	//빈도 수

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }

};

