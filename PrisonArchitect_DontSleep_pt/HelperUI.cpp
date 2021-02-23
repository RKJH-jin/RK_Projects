#include "stdafx.h"
#include "HelperUI.h"
#include "Button.h"

HelperUI::HelperUI()
{
	_name = "상단 바";
	_description = "게임 설정을 확인할 수 있는 상단 바입니다.";
	
	_helperImg = IMAGEMANAGER->FindImage("buttonRed");
	AddComponent<ImageC>()->SetImage(_helperImg);

	_transform->SetPosition(Vector2(50, 50));
	_transform->SetRect();

	_helper = new Button;
	_helper->SetParent(this);
	_helper->SetName("도움말");
	_helper->SetDescription("좌클릭으로 상호 작용, 우클릭으로 취소.\nR키로 오브젝트 회전, 마우스 또는 WASD로 카메라 이동.\n스페이스바 또는 시간 버튼으로 일시 정지.");

	_helper->GetTransform()->SetPosition(Vector2(50, 50));
	_helper->GetTransform()->SetSize(Vector2(50, 50));
	_helper->GetTransform()->SetRect();

	_vButton.push_back(_helper);

}

void HelperUI::update()
{
	Update();
}

void HelperUI::render()
{
	Render();
	_helperImg->SetSize(Vector2(50, 50));
}
