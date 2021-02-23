#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"


void player::hornetAnimationRender()
{
    if (_player.stateType == PLAYER::HIT)
    {
        if (_player.dirType == LEFT)
        {
            IMAGEMANAGER->findImage("hornet_stun_left")->alphaAniRender(getMemDC(), _player.x - 150, _player.y - 90,
                _player.curPlayAni, 0);
            
        }
        else if (_player.dirType == RIGHT)
        {
            IMAGEMANAGER->findImage("hornet_stun_right")->aniRender(getMemDC(), _player.x - 60, _player.y - 90,
                _player.curPlayAni);
        }
        if (!_player.curPlayAni->isPlay())
        {
            _player.stateType = PLAYER::IDLE_NORMAL;
            if (_player.dirType == LEFT)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_idle_normal_left");
            }
            else if (_player.dirType == RIGHT)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_idle_normal_right");
            }
            ANIMATIONMANAGER->resetCurrentAni("hornet_stun_left");
            ANIMATIONMANAGER->resetCurrentAni("hornet_stun_right");
        }
    }
    else
    {
        if (_player.atkType != NON_ATTACK)
        {
            switch (_player.atkType)
            {
            case NORMAL_ATTACK:
                if (_player.dirType == LEFT)
                {
                    IMAGEMANAGER->findImage("hornet_attack_left")->
                        aniRender(getMemDC(), _player.x - 305, _player.y - 322, _player.curPlayAtkAni);
                }
                else if (_player.dirType == RIGHT)
                {
                    IMAGEMANAGER->findImage("hornet_attack_right")->
                        aniRender(getMemDC(), _player.x - 275, _player.y - 322, _player.curPlayAtkAni);
                }
                break;
            case FLOURISH:
                break;
            case THROW:
                // 왼쪽 창던지기
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_left_1")->
                            aniRender(getMemDC(), _player.x - 130, _player.y - 140, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_left_2");
                            _cProjectile->hornetSpearInit(_player.x, _player.y, _player.width, _player.height, _player.dirType);
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_left_2")->
                            aniRender(getMemDC(), _player.x - 95, _player.y - 120, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_left_2_1");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_2_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_left_2")->
                            aniRender(getMemDC(), _player.x - 95, _player.y - 120, _player.curPlayAtkAni);
                        if (!_cProjectile->getCheckSpear())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_left_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_left_3")->
                            aniRender(getMemDC(), _player.x - 145, _player.y - 120, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.atkType = NON_ATTACK;
                        }
                    }
                }
                // 오른쪽 창던지기
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_right_1")->
                            aniRender(getMemDC(), _player.x - 147, _player.y - 140, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_right_2");
                            _cProjectile->hornetSpearInit(_player.x, _player.y, _player.width, _player.height, _player.dirType);
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_right_2")->
                            aniRender(getMemDC(), _player.x - 70, _player.y - 120, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_right_2_1");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_2_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_right_2")->
                            aniRender(getMemDC(), _player.x - 70, _player.y - 120, _player.curPlayAtkAni);
                        if (!_cProjectile->getCheckSpear())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_right_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_throw_right_3")->
                            aniRender(getMemDC(), _player.x - 87, _player.y - 120, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.atkType = NON_ATTACK;
                        }
                    }
                }
                break;
            case DASH_AIR:
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_air_left_1")->
                            aniRender(getMemDC(), _player.x - 110, _player.y - 140, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_air_left_2")->
                            aniRender(getMemDC(), _player.x - 175, _player.y - 80, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_air_left_3")->
                            aniRender(getMemDC(), _player.x - 100, _player.y - 140, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.isAttack = false;
                        }
                    }
                }
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_air_right_1")->
                            aniRender(getMemDC(), _player.x - 122, _player.y - 140, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_air_right_2")->
                            aniRender(getMemDC(), _player.x - 70, _player.y - 80, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_air_right_3")->
                            aniRender(getMemDC(), _player.x - 100, _player.y - 142, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.isAttack = false;
                        }
                    }
                }
                break;
            case DASH_GROUND:
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_ground_left_1")->
                            aniRender(getMemDC(), _player.x - 150, _player.y - 145, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_ground_left_2")->
                            aniRender(getMemDC(), _player.x - 180, _player.y - 105, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_ground_left_3")->
                            aniRender(getMemDC(), _player.x - 160, _player.y - 160, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.isAttack = false;
                        }
                    }
                }
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_ground_right_1")->
                            aniRender(getMemDC(), _player.x - 128, _player.y - 145, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_ground_right_2")->
                            aniRender(getMemDC(), _player.x - 75, _player.y - 105, _player.curPlayAtkAni);

                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_dash_ground_right_3")->
                            aniRender(getMemDC(), _player.x - 160, _player.y - 160, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.isAttack = false;
                        }
                    }
                }
                break;
            case SPLASH_AIR:
                // 공중에서 왼쪽 스플래쉬
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_air_left_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_air_left_1")->
                            aniRender(getMemDC(), _player.x - 110, _player.y - 135, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_left_2")->
                            aniRender(getMemDC(), _player.x - 210, _player.y - 250, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_left_3")->
                            aniRender(getMemDC(), _player.x - 120, _player.y - 150, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.atkType = NON_ATTACK;
                            _player.isAttack = false;
                        }
                    }
                }
                // 공중에서 오른쪽 스플래쉬
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_air_right_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_air_right_1")->
                            aniRender(getMemDC(), _player.x - 120, _player.y - 135, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_right_2")->
                            aniRender(getMemDC(), _player.x - 220, _player.y - 250, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_right_3")->
                            aniRender(getMemDC(), _player.x - 155, _player.y - 150, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.atkType = NON_ATTACK;
                            _player.isAttack = false;
                        }
                    }
                }
                break;
            case SPLASH_GROUND:
                // 땅에서 왼쪽 스플래쉬
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_ground_left_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_ground_left_1")->
                            aniRender(getMemDC(), _player.x - 110, _player.y - 135, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_left_2")->
                            aniRender(getMemDC(), _player.x - 210, _player.y - 250, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_left_3")->
                            aniRender(getMemDC(), _player.x - 120, _player.y - 150, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.atkType = NON_ATTACK;
                            _player.isAttack = false;
                        }
                    }
                }
                // 땅에서 오른쪽 스플래쉬
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_ground_right_1"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_ground_right_1")->
                            aniRender(getMemDC(), _player.x - 120, _player.y - 135, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_2");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_2"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_right_2")->
                            aniRender(getMemDC(), _player.x - 220, _player.y - 250, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3");
                            _player.curPlayAtkAni->resume();
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3"))
                    {
                        IMAGEMANAGER->findImage("hornet_splashAttack_right_3")->
                            aniRender(getMemDC(), _player.x - 155, _player.y - 150, _player.curPlayAtkAni);
                        if (!_player.curPlayAtkAni->isPlay())
                        {
                            _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");
                            _player.atkType = NON_ATTACK;
                            _player.isAttack = false;
                        }
                    }
                }
                break;
            }
        }
        else if (_player.atkType == NON_ATTACK)
        {
            // 땅 위에서 가만히 있을 때
            if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_idle_normal_left")
                    ->aniRender(getMemDC(), _player.x - 95, _player.y - 134,
                        ANIMATIONMANAGER->findAnimation("hornet_idle_normal_left"));
            }
            else if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_idle_normal_right")
                    ->aniRender(getMemDC(), _player.x - 90, _player.y - 134,
                        ANIMATIONMANAGER->findAnimation("hornet_idle_normal_right"));
            }
            // 땅 위에서 달릴 때
            if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                _player.stateType == RUN && _player.jumpType == NON_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_run_left")->aniRender(getMemDC(),
                    _player.x - 195, _player.y - 142,
                    _player.curPlayAni);

                if (!ANIMATIONMANAGER->findAnimation("hornet_run_left_1")->isPlay())
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_run_left_2");
                }
            }
            else if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                _player.stateType == RUN && _player.jumpType == NON_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_run_right")->aniRender(getMemDC(),
                    _player.x - 186, _player.y - 142,
                    _player.curPlayAni);
                if (!ANIMATIONMANAGER->findAnimation("hornet_run_right_1")->isPlay())
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_run_right_2");
                }
            }
            // 제자리 점프 했을 때
            if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
            {
                IMAGEMANAGER->findImage("hornet_jump_left")->aniRender(getMemDC(),
                    _player.x - 190, _player.y - 142,
                    _player.curPlayAni);
                if (!ANIMATIONMANAGER->findAnimation("hornet_jump_left_1")->isPlay())
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_2");
                }
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
            {
                IMAGEMANAGER->findImage("hornet_jump_right")->aniRender(getMemDC(),
                    _player.x - 190, _player.y - 142,
                    _player.curPlayAni);
                if (!ANIMATIONMANAGER->findAnimation("hornet_jump_right_1")->isPlay())
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_2");
                }
            }
            // 달리기 점프 했을 때
            if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                IMAGEMANAGER->findImage("hornet_jump_left")->aniRender(getMemDC(),
                    _player.x - 190, _player.y - 142,
                    _player.curPlayAni);
                if (!ANIMATIONMANAGER->findAnimation("hornet_jump_left_1")->isPlay())
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_2");
                }
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                IMAGEMANAGER->findImage("hornet_jump_right")->aniRender(getMemDC(),
                    _player.x - 190, _player.y - 142,
                    _player.curPlayAni);
                if (!ANIMATIONMANAGER->findAnimation("hornet_jump_right_1")->isPlay())
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_2");
                }
            }
            // 제자리 낙하할 때
            if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
            {
                IMAGEMANAGER->findImage("hornet_jump_left")->aniRender(getMemDC(),
                    _player.x - 186, _player.y - 145,
                    _player.curPlayAni);
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
            {
                IMAGEMANAGER->findImage("hornet_jump_right")->aniRender(getMemDC(),
                    _player.x - 186, _player.y - 145,
                    _player.curPlayAni);
            }
            // 달리기 낙하할 때
            if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                IMAGEMANAGER->findImage("hornet_jump_left")->aniRender(getMemDC(),
                    _player.x - 186, _player.y - 145,
                    _player.curPlayAni);
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                IMAGEMANAGER->findImage("hornet_jump_right")->aniRender(getMemDC(),
                    _player.x - 186, _player.y - 145,
                    _player.curPlayAni);
            }
            // 벽에 매달렸을 때
            if (_player.dirType == LEFT && _player.posType == HANGING &&
                _player.stateType == HANG && _player.jumpType == NON_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_hang_left")->aniRender(getMemDC(),
                    _player.x - 43, _player.y - 110,
                    _player.curPlayAni);
            }
            else if (_player.dirType == RIGHT && _player.posType == HANGING &&
                _player.stateType == HANG && _player.jumpType == NON_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_hang_right")->aniRender(getMemDC(),
                    _player.x - 85, _player.y - 110,
                    _player.curPlayAni);
            }
            // 벽점프할 때
            if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == WALL_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_jump_left")->aniRender(getMemDC(),
                    _player.x - 190, _player.y - 142,
                    _player.curPlayAni);
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == WALL_JUMP)
            {
                IMAGEMANAGER->findImage("hornet_jump_right")->aniRender(getMemDC(),
                    _player.x - 190, _player.y - 142,
                    _player.curPlayAni);
            }
        }

        // 평타는 플레이어 공격 모션 끝나면
        if (_player.atkType == NORMAL_ATTACK && _player.curPlayAtkAni != nullptr && !_player.curPlayAtkAni->isPlay())
        {
            _player.atkType = NON_ATTACK;
            _player.isAttack = false;
        }
    }
    
}


