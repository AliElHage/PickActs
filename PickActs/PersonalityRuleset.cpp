#include "pch.h"
#include "PersonalityRuleset.h"

PersonalityRuleset::PersonalityRuleset()
{
	BaseModule = new FuzzyModule();

	// Base Antecedants
	FuzzyVariable& ArmyFullnessRatio = BaseModule->CreateFLV("ArmyFullnessRatio");
	FuzzyVariable& DraftableNumber = BaseModule->CreateFLV("DraftableNumber");
	FuzzyVariable& PerceivedUnrest = BaseModule->CreateFLV("PerceivedUnrest");

	// Base Consequents
	FuzzyVariable& NeedForSoldiers = BaseModule->CreateFLV("NeedForSoldiers");
	FuzzyVariable& DraftGravity = BaseModule->CreateFLV("DraftGravity");

	// Degrees of antecedants
	FzSet ArmyFullnessRatio_Low = ArmyFullnessRatio.AddLeftShoulderSet("ArmyFullnessRatio_Low", 0, 60, 75);
	FzSet ArmyFullnessRatio_Medium = ArmyFullnessRatio.AddTriangularSet("ArmyFullnessRatio_Medium", 60, 75, 90);
	FzSet ArmyFullnessRatio_High = ArmyFullnessRatio.AddRightShoulderSet("ArmyFullnessRatio_High", 75, 90, 100);
	
	FzSet DraftableNumber_Low = DraftableNumber.AddLeftShoulderSet("DraftableNumber_Low", 0, 25, 50);
	FzSet DraftableNumber_Medium = DraftableNumber.AddTriangularSet("DraftableNumber_Medium", 25, 50, 75);
	FzSet DraftableNumber_High = DraftableNumber.AddRightShoulderSet("DraftableNumber_High", 50, 75, 100);

	FzSet PerceivedUnrest_Low = PerceivedUnrest.AddLeftShoulderSet("PerceivedUnrest_Low", 0, 15, 30);
	FzSet PerceivedUnrest_Medium = PerceivedUnrest.AddTriangularSet("PerceivedUnrest_Medium", 15, 30, 45);
	FzSet PerceivedUnrest_High = PerceivedUnrest.AddRightShoulderSet("PerceivedUnrest_High", 30, 45, 100);

	// Degrees of consequents
	FzSet NeedForSoldiers_Low = NeedForSoldiers.AddLeftShoulderSet("NeedForSoldiers_Low", 0, 25, 50);
	FzSet NeedForSoldiers_Medium = NeedForSoldiers.AddLeftShoulderSet("NeedForSoldiers_Medium", 25, 50, 75);
	FzSet NeedForSoldiers_High = NeedForSoldiers.AddRightShoulderSet("NeedForSoldiers_High", 50, 75, 100);

	FzSet DraftGravity_Low = DraftGravity.AddLeftShoulderSet("DraftGravity_Low", 0, 25, 50);
	FzSet DraftGravity_Medium = DraftGravity.AddTriangularSet("DraftGravity_Medium", 25, 50, 75);
	FzSet DraftGravity_High = DraftGravity.AddRightShoulderSet("DraftGravity_High", 50, 75, 100);
	
	// Knight ruleset
	KnightModule = BaseModule;

	KnightModule->AddRule(ArmyFullnessRatio_Low, NeedForSoldiers_High);
	KnightModule->AddRule(ArmyFullnessRatio_Medium, NeedForSoldiers_Medium);
	KnightModule->AddRule(ArmyFullnessRatio_High, NeedForSoldiers_Low);

	KnightModule->AddRule(DraftableNumber_Low, DraftGravity_Low);
	KnightModule->AddRule(DraftableNumber_Medium, DraftGravity_Medium);
	KnightModule->AddRule(DraftableNumber_High, DraftGravity_High);
	KnightModule->AddRule(PerceivedUnrest_Low, DraftGravity_High);
	KnightModule->AddRule(PerceivedUnrest_Medium, DraftGravity_Medium);
	KnightModule->AddRule(PerceivedUnrest_High, DraftGravity_Low);

}

void PersonalityRuleset::InitializeKnightRuleset()
{
	
}