#pragma once

#include <map>
#include <vector>
#include <string>
#include "FuzzyVariable.h"
#include "FuzzyTerm.h"
#include "FuzzyRule.h"
#include "FuzzyOperators.h"

class FuzzyModule
{
private:
	typedef std::map<std::string, FuzzyVariable*> VarMap;

public:

	// A client must pass one of these values to the defuzzify method.
	// This module only supports the MaxAv and centroid methods.
	enum DefuzzifyType{max_av, centroid};

	// When calculating the centroid of the fuzzy manifold this value is
	// used to determine how many cross sections should be sampled
	enum { NumSamplesToUseForCentroid = 15 };

private:

	// A map of all the fuzzy variables this module uses
	VarMap m_Variables;

	// A vector containing all the fuzzy rules
	std::vector<FuzzyRule*> m_Rules;

	// Zeroes the DOMs of the consequents of each rule. Used by Defuzzify().
	inline void SetConfidencesOfConsequentsToZero();

public:

	~FuzzyModule();

	// Creates a new "empty" fuzzy variable and returns a reference to it.
	FuzzyVariable& CreateFLV(const std::string& VarName);

	// Adds a rule to the module
	void AddRule(FuzzyTerm& antecedant, FuzzyTerm& consequence);

	// This method calls the Fuzzify method of the named FLV
	inline void Fuzzify(const std::string& NameOfFLV, double val);

	// Given a fuzzy variable and a defuzzification method this returns a
	// crisp value
	inline double Defuzzify(const std::string& key, DefuzzifyType method);

	// Get the name of the set the input belongs to the most. Used when consequent sets
	// are a mapping of different variables rather than degrees of the same variable
	std::string GetClosestSetName(std::string nameOfFLV, double val);
};

//-------------------------- ClearConsequents ---------------------------------
//
//  zeros the DOMs of the consequents of each rule
//-----------------------------------------------------------------------------
inline void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		(*curRule)->SetConfidenceOfConsequentToZero();
	}
}

//  this method calls the Fuzzify method of the variable with the same name
//  as the key
//-----------------------------------------------------------------------------
inline void FuzzyModule::Fuzzify(const std::string& NameOfFLV, double val)
{
	//first make sure the key exists
	assert((m_Variables.find(NameOfFLV) != m_Variables.end()) &&
		"<FuzzyModule::Fuzzify>:key not found");

	m_Variables[NameOfFLV]->Fuzzify(val);
}

//---------------------------- DeFuzzify --------------------------------------
//
//  given a fuzzy variable and a defuzzification method this returns a 
//  crisp value
//-----------------------------------------------------------------------------
inline double FuzzyModule::Defuzzify(const std::string& NameOfFLV, DefuzzifyType method)
{
	//first make sure the key exists
	assert((m_Variables.find(NameOfFLV) != m_Variables.end()) &&
		"<FuzzyModule::DeFuzzifyMaxAv>:key not found");

	//clear the DOMs of all the consequents of all the rules
	SetConfidencesOfConsequentsToZero();

	//process the rules
	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		(*curRule)->Calculate();
	}

	// now defuzzify the resultant conclusion using the specified method
	switch (method)
	{
	case centroid:
		return m_Variables[NameOfFLV]->DefuzzifyCentroid(NumSamplesToUseForCentroid);
		break;
	case max_av:
		return m_Variables[NameOfFLV]->Defuzzify();
		break;
	}
	return 0;
}
