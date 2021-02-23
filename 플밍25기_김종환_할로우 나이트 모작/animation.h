#pragma once
#include <vector>

class animation
{
private:
    typedef vector<POINT>   vFrameList;     //프레임 리스트 담은 벡터
    typedef vector<int>     vPlayList;    //플레이 리스트 담을 벡터

private:
    int _frameNum;

    vFrameList _vFrameList;
    vPlayList _vPlayList;

    int _frameWidth;
    int _frameHeight;

    BOOL _loop;

    float _frameUpdateSec;
    float _elapsedSec;

    DWORD _nowPlayIndex;
    BOOL _play;


public:
    animation();
    ~animation();

    virtual HRESULT init(int totalW, int totalH, int frameW, int frameH);
    virtual void release();
    
    //애니메이션 재생 디폴트 함수
    void setDefaultPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
    //원하는 부분만 애니메이션 재생 함수
    void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
    //시작 프레임부터 끝프레임까지 구간만 애니메이션 재생
    void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
    //프레임 셋팅
    void setFPS(int framePerSec);
    //프레임 재생 속도 셋팅
    void frameUpdate(float elapsedTime);

    void start();   //애니메이션 재생
    void stop();    //애니메이션 스탑
    void pause();   //애니메이션 일시중지
    void resume();  //애니메이션 다시재생

    inline BOOL isPlay() { return _play; }
    inline POINT getFramePos() { return _vFrameList[_vPlayList[_nowPlayIndex]]; }
    inline int getFrameWidth() { return _frameWidth; }
    inline int getFrameHeight() { return _frameHeight; }
    inline int getNowPlayIndex() { return _nowPlayIndex; }
    inline void setNowPlayIndex(int idx) { _nowPlayIndex = idx; }
    inline BOOL getIsEnd() {
        if (_nowPlayIndex == _frameNum - 1) return true;
        else return false;
    }
    inline vPlayList getPlayList() { return _vPlayList; }
    inline int getFrameNum() { return _frameNum; }
    inline float getElapsedSec() { return _elapsedSec; }
    inline float getFrameUpdateSec() { return _frameUpdateSec; }
};

