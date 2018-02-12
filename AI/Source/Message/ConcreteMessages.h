#ifndef CONCRETE_MESSAGE_H
#define CONCRETE_MESSAGE_H

#include "Message.h"
#include "../GameObject.h"

struct MessageWRU : public Message
{
	enum SEARCH_TYPE
	{
		MESSAGE_NONE = 0,


		MESSAGE_TOTAL
	};

	MessageWRU(GameObject *goValue, SEARCH_TYPE typeValue, float number = 0) : go(goValue), type(typeValue), number(number) {}
	
	virtual ~MessageWRU() {}

	GameObject *go;
	SEARCH_TYPE type;
	float number;
};

#endif
