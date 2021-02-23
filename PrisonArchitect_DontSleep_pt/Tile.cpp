#include "stdafx.h"
#include "Tile.h"

bool Tile::GetTileEmpty()
{
   if (_wall == nullptr) return true;
   else return false;
}

void Tile::ResetInfo()
{
    _parentTile = nullptr;
    _cost.costFromStart = 0;
    _cost.costToGoal = 0;
    _cost.totalCost = 0;
}

TileAttribute * Tile::MouseEnter()
{
	if(_tileObj)		return _tileObj;
	else if(_wall)		return _wall;
	else if (_area)		return _area;
	//else if (_terrain)		return _terrain;
	return NULL;
}

TileAttribute * Tile::MouseStay()
{
	return NULL;
}

TileAttribute * Tile::MouseExit()
{

	return NULL;
}
