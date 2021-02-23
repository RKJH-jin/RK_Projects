#include "stdafx.h"
#include "playGround.h"

void playGround::hornetAnimationInit()
{
    ANIMATIONMANAGER->addAnimation("hornet_idle_normal_left", "hornet_idle_normal_left", false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_idle_normal_right", "hornet_idle_normal_right", true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_idle_special_left", "hornet_idle_special_left", false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_idle_special_right", "hornet_idle_special_right", true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_run_left", "hornet_run_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_run_left", "hornet_run_left_2", 6, 13, false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_run_right", "hornet_run_right_1", true, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_run_right", "hornet_run_right_2", 7, 0, true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_jump_left", "hornet_jump_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_jump_left", "hornet_jump_left_2", 7, 13, false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_jump_right", "hornet_jump_right_1", true, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_jump_right", "hornet_jump_right_2", 0, 6, true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_hang_left", "hornet_hang_left", false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_hang_right", "hornet_hang_right", false, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_attack_left", "hornet_attack_left", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_attack_right", "hornet_attack_right", 0, 6, true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_dash_air_left_1", "hornet_dash_air_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_dash_air_right_1", "hornet_dash_air_right_1", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_dash_air_left_2", "hornet_dash_air_left_2", false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_dash_air_right_2", "hornet_dash_air_right_2", true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_dash_air_left_3", "hornet_dash_air_left_3", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_dash_air_right_3", "hornet_dash_air_right_3", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_dash_ground_left_1", "hornet_dash_ground_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_dash_ground_right_1", "hornet_dash_ground_right_1", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_dash_ground_left_2", "hornet_dash_ground_left_2", false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_dash_ground_right_2", "hornet_dash_ground_right_2", true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_dash_ground_left_3", "hornet_dash_ground_left_3", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_dash_ground_right_3", "hornet_dash_ground_right_3", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_throw_left_1", "hornet_throw_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_throw_right_1", "hornet_throw_right_1", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_throw_left_2", "hornet_throw_left_2", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_throw_left_2", "hornet_throw_left_2_1", 2, 5, false, true, 1);
    ANIMATIONMANAGER->addAnimation("hornet_throw_right_2", "hornet_throw_right_2", true, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_throw_left_2", "hornet_throw_right_2_1", 0, 3, true, true, 1);

    ANIMATIONMANAGER->addAnimation("hornet_throw_left_3", "hornet_throw_left_3", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_throw_right_3", "hornet_throw_right_3", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_air_left_1", "hornet_splashAttack_air_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_air_right_1", "hornet_splashAttack_air_right_1", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_ground_left_1", "hornet_splashAttack_ground_left_1", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_ground_right_1", "hornet_splashAttack_ground_right_1", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_left_2", "hornet_splashAttack_left_2", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_right_2", "hornet_splashAttack_right_2", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_left_3", "hornet_splashAttack_left_3", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_splashAttack_right_3", "hornet_splashAttack_right_3", true, false, 1);

    ANIMATIONMANAGER->addAnimation("hornet_stun_left", "hornet_stun_left", false, false, 1);
    ANIMATIONMANAGER->addAnimation("hornet_stun_right", "hornet_stun_right", true, false, 1);
}


