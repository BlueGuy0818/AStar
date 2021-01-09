#include "StateMachine.h"
#include "States.h"
#include "SpriteStates.h"

StateMachine::StateMachine(Sprite* sprite)
{
	previousState = NONE;
	currentState = STAND;
	this->sprite = sprite;
}

void StateMachine::enterState(int s)
{
	switch(s)
	{
		// 站立
		case STAND:
			Stand::enter(sprite);
			break;
			// 行走
		case WALK:
			Walk::enter(sprite);
			break;
			// 前进
		case FORWARD_WALK:
			ForwardWalk::enter(sprite);
			break;
			// 后退
		case BACKWARD_WALK:
			BackwardWalk::enter(sprite);
			break;
			// 快进
		case FORWARD_RUN:
			FastForwardRun::enter(sprite);
			break;
			// 快退
		case BACKWARD_RUN:
			FastBackwardRun::enter(sprite);
			break;
			// 跳跃
		case JUMP_UP:
			JumpUp::enter(sprite);
			break;
			// 下落
		case JUMP_DOWN:
			JumpDown::enter(sprite);
			break;
			// 起身
		case GO_UP:
			GoUp::enter(sprite);
			break;
			// 蹲下
		case GO_DOWN:
			GoDown::enter(sprite);
			break;
			// 攻击
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			Attack::enter(sprite);
			break;
			// 受伤
		case HURT:
			Hurt::enter(sprite);
			break;
			// 死亡
		case DEAD:
			Dead::enter(sprite);
			break;
	}
}

void StateMachine::executeState()
{
	switch(currentState)
	{
		// 站立
		case STAND:
			Stand::execute(sprite);
			break;
			// 行走
		case WALK:
			Walk::execute(sprite);
			break;
			// 前进
		case FORWARD_WALK:
			ForwardWalk::execute(sprite);
			break;
			// 后退
		case BACKWARD_WALK:
			BackwardWalk::execute(sprite);
			break;
			// 快进
		case FORWARD_RUN:
			FastForwardRun::execute(sprite);
			break;
			// 快退
		case BACKWARD_RUN:
			FastBackwardRun::execute(sprite);
			break;
			// 跳跃
		case JUMP_UP:
			JumpUp::execute(sprite);
			break;
			// 下落
		case JUMP_DOWN:
			JumpDown::execute(sprite);
			break;
		    // 蹲下
		case GO_DOWN:
			GoDown::execute(sprite);
			break;
			// 起身
		case GO_UP:
			GoUp::execute(sprite);
			break;
		    // 攻击
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			Attack::execute(sprite);
			break;
		    // 受伤
		case HURT:
			Hurt::execute(sprite);
			break;
		    // 死亡
		case DEAD:
			Dead::execute(sprite);
			break;
	}
}

void StateMachine::exitState(int s)
{
	switch(s)
	{
		// 站立
		case STAND:
			Stand::exit(sprite);
			break;
			// 行走
		case WALK:
			Walk::exit(sprite);
			break;
			// 前进
		case FORWARD_WALK:
			ForwardWalk::exit(sprite);
			break;
			// 后退
		case BACKWARD_WALK:
			BackwardWalk::exit(sprite);
			break;
			// 快进
		case FORWARD_RUN:
			FastForwardRun::exit(sprite);
			break;
			// 快退
		case BACKWARD_RUN:
			FastBackwardRun::exit(sprite);
			break;
			// 跳跃
		case JUMP_UP:
			JumpUp::exit(sprite);
			break;
			// 下落
		case JUMP_DOWN:
			JumpDown::exit(sprite);
			break;
			// 蹲下
		case GO_DOWN:
			GoDown::exit(sprite);
			break;
			// 起身
		case GO_UP:
			GoUp::exit(sprite);
			break;
			// 攻击
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			Attack::exit(sprite);
			break;
			// 受伤
		case HURT:
			Hurt::exit(sprite);
			break;
			// 死亡
		case DEAD:
			Dead::exit(sprite);
			break;
	}
}

void StateMachine::setCurrentState(int s)
{
	currentState = s;
}

int StateMachine::getCurrentState()
{
	return currentState;
}

void StateMachine::setPreviousState(int s)
{
	previousState = s;
}
	
int StateMachine::getPreviousState()
{
	return previousState;
}

void StateMachine::changeState(int newState)
{
	previousState = currentState;
	exitState(currentState);
	currentState = newState;
	enterState(newState);
}

void StateMachine::revertToPreviousState()
{
	changeState(previousState);
}
