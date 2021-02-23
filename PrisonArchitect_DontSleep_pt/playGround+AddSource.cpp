#include "stdafx.h"
#include "playGround.h"


void playGround::AddSource()
{
	//이미지 추가
	AddImage();
	AddSound();
}

void playGround::AddImage()
{
	//png 이미지
	wstring path = L"source/image/";
	wstring filter = L".png";

	//tileset
	wstring folder = L"tileset/";
	IMAGEMANAGER->AddFrameImage("terrain", path + folder + L"terrain" + filter, 10, 20);

	//wall
	folder = L"tileset/wall/";
	for (int i = 0; i < (int)TILEWALL::END; i++)
	{
		string key1 = "wall" + to_string(i);
		wstring key2 = L"wall" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(key1, path + folder + key2 + filter, 7, 4);
	}

	//tileObject
	folder = L"tileset/tileObject/";
	IMAGEMANAGER->AddFrameImage("가스레인지", path + folder + L"가스레인지" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("배식대", path + folder + L"배식대" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("벤치", path + folder + L"벤치" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("변기", path + folder + L"변기" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("사무실책상", path + folder + L"사무실책상" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("샤워기", path + folder + L"샤워기" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("서류보관함", path + folder + L"서류보관함" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("쇼파", path + folder + L"쇼파" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("식탁", path + folder + L"식탁" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("싱크대", path + folder + L"싱크대" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("의자", path + folder + L"의자" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("이중철창문", path + folder + L"이중철창문" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("자판기", path + folder + L"자판기" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("직원문", path + folder + L"직원문" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("철창문", path + folder + L"철창문" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("침대", path + folder + L"침대" + filter, 3, 1);
	

	//stuffObject & toolObject
	folder = L"stuffObject/";


	IMAGEMANAGER->AddImage("bacon", path + folder + L"bacon" + filter);
	IMAGEMANAGER->AddImage("trash", path + folder + L"trash" + filter);

	IMAGEMANAGER->AddFrameImage("bacons", path + folder + L"bacons" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("cabbages", path + folder + L"cabbages" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("patatos", path + folder + L"patatos" + filter, 3, 1);


	IMAGEMANAGER->AddFrameImage("baconCook", path + folder + L"baconCook" + filter, 3, 1);
	IMAGEMANAGER->AddFrameImage("baconFood", path + folder + L"baconFood" + filter, 3, 1);

	IMAGEMANAGER->AddImage("brick", path + folder + L"brick" + filter);
	IMAGEMANAGER->AddFrameImage("bricks", path + folder + L"bricks" + filter, 3, 1);

	IMAGEMANAGER->AddImage("brickRed", path + folder + L"brickRed" + filter);
	IMAGEMANAGER->AddFrameImage("brickReds", path + folder + L"brickReds" + filter, 3, 1);

	IMAGEMANAGER->AddImage("cabbage", path + folder + L"cabbage" + filter);

	IMAGEMANAGER->AddImage("material", path + folder + L"material" + filter);
	IMAGEMANAGER->AddFrameImage("materials", path + folder + L"materials" + filter, 3, 1);


	IMAGEMANAGER->AddImage("patato", path + folder + L"patato" + filter);

	IMAGEMANAGER->AddImage("rebar", path + folder + L"rebar" + filter);
	IMAGEMANAGER->AddFrameImage("rebars", path + folder + L"rebars" + filter, 3, 1);

	IMAGEMANAGER->AddImage("soup", path + folder + L"soup" + filter);
	IMAGEMANAGER->AddFrameImage("soups", path + folder + L"soups" + filter, 3, 1);

	IMAGEMANAGER->AddImage("soupGreen", path + folder + L"soupGreen" + filter);
	IMAGEMANAGER->AddFrameImage("soupGreens", path + folder + L"soupGreens" + filter, 3, 1);

	IMAGEMANAGER->AddImage("tray", path + folder + L"tray" + filter);
	IMAGEMANAGER->AddFrameImage("trays", path + folder + L"trays" + filter, 3, 1);

	IMAGEMANAGER->AddImage("trayDirty", path + folder + L"trayDirty" + filter);
	IMAGEMANAGER->AddFrameImage("trayDirtys", path + folder + L"trayDirtys" + filter, 3, 1);

	IMAGEMANAGER->AddImage("wood0", path + folder + L"wood0" + filter);
	IMAGEMANAGER->AddFrameImage("wood0s", path + folder + L"wood0s" + filter, 3, 1);

	IMAGEMANAGER->AddImage("wood1", path + folder + L"wood1" + filter);
	IMAGEMANAGER->AddFrameImage("wood1s", path + folder + L"wood1s" + filter, 3, 1);

	IMAGEMANAGER->AddImage("woodCut", path + folder + L"woodCut" + filter);
	IMAGEMANAGER->AddFrameImage("woodCuts", path + folder + L"woodCuts" + filter, 3, 1);

	IMAGEMANAGER->AddImage("box", path + folder + L"box" + filter);
	IMAGEMANAGER->AddImage("document", path + folder + L"document" + filter);
	IMAGEMANAGER->AddImage("driver", path + folder + L"driver" + filter);
	IMAGEMANAGER->AddImage("mop", path + folder + L"mop" + filter);
	IMAGEMANAGER->AddImage("spatula", path + folder + L"spatula" + filter);
	IMAGEMANAGER->AddImage("syringe", path + folder + L"syringe" + filter);
	IMAGEMANAGER->AddImage("car", path + folder + L"car" + filter);

	// PIC
	folder = L"pic/";
	IMAGEMANAGER->AddImage("titleBackground", path + folder + L"titleBackground" + filter);

	// UI
	folder = L"ui/";

	IMAGEMANAGER->AddImage("clock", path + folder + L"clock" + filter);
	IMAGEMANAGER->AddImage("codex", path + folder + L"codex" + filter);
	IMAGEMANAGER->AddFrameImage("buttonBlue", path + folder + L"buttonBlue" + filter, 7, 1);
	IMAGEMANAGER->AddImage("screenEdge", path + folder + L"screenEdge" + filter);
    IMAGEMANAGER->AddFrameImage("buttonRed", path + folder + L"buttonRed" + filter, 1, 1);
    IMAGEMANAGER->AddFrameImage("buttonGray", path + folder + L"buttonGray" + filter, 3, 1);
    IMAGEMANAGER->AddFrameImage("buttonGreen", path + folder + L"buttonGreen" + filter, 6, 1);
    IMAGEMANAGER->AddFrameImage("buttonOrange", path + folder + L"buttonOrange" + filter, 2, 1);
    IMAGEMANAGER->AddFrameImage("clockHands", path + folder + L"clockHands" + filter, 2, 1);
    IMAGEMANAGER->AddImage("letterBlank", path + folder + L"letterBlank" + filter);
    IMAGEMANAGER->AddFrameImage("playButton", path + folder + L"playButton" + filter, 5, 1);
	IMAGEMANAGER->AddImage("PAlogo", path + folder + L"PAlogo" + filter);
	IMAGEMANAGER->AddImage("temp", path + folder + L"temp" + filter);
	IMAGEMANAGER->AddImage("dialogWindow", path + folder + L"dialogWindow" + filter);

    IMAGEMANAGER->AddImage("time_play0", path + folder + L"time_play0" + filter);
    IMAGEMANAGER->AddImage("time_play1", path + folder + L"time_play1" + filter);
    IMAGEMANAGER->AddImage("time_play2", path + folder + L"time_play2" + filter);
    IMAGEMANAGER->AddImage("time_play3", path + folder + L"time_play3" + filter);
    IMAGEMANAGER->AddImage("time_play4", path + folder + L"time_play4" + filter);


	//사람
	folder = L"character/";

	IMAGEMANAGER->AddFrameImage("accountant", path + folder + L"accountant" + filter, 4, 1);
	IMAGEMANAGER->AddFrameImage("bitalia", path + folder + L"bitalia" + filter, 4, 1);
	IMAGEMANAGER->AddFrameImage("boss", path + folder + L"boss" + filter, 4, 1);
	IMAGEMANAGER->AddFrameImage("nico", path + folder + L"nico" + filter, 4, 1);
	IMAGEMANAGER->AddFrameImage("teacher", path + folder + L"teacher" + filter, 4, 1);
	IMAGEMANAGER->AddFrameImage("warden", path + folder + L"warden" + filter, 4, 1);

	IMAGEMANAGER->AddImage("hand", path + folder + L"hand" + filter);

	string imgName;	//등록할 이름
	wstring fileName;//등록할 이미지이름

	for (int i = 0; i < 4; i++)
	{
		//몸 이미지 등록
		imgName = "bod" + to_string(i);
		fileName = L"bod" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

		//몸(옷) 이미지 등록
		imgName = "bodCloth" + to_string(i);
		fileName = L"bodCloth" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

		//청소부 이미지 등록
		imgName = "cleaner" + to_string(i);
		fileName = L"cleaner" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

		//요리사 이미지 등록
		imgName = "cooker" + to_string(i);
		fileName = L"cooker" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

		//의사 이미지 등록
		imgName = "docter" + to_string(i);
		fileName = L"docter" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

		//인부 이미지 등록
		imgName = "worker" + to_string(i);
		fileName = L"worker" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

		//교도관 이미지 등록
		imgName = "warder" + to_string(i);
		fileName = L"warder" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);
	}
	imgName = "warder" + to_string(4);
	fileName = L"warder" + to_wstring(4);
	IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);

	for (int i = 0; i < 10; i++)
	{
		//머리 이미지 등록
		imgName = "head" + to_string(i);
		fileName = L"head" + to_wstring(i);
		IMAGEMANAGER->AddFrameImage(imgName, path + folder + fileName + filter, 4, 1);
	}

}

void playGround::AddSound()
{
	for (int i = 1; i < 9; i++)
	{
		SOUNDMANAGER->addSound("click" + to_string(i), "source/sound/sfx/Drag_Tick" + to_string(i) + ".ogg", false, false);
	}
	SOUNDMANAGER->addSound( "map", "source/sound/bgm/map.mp3", true, true);
	SOUNDMANAGER->addSound( "title", "source/sound/bgm/title.mp3", true, true);
}
