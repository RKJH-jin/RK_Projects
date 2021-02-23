#pragma once
class camera
{
public:
    //===================================변수 설명===================================//
    typedef struct tagCameraInfo
    {
        float centerX, centerY;                 // 카메라의 중심좌표 X, Y 값
        float cameraWidth, cameraHeight;        // 카메라의 가로 길이, 세로 길이 값
        POINT cameraLT, cameraRB;               // 카메라의 좌상단(LEFT, TOP)과 우하단(RIGHT, BOTTOM) 좌표 값

        float Magnification;                    // 카메라 배율 (추후 업데이트 예정)

        tagCameraInfo()                         // 초기값 설정
        {
            centerX = 0;
            centerY = 0;
            cameraWidth = 0;
            cameraHeight = 0;
            cameraLT.x = 0;
            cameraLT.y = 0;
            cameraRB.x = 0;
            cameraRB.y = 0;
            Magnification = 1;
        }
    }CAMERA_INFO, *LPCAMERA_INFO;

private:
    LPCAMERA_INFO _cameraInfo;                  // 카메라 변수값 선언


public:
    camera();
    ~camera();

    HRESULT init(float x, float y, int width, int height, int mag);               // 카메라 초기값
    void release();

    void updateVertax();                                                          // 메인카메라 좌상단/우하단 좌표 업데이트
    
    inline void setX(float x) { _cameraInfo->centerX = x; }                       // 메인카메라 중심 X좌표 설정
    inline float getX() { return _cameraInfo->centerX; }                          // 메인카메라 중심 X좌표 획득

    inline void setY(float y) { _cameraInfo->centerY = y; }                       // 메인카메라 중심 X좌표 설정
    inline float getY() { return _cameraInfo->centerY; }                          // 메인카메라 중심 X좌표 획득

    inline float setWidth(int width) { _cameraInfo->cameraWidth = width; }        // 메인카메라 가로 길이 설정
    inline float getWidth() { return _cameraInfo->cameraWidth; }                  // 메인카메라 가로 길이 획득
    inline float setHeight(int height) { _cameraInfo->cameraHeight = height; }    // 메인카메라 세로 길이 설정
    inline float getHeight() { return _cameraInfo->cameraHeight; }                // 메인카메라 세로 길이 획득

    inline float getLTX() { return _cameraInfo->cameraLT.x; }                     // 메인카메라 LEFT값 획득
    inline float getLTY() { return _cameraInfo->cameraLT.y; }                     // 메인카메라 TOP값 획득
    inline float getRBX() { return _cameraInfo->cameraRB.x; }                     // 메인카메라 RIGHT값 획득
    inline float getRBY() { return _cameraInfo->cameraRB.y; }                     // 메인카메라 BOTTOM값 획득
    
};

