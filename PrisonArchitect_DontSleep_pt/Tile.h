#pragma once

class TileAttribute;

class Tile
{
public:
    struct tagCost
    {
        int totalCost;              //총 비용
        int costFromStart;          //출발지점으로부터의 비용
        int costToGoal;             //목적지까지의 비용
        tagCost()
        {
            totalCost = 0;
            costFromStart = 0;
            costToGoal = 0;
        }
    };
public:
	Vector2 _index;				//인덱스
	RECT _rc;					//렉트

	TileAttribute* _terrain;		//지형
	
	TileAttribute* _wall;			//벽

	TileAttribute* _tileObj;		//타일 오브젝트
	
	TileAttribute* _area;			//지역

    //길찾기에서 쓰는 변수들
    SEARCHDIRECTION _sDir;        //탐색하던 방향
    Tile* _parentTile;           //부모 타일 
    tagCost _cost;               //비용

public:
    //GETTER
	Vector2 GetIndex() { return _index; }
    
    //SETTER
    void SetIndex(Vector2 index) { _index = index; }

    //길찾기에서 쓰는 함수들
    bool GetTileEmpty();
    Tile* GetParentTile() { return _parentTile; }
    tagCost& GetCost() { return _cost; }
    SEARCHDIRECTION& GetDirection() { return _sDir; }

    void SetParentTile(Tile* tile) { _parentTile = tile; }

    void ResetInfo();


    //마우스 함수
	virtual TileAttribute* MouseEnter();
	virtual TileAttribute* MouseStay();
	virtual TileAttribute* MouseExit();

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _index;
            ar& _terrain;
            ar& _wall;
            ar& _tileObj;
            ar& _area;
        }

        if (Archive::is_loading::value)
        {
            ar& _index;
            ar& _terrain;
            ar& _wall;
            ar& _tileObj;
            ar& _area;
        }
    }
};

