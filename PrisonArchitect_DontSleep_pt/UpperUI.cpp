#include "stdafx.h"
#include "UpperUI.h"
#include "Button.h"
#include "AllComponents.h"
#include "MapToolScene.h"

UpperUI::UpperUI()
{
	_name = "상단 바";
	_description = "게임 설정을 확인할 수 있는 상단 바입니다.";
	_transform->SetPosition(Vector2(WINSIZEX / 2, 50));
	_transform->SetSize(Vector2(500, 50));
	_transform->SetRect();

	_schedule = new Button;
	_schedule->SetParent(this);
	_schedule->SetName("시간표");
	_schedule->SetDescription("현재 일정과 스케줄을 확인할 수 있습니다.");
	_schedule->GetTransform()->SetPosition(Vector2(200, 50));
	_schedule->GetTransform()->SetSize(Vector2(200, 30));
	_schedule->GetTransform()->SetRect();

	_schedule->AddComponent<RectC>()->SetAlpha(0.7f);
	_schedule->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkSlateBlue);

	_schedule->AddComponent<TextC>()->ChangeText("스케줄 : ");
	_schedule->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_schedule);


	_manageDay = new Button;
	_manageDay->SetParent(this);
	_manageDay->SetName("운영일");
	_manageDay->SetDescription("교도소를 얼마나 오랫동안 운영했는지 보여줍니다. \n총 플래이 시간 : " + to_string(DATAMANAGER->GetInfo().time.day) + "일 " + to_string(DATAMANAGER->GetInfo().time.hour) + "시 " + to_string(DATAMANAGER->GetInfo().time.minute) + "분 " + to_string(DATAMANAGER->GetInfo().time.second) + "초");

	_manageDay->GetTransform()->SetPosition(Vector2(450, 50));
	_manageDay->GetTransform()->SetSize(Vector2(200, 30));
	_manageDay->GetTransform()->SetRect();

	_manageDay->AddComponent<RectC>()->SetAlpha(0.7f);
	_manageDay->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkGoldenrod);

	_manageDay->AddComponent<TextC>()->ChangeText("날짜 : " + to_string(DATAMANAGER->GetInfo().time.day) + "일");
	_manageDay->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_manageDay);

	_money = new Button;
	_money->SetParent(this);
	_money->SetName("은행 잔고");
	_money->SetDescription("은행에 보유한 현금이 얼마나 있는지 보여줍니다.");

	_money->GetTransform()->SetPosition(Vector2(700, 50));
	_money->GetTransform()->SetSize(Vector2(200, 30));
	_money->GetTransform()->SetRect();

	_money->AddComponent<RectC>()->SetAlpha(0.7f);
	_money->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkOrchid);

	_money->AddComponent<TextC>()->ChangeText("소지금 : " + to_string(DATAMANAGER->GetInfo().money) + "원");
	_money->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_money);

	_prisoner = new Button;
	_prisoner->SetParent(this);
	_prisoner->SetName("인원");
	_prisoner->SetDescription("현재 교도소에 수용하고 있는 인원의 수를 보여줍니다.");
	_prisoner->GetTransform()->SetPosition(Vector2(950, 50));
	_prisoner->GetTransform()->SetSize(Vector2(200, 30));
	_prisoner->GetTransform()->SetRect();
	_prisoner->AddComponent<RectC>()->SetAlpha(0.7f);
	_prisoner->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkTurquoise);
	_prisoner->AddComponent<TextC>()->ChangeText("인원 : " + to_string(DATAMANAGER->GetMapToolScene()->GetMapM()->GetVCharacter().size()) + "명");
	_prisoner->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_prisoner);

}

void UpperUI::release()
{
	delete _manageDay;
}

void UpperUI::update()
{
	GameObject::Update();
	_manageDay->GetComponent<TextC>()->ChangeText("날짜 : " + to_string(DATAMANAGER->GetInfo().time.day) + "일");
	_manageDay->SetDescription("교도소를 얼마나 오랫동안 운영했는지 보여줍니다. \n총 플래이 시간 : " + to_string(DATAMANAGER->GetInfo().time.day) + "일 " + to_string(DATAMANAGER->GetInfo().time.hour) + "시 " + to_string(DATAMANAGER->GetInfo().time.minute) + "분 " + to_string(DATAMANAGER->GetInfo().time.second) + "초");
	_money->GetComponent<TextC>()->ChangeText("소지금 : " + to_string(DATAMANAGER->GetInfo().money) + "원");
	_prisoner->GetComponent<TextC>()->ChangeText("인원 : " + to_string(DATAMANAGER->GetMapToolScene()->GetMapM()->GetVCharacter().size()) + "명");


	switch (DATAMANAGER->GetInfo().schedule)
	{
	case TIMESCHEDULE::SLEEP:
		_schedule->GetComponent<TextC>()->ChangeText("시간표 : 취침");
		break;
	case TIMESCHEDULE::MEAL:
		_schedule->GetComponent<TextC>()->ChangeText("시간표 : 식사");
		break;
	case TIMESCHEDULE::WASH:
		_schedule->GetComponent<TextC>()->ChangeText("시간표 : 샤워");
		break;
	case TIMESCHEDULE::GROUND:
		_schedule->GetComponent<TextC>()->ChangeText("시간표 : 운동");
		break;
	case TIMESCHEDULE::REST:
		_schedule->GetComponent<TextC>()->ChangeText("시간표 : 휴식");
		break;
	case TIMESCHEDULE::IMPRISON:
		_schedule->GetComponent<TextC>()->ChangeText("시간표 : 감금");
		break;
	default:
		break;
	}
}

void UpperUI::render()
{
	GameObject::Render();
}
