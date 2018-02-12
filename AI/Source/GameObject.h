#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "StateMachine\StateMachine.h"
#include "Message\ObjectBase.h"

#include <vector>

struct GameObject : public ObjectBase
{
	enum TYPE
	{
		GO_NONE = 0,

		GO_TOTAL, //must be last
	};

	std::string address;

	//States
	StateMachine *sm;

	TYPE type;
	GameObject* nearest;
	
	Vector3 pos;
	Vector3 vel;
	Vector3 target;
	Vector3 scale;
	bool active;

	int id;

	GameObject(TYPE typeValue = GO_NONE);
	~GameObject();

	void Update(double dt);
	virtual bool Handle(Message *message);
};

#endif