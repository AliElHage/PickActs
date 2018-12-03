#include "pch.h"
#include "WolfRuleset.h"

WolfRuleset::WolfRuleset()
{
	InitializeWolfRuleset();
}

void WolfRuleset::InitializeWolfRuleset()
{
	WolfModule = new FuzzyModule();

	// Base Antecedants
	FuzzyVariable& SizeOfTarget = WolfModule->CreateFLV("SizeOfTarget");
	FuzzyVariable& HungerLevel = WolfModule->CreateFLV("HungerLevel");
	FuzzyVariable& DistanceFromTarget = WolfModule->CreateFLV("DistanceFromTarget");
	FuzzyVariable& SelfTopSpeed = WolfModule->CreateFLV("SelfTopSpeed");

	// Base Consequents
	FuzzyVariable& WolfAction = WolfModule->CreateFLV("WolfAction");

	// Degrees of antecedants
	FzSet SizeOfTarget_Small = SizeOfTarget.AddLeftShoulderSet("SizeOfTarget_Small", 0, 35, 50);
	FzSet SizeOfTarget_Medium = SizeOfTarget.AddTriangularSet("SizeOfTarget_Medium", 35, 50, 75);
	FzSet SizeOfTarget_Large = SizeOfTarget.AddRightShoulderSet("SizeOfTarget_Large", 50, 75, 100);

	FzSet HungerLevel_Low = HungerLevel.AddLeftShoulderSet("HungerLevel_Low", 0, 10, 20);
	FzSet HungerLevel_Medium = HungerLevel.AddTriangularSet("HungerLevel_Medium", 10, 20, 40);
	FzSet HungerLevel_High = HungerLevel.AddRightShoulderSet("HungerLevel_High", 20, 40, 100);

	FzSet DistanceFromTarget_Low = DistanceFromTarget.AddLeftShoulderSet("DistanceFromTarget_Low", 0, 30, 40);
	FzSet DistanceFromTarget_Medium = DistanceFromTarget.AddTriangularSet("DistanceFromTarget_Medium", 30, 40, 60);
	FzSet DistanceFromTarget_High = DistanceFromTarget.AddRightShoulderSet("DistanceFromTarget_High", 40, 60, 100);

	FzSet SelfTopSpeed_Low = SelfTopSpeed.AddLeftShoulderSet("SelfTopSpeed_Low", 0, 50, 65);
	FzSet SelfTopSpeed_Medium = SelfTopSpeed.AddTriangularSet("SelfTopSpeed_Medium", 50, 65, 80);
	FzSet SelfTopSpeed_High = SelfTopSpeed.AddRightShoulderSet("SelfTopSpeed_High", 65, 80, 100);

	// Degrees of consequents
	FzSet WolfAction_Flee = WolfAction.AddLeftShoulderSet("WolfAction_Flee", 0, 20, 40);
	FzSet WolfAction_Ignore = WolfAction.AddTriangularSet("WolfAction_Ignore", 20, 40, 60);
	FzSet WolfAction_Stalk = WolfAction.AddTriangularSet("WolfAction_Stalk", 40, 60, 80);
	FzSet WolfAction_Attack = WolfAction.AddRightShoulderSet("WolfAction_Attack", 60, 80, 100);

	WolfModule->AddRule(SizeOfTarget_Small, WolfAction_Attack);
	WolfModule->AddRule(SizeOfTarget_Medium, WolfAction_Stalk);
	WolfModule->AddRule(SizeOfTarget_Large, WolfAction_Flee);
	WolfModule->AddRule(HungerLevel_Low, WolfAction_Ignore);
	WolfModule->AddRule(HungerLevel_Medium, WolfAction_Stalk);
	WolfModule->AddRule(HungerLevel_High, WolfAction_Attack);
	WolfModule->AddRule(DistanceFromTarget_Low, WolfAction_Attack);
	WolfModule->AddRule(DistanceFromTarget_Medium, WolfAction_Stalk);
	WolfModule->AddRule(DistanceFromTarget_High, WolfAction_Ignore);
	WolfModule->AddRule(SelfTopSpeed_Low, WolfAction_Ignore);
	WolfModule->AddRule(SelfTopSpeed_Medium, WolfAction_Stalk);
	WolfModule->AddRule(SelfTopSpeed_High, WolfAction_Attack);
}