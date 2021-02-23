#pragma once

class TileAttribute;
class Character;
class MapToolScene;

class DataManager
{
public:
	static DataManager* GetInstance()
	{
		static DataManager istance;
		return &istance;
	}

private:
    struct tagTime
    {
        int day;
        int hour;
        int minute;
        int second;
        float milliSeconds;

        tagTime()
        {
            day = 0;
            hour = 19;
            minute = 0;
            second = 0;
            milliSeconds = 0;
        }
    };

	struct tagDataInfo
	{
		int         money;
		float       gameSpeed = 1.0f;			//게임 변수 (임시로 1로 초기화해둠)
        tagTime     time;
        float       skyAlpha;                //하늘 알파값
        TIMESCHEDULE schedule;
		
		float		soundVolume;			//소리 크기
		float		sfxVolume;			//효과음 크기
		float		bgmVolume;				//배경음 크기

    private:
        //boost
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            if (Archive::is_saving::value)
            {
                ar& gameSpeed;
                ar& money;
                ar& skyAlpha;
                ar& time.day;
                ar& time.hour;
                ar& time.minute;
                ar& time.second;
                ar& time.milliSeconds;
            }

            if (Archive::is_loading::value)
            {
                ar& gameSpeed;
                ar& money;
                ar& skyAlpha;
                ar& time.day;
                ar& time.hour;
                ar& time.minute;
                ar& time.second;
                ar& time.milliSeconds;
            }
        }
	};

	typedef map<string, TileAttribute*> mTileAttribute;
	typedef map<string, TileAttribute*>::iterator miTileAttribute;

	typedef map<string, Character*> mCharacter;
	typedef map<string, Character*>::iterator miCharacter;

	tagDataInfo _info;
	Image* _terrainImg;				//지형 이미지

	mTileAttribute _mTileObject;		//타일 오브젝트를 담은 맵
	mCharacter _mCharacter;				//캐릭터 오브젝트를 담은 맵

	MapToolScene* _mapToolScene;		//맵툴씬

public:
	vector<string> _vStr_buf;		//읽은 문자를 받을 버퍼 테스트

	void init();					//초기화
    void update();                  //내부 데이터 업데이트

	//GETTER
	mTileAttribute* GetMTileObject() { return &_mTileObject; }
	TileAttribute* FindTileObject(string key);
	TileAttribute* CreateTileObject(string key);

    string GetTimeSchedule();
	Character* FindCharacter(string key);
	Character* CreateCharacter(string key);
	mCharacter* GetMCharacter() { return &_mCharacter; }

	MapToolScene* GetMapToolScene() { return _mapToolScene; }

	//링커
	void SetLinkMapToolScene(MapToolScene* mapToolScene) { _mapToolScene = mapToolScene; };

	tagDataInfo& GetInfo() { return _info; }

	Image* GetTerrainImage() { return _terrainImg; }

	//SETTER

	//FUNCTION
	void UpdateTime();
    void Save();
    void Load();


};

