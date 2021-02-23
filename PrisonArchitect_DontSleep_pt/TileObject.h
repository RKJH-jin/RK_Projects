#pragma once
#include "TileAttribute.h"
class TileObject : public TileAttribute
{
private:
	TILEOBJECT		_type;		//오브젝트 타입

	int				_frame[4];		//프레임 인덱스
	vector<Vector2> _vUsable;		//사용 가능한 인덱스

public:
    TileObject() {};
	TileObject(TILEOBJECT type);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//FUNCTION
	virtual void Build(Vector2 index);
	virtual void Destroy();

	//GETTER
	TILEOBJECT GetType() { return _type; }

	virtual vector<Vector2>* GetvUsable() { return &_vUsable; };	//사용 가능한 인덱스

    virtual bool CheckVoidIndex();
	virtual Vector2* GetVoidIndexfromVector();
	virtual void PutIndexToVector(Vector2* index);

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
            ar& _frame;
            ar& _vUsable;
        }

        if (Archive::is_loading::value)
        {
            ar& _type;
            ar& _frame;
            ar& _vUsable;
        }
    }
};

