#ifndef STATE_ATTACK_H
#define STATE_ATTACK_H

#include "State.h"
#include "../GameObject.h"

/*****************************
Dota Minion State: Attack
*****************************/
class StateAttack : public State
{
	GameObject *m_go;
public:
	StateAttack(const std::string &stateID, GameObject *go);
	~StateAttack();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

/*****************************
Dota Tower State: Attack
*****************************/
class StateTowerAttack : public State
{
	GameObject *m_go;
public:
	StateTowerAttack(const std::string &stateID, GameObject *go);
	~StateTowerAttack();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};

#endif