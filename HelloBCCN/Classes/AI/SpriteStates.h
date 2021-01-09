#ifndef __SPRITE_STATES_H_
#define __SPRITE_STATES_H_

#include "Sprite\Sprite.h"

// 站立
class Sprite;
class Stand
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 行走
class Walk
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 前进
class ForwardWalk
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 后退
class BackwardWalk
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 快进
class FastForwardRun
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 快退
class FastBackwardRun
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 跳跃
class JumpUp
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 下落
class JumpDown
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 蹲下
class GoDown
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 起身
class GoUp
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 攻击
class Attack
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 受伤
class Hurt
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// 死亡
class Dead
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

#endif