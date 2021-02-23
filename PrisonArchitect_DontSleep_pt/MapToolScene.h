#pragma once
#include "MapManager.h"
#include "Scene.h"
#include "Button.h"

class MapToolScene : public Scene
{
private:
	//맵 매니저
	MapManager* _mapM;

	//UI
	DescriptionUI*			_descriptionUI;
	InfoUI*					_infoUI;

	vector<BarButtonUI*>	_vUnderBarUI;
	vector<WindowUI*>		_vUnderBarWindowUI;
	BarButtonUI*			_currentUnderBarActive;
    ClockUI*                _clockUI;
    vector<PlayButtonUI*>   _vPlayButtonUI;
    FloatRect               _sky;


	vector<UI*>				_vUI;

public:
	MapToolScene() {};
	~MapToolScene() {};
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// UI
	void AddUI();
	void renderUI();
	vector<UI*> GetvUI() { return _vUI; }

	void addUnderBarUI(string strName, Vector2 pos, float scale, Image* img);
	void addUnderBarUI(string strName, Vector2 pos, float scale, Image* img, int frameX, int frameY);
	void addUnderBarWindowUI(Vector2 pos, Vector2 size, float scale);
	void addObjectButtonUIInWindowUI(int arrNum, string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame);
	void setLinkUnderBarUI(int arrNum, int arrNum2);
	void addSingleUI(string strName, Vector2 pos, float scale, Image* img);
    void addPlayButtonUI(string strName, Vector2 pos, Vector2 size, float scale, Image* img);

	//GETTER
	MapManager* GetMapM() { return _mapM; }
    
	DescriptionUI*			GetDescriptionUI() { return _descriptionUI; }
	InfoUI*					GetInfoUI() { return _infoUI; }

	vector<BarButtonUI*>	GetvUnderBarUI() { return _vUnderBarUI; };
	vector<WindowUI*>		GetvUnderBarWindowUI() { return _vUnderBarWindowUI; }
	BarButtonUI*			GetCurrentUnderBarActive() { return _currentUnderBarActive; }
    vector<PlayButtonUI*>   GetvPlayButtonUI() { return _vPlayButtonUI; }
   
	//SETTER
    void SetCurrentUnderBarActive(BarButtonUI* ui) { _currentUnderBarActive = ui; }

    // 마우스
    virtual void MouseEnter();
    virtual void MouseStay();
    virtual void MouseExit();

    void Save();
    void Load();

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _mapM;
            //ar& _vCharacter;
        }

        if (Archive::is_loading::value)
        {
            ar& _mapM;
            //ar& _vCharacter;
        }
    }
};

