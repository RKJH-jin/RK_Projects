#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::makePlayerHornet()
{
    _player.img = new image;

    _player.x = WINSIZEX / 2 - 200;
    _player.y = WINSIZEY - 300;
    _player.width = 65;
    _player.height = 160;

    _player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
    _player.angle = PI;
    _player.jumpPower = 10;
    _player.jumpTimeLimit = 0.5f;
    _player.jumpTimer = 0;
    _player.jumpCount = 0;
    _player.gravity = 10;
    _player.speed = 10;

    _player.isJump = false;
    _player.isAttack = false;
    _player.isSkill = false;

    _player.maxHp = 100;
    _player.hp = 100;
    _player.isDead = false;

    _player.dirType = LEFT;
    _player.stateType = IDLE_NORMAL;
    _player.posType = ONTHEGROUND;
    _player.atkType = NON_ATTACK;

    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_idle_normal_left");
    _player.curPlayAni->start();
    _player.prePlayAni = _player.curPlayAni;
    _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
    _player.airDashCount = 0;
    _player.groundDashCount = 0;
    _player.airSplashCount = 0;
    _player.groundSplashCount = 0;

    _player.splashRcWidth = 400;
    _player.splashRcHeight = 400;
}

