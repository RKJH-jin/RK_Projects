#pragma once
#include "singletonBase.h"
#include <map>

#include "Plugins/inc/fmod.hpp"
#pragma comment(lib, "Plugins/lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 100
#define CHANNELBUFFER 10
#define TOTALCHANNELBUFFER CHANNELBUFFER * 2
#define TOTALALLBUFFER TOTALCHANNELBUFFER + SOUNDBUFFER

enum class tagVolumeType
{
    MUSIC,
    SFX,
    DIALOGUE
};
//===============================channel 인덱스 설명===============================//
// 0 번 채널------------------->BGM (브금)
// 1 번 채널------------------->DIALOGUE (대화)
//================================================================================//

//===============================SFX Channel===============================//
// 0 번 채널부터~~ ------------------->SFX (효과음)
//================================================================================//

class soundManager : public singletonBase<soundManager>
{
private:
    typedef map<string, Sound**>                    arrSounds;
    typedef map<string, Sound**>::iterator          arrSoundsIter;

    typedef map<string, Channel**>                  arrChannels;
    typedef map<string, Channel**>::iterator        arrChannelsIter;
private:
    System*                 _system;
    Sound**                 _sound;

    Channel**               _channel;
    Channel**               _sfxChannel;
    arrSounds               _mTotalSounds;
    arrChannels             _mTotalChannels;

	float _masterVolume;
	float _musicVolume;
	float _dialogueVolume;
	float _sfxVolume;
	
public:         
    soundManager();
    ~soundManager();

    HRESULT init();
    void release();
    void update();

    void addSound(string keyName, string soundName, tagVolumeType volumeType, bool loop);


	//============쓸꺼?============//
    void playMusic(string keyName); // 얘가 브금 재생
    void playDialogue(string keyName); // 얘가 대화 재생
    void playSFX(string keyName); // 얘가 효과음 재생

	void setVolumeMaster(float volume); // 마스터 볼륨
    void setVolumeMusic(float volume);
    void setVolumeDialogue(float volume);
    void setVolumeSFX(float volume);

	void stopMusic(string keyName);
	void pauseMusic(string keyName);
	void resumeMusic(string keyName);
	

    void stop(string keyName);
    void pause(string keyName);
    void resume(string keyName);

    bool isPlaySound(string keyName);
    bool isPauseSound(string keyName);

};

