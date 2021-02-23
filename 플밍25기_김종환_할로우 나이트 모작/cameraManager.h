#pragma once
#include "singletonBase.h"
#include "camera.h"
#include <map>

class cameraManager : public singletonBase<cameraManager>
{
private:
    typedef map<string, camera*>				mapCameraList;              // 카메라 보관할 Map
    typedef map<string, camera*>::iterator	    mapCameraIter;              

private:
    mapCameraList _mCameraList;                                             // 카메라 보관할 Map
    camera* _mainCamera;                                                    // 메인카메라
    string mc = "mainCamera";                                               // 메인카메라 String 값
    int maxScreenWidth, maxScreenHeight;                                    // 맵 최대 가로 길이, 세로 길이

public:
    cameraManager();
    ~cameraManager();

    HRESULT init();
    void release();

    BOOL deleteCamera(string strKey);
    BOOL deleteAll();

    void setMaxScreen(int width, int height) { maxScreenWidth = width, maxScreenHeight = height; }

    //-----------메인 카메라(Main Camera == MC) 함수-----------//
    void mainCameraUpdate(float x, float y);
    camera* getMainCamera() { return _mainCamera; }
    
    
    void cameraUpdate(string strKey, float x, float y);

    camera* findCamera(string strkey);
    camera* addCamera(string strKey, float x, float y, int width, int height, int mag);

    // 미구현 함수(추후 업데이트 예정)
    void shakeMainCamera();
    void shakeCamera(string strKey);
};

