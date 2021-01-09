#ifndef __STATE_MACHINE_H_
#define __STATE_MACHINE_H_

#include "Sprite\Sprite.h"

class Sprite;
class StateMachine
{
public:
	Sprite* sprite;		
	
	int currentState;

	int previousState;

	StateMachine(Sprite* sprite);

	void enterState(int s);

	void executeState();

	void exitState(int s);

	void setCurrentState(int s);

	void setPreviousState(int s);

	int getCurrentState();

	int getPreviousState();	

	void changeState(int newState);

	void revertToPreviousState();
};

#endif
