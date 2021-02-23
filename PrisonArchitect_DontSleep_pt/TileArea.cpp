#include "stdafx.h"
#include "TileArea.h"
#include "AllComponents.h"
#include "MapToolScene.h"

TileArea::TileArea(TILEAREA type)
{
    _info._type = (int)type;

    _info._attribute = TILEATTRIBUTE::AREA;
    _type = type;
    _info._price = 10;

    switch (type)
    {
    case TILEAREA::JAIL:
        _key = _name = "감옥";
        break;
    case TILEAREA::KITCHEN:
        _key = _name = "부엌";
        break;
    case TILEAREA::FOODCOURT:
        _key = _name = "식당";
        break;
    case TILEAREA::SHOWERROOM:
        _key = _name = "샤워실";
        break;
    case TILEAREA::STORAGE:
        _key = _name = "창고";
        break;
    case TILEAREA::DUMP:
        _key = _name = "쓰레기장";
        break;
    case TILEAREA::FIELD:
        _key = _name = "운동장";
        break;
    case TILEAREA::MEDICAL:
        _key = _name = "의료실";
        break;
    case TILEAREA::LOUNGE:
        _key = _name = "휴게실";
        break;
    case TILEAREA::OFFICE:
        _key = _name = "사무실";
        break;
    case TILEAREA::STUDYROOM:
        _key = _name = "교실";
        break;
    case TILEAREA::WARDENROOM:
        _key = _name = "교도소장실";
        break;
    }

    _description = _name + "입니다.";
}

HRESULT TileArea::init()
{
    return E_NOTIMPL;
}

void TileArea::release()
{
}

void TileArea::update()
{
}

void TileArea::render()
{
    FloatRect areaRc = FloatRect(_info._pos.x, _info._pos.y, _info._pos.x + TILESIZE * _info._count.x, _info._pos.y + TILESIZE * _info._count.y);
    areaRc = CAMERAMANAGER->GetMainCamera()->GetRelativePos(areaRc);
    _D2DRenderer->FillRectangle(areaRc, D2D1::ColorF::DarkTurquoise, 0.3f);

    wstring text = TextC::ConvertStringToWstring(_name);
    float size = sqrt(_info._count.x);
    Vector2 pos = CAMERAMANAGER->GetMainCamera()->GetRelativePos(Vector2(-size * 20 + _info._pos.x + (_info._count.x*TILESIZE) / 2,
        -size * 15 + _info._pos.y + (_info._count.y*TILESIZE) / 2));
    _D2DRenderer->RenderText(pos.x, pos.y, text, 15 * size* CAMERAMANAGER->GetMainCamera()->_zoom, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);
}

void TileArea::Build(Vector2 index)
{
    TileAttribute::Build(index);

}
bool TileArea::CheckHaveObject(string objectName)
{
    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    Vector2 maxTileNum = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount();
    for (int i = _info._startIndex.y; i < _info._startIndex.y + _info._count.y; ++i)
    {
        for (int j = _info._startIndex.x; j < _info._startIndex.x + _info._count.x; ++j)
        {
            if (tempV[i * maxTileNum.x + j]->_tileObj != nullptr && tempV[i * maxTileNum.x + j]->_tileObj->GetKey() == objectName) return true;
        }
    }

    return false;
}
vector<TileObject*> TileArea::GetHaveObject(string objectName)
{

    vector<TileObject*> result;
    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    Vector2 maxTileNum = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount();
    for (int i = _info._startIndex.y; i < _info._startIndex.y + _info._count.y; ++i)
    {
        for (int j = _info._startIndex.x; j < _info._startIndex.x + _info._count.x; ++j)
        {
            TileObject* tempObj = dynamic_cast<TileObject*>(tempV[i * maxTileNum.x + j]->_tileObj);
            if (tempObj != nullptr && tempObj->GetKey() == objectName)
            {

                if (!result.empty())
                {
                    bool flag = false;
                    for (int k = 0; k < result.size(); ++k)
                    {
                        if (result[k]->GetLeftTopIndex() == tempObj->GetLeftTopIndex())
                        {
                            flag = true;
                            break;
                        }
                    }
                    if (flag) continue;
                }

                result.push_back(tempObj);
            }
        }
    }
    return result;
}

BOOST_CLASS_EXPORT(TileArea)