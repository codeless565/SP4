#include "GameObject.h"

#include "Message/PostOffice.h"
#include "Message/ConcreteMessages.h"


GameObject::GameObject(TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	sm(NULL),
	nearest(NULL)
{
}

GameObject::~GameObject()
{
	if (sm)
	{
		delete sm;
		sm = NULL;
	}
}

void GameObject::Update(double dt)
{
}

bool GameObject::Handle(Message *message)
{
	MessageWRU *messageWRU = dynamic_cast<MessageWRU*>(message);

	if (messageWRU)
	{
		delete message;
		return true;
	}
	delete message;
	return false;
}