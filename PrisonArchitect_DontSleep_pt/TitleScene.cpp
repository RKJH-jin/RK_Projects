#include "stdafx.h"
#include "TitleScene.h"
#include "MapToolScene.h"

#include "VolumeUI.h"

HRESULT TitleScene::init()
{
	Scene::init();
	DATAMANAGER->init();

	SOUNDMANAGER->play("title");

	//마우스 생성 및 초기화
	_mouse = new Mouse;
	_mouse->Init();

	//타일 오브젝트 저장고에 만들어 준다.
	
	//로고 이미지를 설정한다.
	_logoImg = IMAGEMANAGER->FindImage("PAlogo");
	
	_background = IMAGEMANAGER->FindImage("titleBackground");

	_volume = new VolumeUI;
	_text = L"Press Enter Or Click To Start";
	return S_OK;
}

void TitleScene::release()
{
	Scene::release();

}

void TitleScene::update()
{
	Scene::update();
	
	_volume->update();

	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) SOUNDMANAGER->play("click8");

	if (_volume->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
	{

	}
	else
	{
		//엔터를 치거나 볼륨 외를 클릭하면 게임 시작
		if (KEYMANAGER->isOnceKeyUp(VK_RETURN) || KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			SOUNDMANAGER->play("click3", DATAMANAGER->GetInfo().soundVolume * DATAMANAGER->GetInfo().sfxVolume);
			SCENEMANAGER->ReplaceScene(new MapToolScene);
		}
	}

}

void TitleScene::render()
{
	Scene::render();

	_background->Render(Vector2(WINSIZEX / 2, WINSIZEY / 2));

	_logoImg->SetScale(0.4f);
	_logoImg->Render(Vector2(WINSIZEX / 8, WINSIZEY/8));

	_volume->render();

	if (!_volume->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
	{
		D2DRenderer::GetInstance()->RenderText(_ptMouse.x, _ptMouse.y, _text, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING);
	}

}
