#include "StateAttack.h"

#include "../Message/PostOffice.h"
#include "../Message/ConcreteMessages.h"

#include "../../Common/Source/MyCalculatorHelper.h"

/****************************************
Dota Minion State: Attack
****************************************/
StateAttack::StateAttack(const std::string & stateID, GameObject * go)
	:State(stateID),
	m_go(go)
{
}

StateAttack::~StateAttack()
{
}

void StateAttack::Enter()
{
}

void StateAttack::Update(double dt)
{
}

void StateAttack::Exit()
{
}
