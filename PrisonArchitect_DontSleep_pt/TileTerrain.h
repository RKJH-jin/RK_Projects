#pragma once
#include "TileAttribute.h"
class TileTerrain : public TileAttribute
{
private:
	TILETERRAIN		_type;	//지형 타입

public:
    TileTerrain() {};
	TileTerrain(TILETERRAIN type);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	
	virtual void Build(Vector2 index);

	TILETERRAIN GetType() { return _type; }

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

