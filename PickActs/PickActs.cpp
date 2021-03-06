// PickActs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "WolfRuleset.h"
#include "RulerRuleset.h"
#include "FuzzyModule.h"
#include <cmath>
#include <iostream>

int main()
{
	/*WolfRuleset* wolfRuleset = new WolfRuleset();

	wolfRuleset->WolfModule->Fuzzify("SizeOfTarget", 20.0);
	wolfRuleset->WolfModule->Fuzzify("HungerLevel", 1.0);
	wolfRuleset->WolfModule->Fuzzify("DistanceFromTarget", 0.0);
	wolfRuleset->WolfModule->Fuzzify("SelfTopSpeed", 1.0);

	double DesirableAction = wolfRuleset->WolfModule->Defuzzify("WolfAction", FuzzyModule::max_av);

	std::cout << "Desirability: " << std::endl;
	std::cout << "Desirable Action: " << DesirableAction << std::endl;
	std::cout << "Desirable Action Name: " << wolfRuleset->WolfModule->GetClosestSetName("WolfAction", DesirableAction) << std::endl;*/

	RulerRuleset* rulerRuleset = new RulerRuleset();

	rulerRuleset->RulerModule->Fuzzify("Unemployment", 20.0);
	rulerRuleset->RulerModule->Fuzzify("SafetyLevel", 16.0);
	rulerRuleset->RulerModule->Fuzzify("PerceivedUnrest", 32.0);
	rulerRuleset->RulerModule->Fuzzify("Isolation", 27.0);

	double DraftSoldiersDesirability = rulerRuleset->RulerModule->Defuzzify("DraftSoldiers", FuzzyModule::max_av);
	double SeekAllianceDesirability = rulerRuleset->RulerModule->Defuzzify("SeekAlliance", FuzzyModule::max_av);
	double IncreaseTaxesDesirability = rulerRuleset->RulerModule->Defuzzify("IncreaseTaxes", FuzzyModule::max_av);

	std::cout << "Draft Soldiers Desirability: " << DraftSoldiersDesirability  << std::endl;
	std::cout << "Seek Alliance Desirability: " << SeekAllianceDesirability << std::endl;
	std::cout << "Increase Taxes Desirability: " << IncreaseTaxesDesirability << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
