#pragma once

#include "SingletonTemplate.h"

class MyCalculatorHelper : public Singleton<MyCalculatorHelper>
{
	friend Singleton<MyCalculatorHelper>;

public:

	float dota_calculateDMG(float _myattack, float _otherdefense, float _myarmorpenetration = 0, float _otherarmor = 0)
	{
		return _myattack / _otherdefense * _myattack;
	}


};