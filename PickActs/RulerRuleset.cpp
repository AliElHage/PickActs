#include "pch.h"
#include "RulerRuleset.h"

RulerRuleset::RulerRuleset()
{
	InitializeRulerRuleset();
}

void RulerRuleset::InitializeRulerRuleset()
{
	RulerModule = new FuzzyModule();

	// Base Antecedants
	FuzzyVariable& Unemployment = RulerModule->CreateFLV("Unemployment");
	FuzzyVariable& SafetyLevel = RulerModule->CreateFLV("SafetyLevel");
	FuzzyVariable& PerceivedUnrest = RulerModule->CreateFLV("PerceivedUnrest");
	FuzzyVariable& Isolation = RulerModule->CreateFLV("Isolation");

	// Base Consequents
	FuzzyVariable& DraftSoldiers = RulerModule->CreateFLV("DraftSoldiers");
	FuzzyVariable& SeekAlliance = RulerModule->CreateFLV("SeekAlliance");
	FuzzyVariable& IncreaseTaxes = RulerModule->CreateFLV("IncreaseTaxes");

	// Degrees of antecedants
	FzSet Unemployment_Small = Unemployment.AddLeftShoulderSet("Unemployment_Small", 0, 35, 50);
	FzSet Unemployment_Medium = Unemployment.AddTriangularSet("Unemployment_Medium", 35, 50, 75);
	FzSet Unemployment_Large = Unemployment.AddRightShoulderSet("Unemployment_Large", 50, 75, 100);

	FzSet SafetyLevel_Low = SafetyLevel.AddLeftShoulderSet("SafetyLevel_Low", 0, 10, 20);
	FzSet SafetyLevel_Medium = SafetyLevel.AddTriangularSet("SafetyLevel_Medium", 10, 20, 40);
	FzSet SafetyLevel_High = SafetyLevel.AddRightShoulderSet("SafetyLevel_High", 20, 40, 100);

	FzSet PerceivedUnrest_Low = PerceivedUnrest.AddLeftShoulderSet("PerceivedUnrest_Low", 0, 30, 40);
	FzSet PerceivedUnrest_Medium = PerceivedUnrest.AddTriangularSet("PerceivedUnrest_Medium", 30, 40, 60);
	FzSet PerceivedUnrest_High = PerceivedUnrest.AddRightShoulderSet("PerceivedUnrest_High", 40, 60, 100);

	FzSet Isolation_Low = Isolation.AddLeftShoulderSet("Isolation_Low", 0, 50, 65);
	FzSet Isolation_Medium = Isolation.AddTriangularSet("Isolation_Medium", 50, 65, 80);
	FzSet Isolation_High = Isolation.AddRightShoulderSet("Isolation_High", 65, 80, 100);

	// Degrees of consequents
	FzSet DraftSoldiers_Undesirable = DraftSoldiers.AddLeftShoulderSet("DraftSoldiers_Undesirable", 0, 20, 40);
	FzSet DraftSoldiers_Desirable = DraftSoldiers.AddTriangularSet("DraftSoldiers_Desirable", 20, 40, 60);
	FzSet DraftSoldiers_VeryDesirable = DraftSoldiers.AddTriangularSet("DraftSoldiers_VeryDesirable", 40, 60, 80);

	FzSet SeekAlliance_Undesirable = SeekAlliance.AddLeftShoulderSet("SeekAlliance_Undesirable", 0, 20, 40);
	FzSet SeekAlliance_Desirable = SeekAlliance.AddTriangularSet("SeekAlliance_Desirable", 20, 40, 60);
	FzSet SeekAlliance_VeryDesirable = SeekAlliance.AddTriangularSet("SeekAlliance_VeryDesirable", 40, 60, 80);

	FzSet IncreaseTaxes_Undesirable = IncreaseTaxes.AddLeftShoulderSet("IncreaseTaxes_Undesirable", 0, 20, 40);
	FzSet IncreaseTaxes_Desirable = IncreaseTaxes.AddTriangularSet("IncreaseTaxes_Desirable", 20, 40, 60);
	FzSet IncreaseTaxes_VeryDesirable = IncreaseTaxes.AddTriangularSet("IncreaseTaxes_VeryDesirable", 40, 60, 80);

	// Draft Soldiers Rules
	RulerModule->AddRule(Unemployment_Small, DraftSoldiers_Undesirable);
	RulerModule->AddRule(Unemployment_Medium, DraftSoldiers_Desirable);
	RulerModule->AddRule(Unemployment_Large, DraftSoldiers_VeryDesirable);
	RulerModule->AddRule(SafetyLevel_Low, DraftSoldiers_VeryDesirable);
	RulerModule->AddRule(SafetyLevel_Medium, DraftSoldiers_Desirable);
	RulerModule->AddRule(SafetyLevel_High, DraftSoldiers_Undesirable);
	RulerModule->AddRule(PerceivedUnrest_Low, DraftSoldiers_Undesirable);
	RulerModule->AddRule(PerceivedUnrest_Medium, DraftSoldiers_Desirable);
	RulerModule->AddRule(PerceivedUnrest_High, DraftSoldiers_VeryDesirable);

	// Seek Alliances Rules
	RulerModule->AddRule(Unemployment_Small, SeekAlliance_Desirable);
	RulerModule->AddRule(Unemployment_Medium, SeekAlliance_Desirable);
	RulerModule->AddRule(Unemployment_Large, SeekAlliance_VeryDesirable);
	RulerModule->AddRule(Isolation_Low, SeekAlliance_Desirable);
	RulerModule->AddRule(Isolation_Medium, SeekAlliance_VeryDesirable);
	RulerModule->AddRule(Isolation_High, SeekAlliance_VeryDesirable);


	// Increase Taxes Rules
	RulerModule->AddRule(Unemployment_Small, IncreaseTaxes_VeryDesirable);
	RulerModule->AddRule(Unemployment_Medium, IncreaseTaxes_Desirable);
	RulerModule->AddRule(Unemployment_Large, IncreaseTaxes_Undesirable);
	RulerModule->AddRule(PerceivedUnrest_Low, IncreaseTaxes_Desirable);
	RulerModule->AddRule(PerceivedUnrest_Medium, IncreaseTaxes_Undesirable);
	RulerModule->AddRule(PerceivedUnrest_High, IncreaseTaxes_Undesirable);
	RulerModule->AddRule(Isolation_Low, IncreaseTaxes_Desirable);
	RulerModule->AddRule(Isolation_Medium, IncreaseTaxes_Undesirable);
	RulerModule->AddRule(Isolation_High, IncreaseTaxes_Undesirable);
}