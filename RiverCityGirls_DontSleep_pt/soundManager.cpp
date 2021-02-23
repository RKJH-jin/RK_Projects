#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
    : _system(nullptr),
    _channel(nullptr),
    _sound(nullptr)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
    // FMOD 엔진 초기화
    System_Create(&_system);

    // system 초기화
    _system->init(TOTALALLBUFFER, FMOD_INIT_NORMAL, NULL);

	
    // 사운드 채널 생성
    _sound = new Sound*[SOUNDBUFFER];
    _channel = new Channel*[CHANNELBUFFER]; // 포인터 배열
    _sfxChannel = new Channel*[CHANNELBUFFER];

    // 메모리 공간 할당
    memset(_sound, 0, sizeof(Sound*) * SOUNDBUFFER);
    memset(_channel, 0, sizeof(Channel*) * CHANNELBUFFER);
    memset(_sfxChannel, 0, sizeof(Channel*) * CHANNELBUFFER);

	_masterVolume = 0.1f;
	_musicVolume = 0.1f;
	_dialogueVolume = 0.1f;
	_sfxVolume = 0.01f;
    return S_OK;
}

void soundManager::release()
{
    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }

   
	delete[] _sound;
    delete[] _channel;
    delete[] _sfxChannel;
	
}

void soundManager::update()
{
    _system->update();
}

void soundManager::addSound(string keyName, string soundName, tagVolumeType volumeType, bool loop)
{
	
    if (loop)
    {
        switch (volumeType)
        {
		case tagVolumeType::SFX:
            _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
            break;
        case tagVolumeType::DIALOGUE: case  tagVolumeType::MUSIC: 
            _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
            break;
		default:
			break;
        }
    }
    else
    {
        switch (volumeType)
        {
        case  tagVolumeType::SFX:
            _system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
            break;
        case  tagVolumeType::DIALOGUE: case tagVolumeType::MUSIC:
            _system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
            break;
		default:
			break;
        }
    }
    _mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()])); // 포인터 배열에 들어있는 해당 포인터의 주소값
    
}



void soundManager::playMusic(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    for (iter; iter != _mTotalSounds.end(); ++iter)
    {
        if (keyName == iter->first)
        {
            _channel[0]->stop();
            // 사운드가 계속 재생하려는데 끊기고 안나온다 싶으면 FMOD_CHANNEL_FREE를 바꿔서!
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[0]);
            _channel[0]->setVolume(_musicVolume);
            break;
        }
    }
}

void soundManager::playDialogue(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    for (iter; iter != _mTotalSounds.end(); ++iter)
    {
        if (keyName == iter->first)
        {
            _channel[1]->stop();
            // 사운드가 계속 재생하려는데 끊기고 안나온다 싶으면 FMOD_CHANNEL_FREE를 바꿔서!
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[1]);
            _channel[1]->setVolume(_dialogueVolume);
            break;
        }
    }
}

void soundManager::playSFX(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
			for (int j = 0; j < CHANNELBUFFER; ++j)
			{
				bool check;
				_sfxChannel[j]->isPlaying(&check);
				if (check) continue;
				_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_sfxChannel[j]);
				_sfxChannel[j]->setVolume(_sfxVolume);
			}
            // 사운드가 계속 재생하려는데 끊기고 안나온다 싶으면 FMOD_CHANNEL_FREE를 바꿔서!
            break;
        }
    }
}

void soundManager::setVolumeMaster(float volume)
{
	_masterVolume = volume;
	

	setVolumeMusic(_musicVolume);
	setVolumeDialogue(_dialogueVolume);
	setVolumeSFX(_sfxVolume);
}

void soundManager::setVolumeMusic(float volume)
{
	_musicVolume = volume;
    _channel[0]->setVolume(_masterVolume * _musicVolume);
}

void soundManager::setVolumeDialogue(float volume)
{
	_dialogueVolume = volume;
    _channel[1]->setVolume(_masterVolume * _dialogueVolume);
}

void soundManager::setVolumeSFX(float volume)
{
	_sfxVolume = volume;
    for (int i = 0; i < CHANNELBUFFER; ++i)
    {
        _sfxChannel[i]->setVolume(_masterVolume * _sfxVolume);
    }
}

void soundManager::stopMusic(string keyName)
{
	_channel[0]->stop();
}

void soundManager::pauseMusic(string keyName)
{
	_channel[0]->setPaused(true);
}

void soundManager::resumeMusic(string keyName)
{
	_channel[0]->setPaused(false);
}

void soundManager::stop(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->stop();
            break;
        }
    }
}

void soundManager::pause(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();
    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(true);
            break;
        }
    }
}

void soundManager::resume(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(false);
            break;
        }
    }
}

bool soundManager::isPlaySound(string keyName)
{
    bool isPlay;
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPlay);
            break;
        }
    }
    return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
    bool isPause;
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->getPaused(&isPause);
            break;
        }
    }
    return isPause;

}
