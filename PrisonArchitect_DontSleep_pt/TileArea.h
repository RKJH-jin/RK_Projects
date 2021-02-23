#pragma once
#include "TileAttribute.h"
class TileArea : public TileAttribute
{
private:
	TILEAREA		_type;		//지역 타입

public:
    TileArea() {};
	TileArea(TILEAREA type);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	TILEAREA GetType() { return _type; }


	virtual void Build(Vector2 index);
    bool CheckHaveObject(string objectName);
    vector<TileObject*> GetHaveObject(string objectName);
private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<TileAttribute>(*this);
        if (Archive::is_saving::value)
        {
            ar& _type;
        }

        if (Archive::is_loading::value)
        {
            ar& _type;
        }
    }
};

