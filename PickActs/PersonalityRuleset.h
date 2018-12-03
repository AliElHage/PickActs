#pragma once
#include "FuzzyModule.h"

class PersonalityRuleset
{
public:

	FuzzyModule* BaseModule;
	FuzzyModule* KnightModule;

	PersonalityRuleset();

	void InitializeKnightRuleset();
};
