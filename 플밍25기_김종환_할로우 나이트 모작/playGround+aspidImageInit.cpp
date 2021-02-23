#include "stdafx.h"
#include "playGround.h"

void playGround::aspidImageInit()
{
    IMAGEMANAGER->addFrameImage("aspid_turn_left", "image/enemy/aspid/aspid_turn_left.bmp", 320, 122, 2, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("aspid_turn_right", "image/enemy/aspid/aspid_turn_right.bmp", 320, 122, 2, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("aspid_move_left", "image/enemy/aspid/aspid_move_left.bmp", 852, 122, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("aspid_move_right", "image/enemy/aspid/aspid_move_right.bmp", 852, 122, 6, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("aspid_attack_left", "image/enemy/aspid/aspid_attack_left.bmp", 1848, 117, 12, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("aspid_attack_right", "image/enemy/aspid/aspid_attack_right.bmp", 1848, 117, 12, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("aspid_death_left", "image/enemy/aspid/aspid_death_left.bmp", 906, 133, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("aspid_death_right", "image/enemy/aspid/aspid_death_right.bmp", 906, 133, 6, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addImage("death_core", "image/enemy/aspid/death_core.bmp", 31, 34, true, RGB(255, 0, 255));
}

