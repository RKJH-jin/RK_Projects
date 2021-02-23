#include "stdafx.h"
#include "playGround.h"

void playGround::hornetImageInit()
{
	// HORNET - IDLE
	IMAGEMANAGER->addFrameImage("hornet_idle_normal_left", "image/hornet/hornet_idle_normal_left.bmp", 1104, 216, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_idle_normal_right", "image/hornet/hornet_idle_normal_right.bmp", 1104, 216, 6, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("hornet_idle_special_left", "image/hornet/hornet_idle_special_left.bmp", 5239, 373, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_idle_special_right", "image/hornet/hornet_idle_special_right.bmp", 5239, 373, 13, 1, true, RGB(255, 0, 255));
	
	// HORNET - RUN
	IMAGEMANAGER->addFrameImage("hornet_run_left", "image/hornet/hornet_run_left.bmp", 5334, 249, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_run_right", "image/hornet/hornet_run_right.bmp", 5334, 249, 14, 1, true, RGB(255, 0, 255));
	
	// HORNET - JUMP
	IMAGEMANAGER->addFrameImage("hornet_jump_left", "image/hornet/hornet_jump_left.bmp", 5334, 249, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_jump_right", "image/hornet/hornet_jump_right.bmp", 5334, 249, 14, 1, true, RGB(255, 0, 255));
	
	// HORNET - LAND
	IMAGEMANAGER->addFrameImage("hornet_land_left", "image/hornet/hornet_land_left.bmp", 588, 219, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_land_right", "image/hornet/hornet_land_right.bmp", 588, 219, 3, 1, true, RGB(255, 0, 255));

	// HORNET - HANG
	IMAGEMANAGER->addFrameImage("hornet_hang_left", "image/hornet/hornet_hang_left.bmp", 396, 215, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_hang_right", "image/hornet/hornet_hang_right.bmp", 396, 215, 3, 1, true, RGB(255, 0, 255));
	
	// HORNET - DASH_AIR
	IMAGEMANAGER->addFrameImage("hornet_dash_air_left_1", "image/hornet/hornet_dash_air_1_left.bmp", 2088, 198, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_air_right_1", "image/hornet/hornet_dash_air_1_right.bmp", 2088, 198, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_air_left_2", "image/hornet/hornet_dash_air_2_left.bmp", 510, 137, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_air_right_2", "image/hornet/hornet_dash_air_2_right.bmp", 510, 137, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_air_left_3", "image/hornet/hornet_dash_air_3_left.bmp", 985, 206, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_air_right_3", "image/hornet/hornet_dash_air_3_right.bmp", 985, 206, 5, 1, true, RGB(255, 0, 255));
	
	// HORNET - DASH_GROUND
	IMAGEMANAGER->addFrameImage("hornet_dash_ground_left_1", "image/hornet/hornet_dash_ground_1_left.bmp", 2760, 193, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_ground_right_1", "image/hornet/hornet_dash_ground_1_right.bmp", 2760, 193, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_ground_left_2", "image/hornet/hornet_dash_ground_2_left.bmp", 510, 137, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_ground_right_2", "image/hornet/hornet_dash_ground_2_right.bmp", 510, 137, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_ground_left_3", "image/hornet/hornet_dash_ground_3_left.bmp", 1746, 208, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_dash_ground_right_3", "image/hornet/hornet_dash_ground_3_right.bmp", 1746, 208, 6, 1, true, RGB(255, 0, 255));

	// HORNET - ATTACK
	IMAGEMANAGER->addFrameImage("hornet_attack_left", "image/hornet/hornet_attack_left.bmp", 3480, 420, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_attack_right", "image/hornet/hornet_attack_right.bmp", 3480, 420, 6, 1, true, RGB(255, 0, 255));

	// HORNET - THROW
	IMAGEMANAGER->addFrameImage("hornet_throw_left_1", "image/hornet/hornet_throw_1_left.bmp", 2780, 214, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_throw_right_1", "image/hornet/hornet_throw_1_right.bmp", 2780, 214, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_throw_left_2", "image/hornet/hornet_throw_2_left.bmp", 990, 200, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_throw_right_2", "image/hornet/hornet_throw_2_right.bmp", 990, 200, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_throw_left_3", "image/hornet/hornet_throw_3_left.bmp", 1440, 190, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_throw_right_3", "image/hornet/hornet_throw_3_right.bmp", 1440, 190, 6, 1, true, RGB(255, 0, 255));
	
	// HORNET - SPEAR
	IMAGEMANAGER->addImage("hornet_spear_left", "image/hornet/hornet_spear_left.bmp", 281, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hornet_spear_right", "image/hornet/hornet_spear_right.bmp", 281, 22, true, RGB(255, 0, 255));

	// HORNET - SPLASHATTACK_AIR
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_air_left_1", "image/hornet/hornet_splashAttack1_air_left.bmp", 1687, 204, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_air_right_1", "image/hornet/hornet_splashAttack1_air_right.bmp", 1687, 204, 7, 1, true, RGB(255, 0, 255));
	
	// HORNET - SPLASHATTACK_GROUND
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_ground_left_1", "image/hornet/hornet_splashAttack1_ground_left.bmp", 2360, 201, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_ground_right_1", "image/hornet/hornet_splashAttack1_ground_right.bmp", 2360, 201, 10, 1, true, RGB(255, 0, 255));
	
	// HORNET - SPLASHATTACK
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_left_2", "image/hornet/hornet_splashAttack2_left.bmp", 3816, 447, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_right_2", "image/hornet/hornet_splashAttack2_right.bmp", 3816, 447, 9, 1, true, RGB(255, 0, 255));
	
	// HORNET - SPLASHATTACK
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_left_3", "image/hornet/hornet_splashAttack3_left.bmp", 546, 211, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_splashAttack_right_3", "image/hornet/hornet_splashAttack3_right.bmp", 546, 211, 2, 1, true, RGB(255, 0, 255));

	// HORNET - STUN
	IMAGEMANAGER->addFrameImage("hornet_stun_left", "image/hornet/hornet_stun_left.bmp", 2332, 187, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_stun_right", "image/hornet/hornet_stun_right.bmp", 2332, 187, 11, 1, true, RGB(255, 0, 255));
	//====================미사용====================//
	// 회피
	IMAGEMANAGER->addFrameImage("hornet_evade1_left", "image/hornet/hornet_evade1_left.bmp", 555, 218, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_evade1_right", "image/hornet/hornet_evade1_right.bmp", 555, 218, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_evade2_left", "image/hornet/hornet_evade2_left.bmp", 588, 212, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_evade2_right", "image/hornet/hornet_evade2_right.bmp", 588, 212, 3, 1, true, RGB(255, 0, 255));
	// 일반 공격
	IMAGEMANAGER->addFrameImage("hornet_flourish_left", "image/hornet/hornet_flourish_left.bmp", 5012, 301, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hornet_flourish_right", "image/hornet/hornet_flourish_right.bmp", 5012, 301, 14, 1, true, RGB(255, 0, 255));
	//=============================================//

	//================TOWN IMAGE================//
	IMAGEMANAGER->addImage("town_background", "image/object/town_background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_floor_1", "image/object/town_floor_1.bmp", 7225, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_wall_left", "image/object/town_wall_left.bmp", 768, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_wall_left_2", "image/object/town_wall_left_2.bmp", 280, 368, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_wall_left_3", "image/object/town_wall_left_3.bmp", 280, 368, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor_1", "image/object/floor_1.bmp", 174, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor_2", "image/object/floor_2.bmp", 1195, 249, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("platform_1", "image/object/platform_1.bmp", 140, 227, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("platform_2", "image/object/platform_2.bmp", 156, 197, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("basketwall_1", "image/object/basketwall_1.bmp", 313, 386, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("basketwall_2", "image/object/basketwall_2.bmp", 313, 750, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("basketwall_3", "image/object/basketwall_3.bmp", 313, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ruins_wall", "image/object/ruins_wall.bmp", 412, 849, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wall_1", "image/object/wall_1.bmp", 105, 169, true, RGB(255, 0, 255));
	//================UI IMAGE================//
	IMAGEMANAGER->addImage("hpbar_soul", "image/UI/hpbar_soul.bmp", 176, 133, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpbar_back", "image/UI/hpbar_back.bmp", 55, 71, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpbar_front", "image/UI/hpbar_front.bmp", 64, 71, true, RGB(255, 0, 255));
	//=============================================//
}

