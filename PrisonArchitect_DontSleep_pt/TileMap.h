#pragma once

#include "Tile.h"
#include "TileObject.h"

class TileMap
{
public:
	static TileMap* GetInstance()
	{
		static TileMap istance;
		return &istance;
	}

protected:
	vector<Tile*> _vTile;				//타일 벡터

	Vector2 _count;						//타일 x, y 개수
	int _tileCount;						//전체 타일 개수

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Vector2 GetCount() { return _count; }

	//타일맵을 세팅함
	void SetTileMap(Vector2 count);

	//타일 오브젝트를 생성
	void BuildTileObject(Vector2 index, TileAttribute* tileObj);

	//타일 오브젝트 파괴
	void DestroyTileObject(TileAttribute* tileObj);

	//벽의 오토타일 프레임을 구해 줌
	Vector2 GetWallFrame(Vector2 index, TileAttribute* tileObj);
	
	//타일에 지을 수 있는지 확인 해 줌
	bool CanBuildTile(Vector2 index, TileAttribute* tileObj);

	//타일 오브젝트를 찾아 줌
	TileAttribute* FindTileObject(string key);

	//GETTER
	vector<Tile*> GetvTile() { return _vTile; }

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _vTile;
            ar& _tileCount;
            ar& _count;
        }

        if (Archive::is_loading::value)
        {
            ar& _vTile;
            ar& _tileCount;
            ar& _count;
        }
    }
};

