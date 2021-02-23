#pragma once
#include "gameNode.h"
#include "Tile.h"
class Tile;
class TileAttribute;
class TileMap;

enum class CHECKDIVERGENT : int
{
	NONE,
	DIVERGENT,
	END
};


struct compare
{
	bool operator()(Tile* A, Tile* B)
	{
		return A->GetCost().totalCost > B->GetCost().totalCost;
	}
};

class JumpPointSearch
{
public:
	static JumpPointSearch* GetInstance()
	{
		static JumpPointSearch istance;
		return &istance;
	}
private:
	vector<Tile*>			_vCloseList;
	vector<Tile*>::iterator _viCloseList;

	Tile* _startTile;		//시작타일
	Tile* _endTile;			//도착타일
	Tile* _currentTile;		//현재타일

	int TILENUMX;
	int TILENUMY;

	priority_queue<Tile*, vector<Tile*>, compare> _vOpenList;

	stack<Vector2> _vResultList;

	TileMap* _tileMap;
public:
	JumpPointSearch();
	~JumpPointSearch();

	HRESULT init();
	void release();
	void update();
	void render();

	Vector2 GetMaxTileNum() { return Vector2(TILENUMX, TILENUMY); }

	void addOpenList(Tile* currentTile);

	void pathFinder(Tile* currentTile);

	stack<Vector2> PathFinding(Vector2 start, Vector2 end);

	void linearLeft(Tile* currentTile);
	void linearRight(Tile* currentTile);
	void linearUp(Tile* currentTile);
	void linearDown(Tile* currentTile);

	void linearLU(Tile* currentTile);
	void linearRU(Tile* currentTile);
	void linearLD(Tile* currentTile);
	void linearRD(Tile* currentTile);

	CHECKDIVERGENT subLinearLeft(Tile* currentTile);
	CHECKDIVERGENT subLinearRight(Tile* currentTile);
	CHECKDIVERGENT subLinearUp(Tile* currentTile);
	CHECKDIVERGENT subLinearDown(Tile* currentTile);

	void SetLinkTileMap(TileMap* tileMap) { _tileMap = tileMap; }
};

