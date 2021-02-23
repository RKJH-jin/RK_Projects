#pragma once
#include "TileMap.h"

class MapManager
{
private:
	typedef vector<Character*> vCharacter;
	typedef vector<StuffObject*> vStuffObj;

private:
	TileMap* _tileMap;			//타일 맵

	vCharacter _vCharacter;		//캐릭터 벡터
	vStuffObj _vStuffObj;		//아이템 벡터

	//Y-Order 벡터
	vector<GameObject*> _vYOrderObject;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	/*====================================================
							GETTER
	====================================================*/
	TileMap* GetTileMap() { return _tileMap; }
	vCharacter& GetVCharacter() { return _vCharacter; }
	vStuffObj& GetVStuffObj() { return _vStuffObj; }

	/*====================================================
							스터프
	====================================================*/
	//스터프 오브젝트를 찾아 줌
	StuffObject* FindStuffObject(string key);

	/*====================================================
							캐릭터
	====================================================*/
	//캐릭터를 생성 함
	void CreateCharacter(Vector2 pos, Character* obj);
	
	//캐릭터를 삭제 함
	void DeleteCharacter(int i);

	/*====================================================
							Y-Order
	====================================================*/
	void SortYOrder(int s, int e);
	void RenderYOrder();

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _tileMap;
        }

        if (Archive::is_loading::value)
        {
            ar& _tileMap;
        }
    }
};

