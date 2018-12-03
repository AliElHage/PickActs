#include "pch.h"
#include "FuzzyModule.h"
#include <cassert>

#ifndef FUZZY_MODULE_H
#define FUZZY_MODULE_H

//------------------------------ dtor -----------------------------------------

FuzzyModule::~FuzzyModule()
{
	VarMap::iterator curVar = m_Variables.begin();
	for (curVar; curVar != m_Variables.end(); ++curVar)
	{
		delete curVar->second;
	}

	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		delete *curRule;
	}
}

//----------------------------- AddRule ---------------------------------------
void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
	m_Rules.push_back(new FuzzyRule(antecedent, consequence));
}


//-------------------------- CreateFLV ---------------------------
//
//  creates a new fuzzy variable and returns a reference to it
//-----------------------------------------------------------------------------
FuzzyVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
	m_Variables[VarName] = new FuzzyVariable();;

	return *m_Variables[VarName];
}

//-------------------------- GetClosestSetName ---------------------------
//
//  Gets the name of the set the value belongs to the most.
//-----------------------------------------------------------------------------
std::string FuzzyModule::GetClosestSetName(std::string nameOfFLV, double val)
{
	assert((m_Variables.find(nameOfFLV) != m_Variables.end()));

	double currentDifference = std::numeric_limits<double>::max();
	std::string closestSetName;

	std::map<std::string, FuzzySet*> memberSets = m_Variables[nameOfFLV]->m_MemberSets;

	std::map<std::string, FuzzySet*>::const_iterator curSet;
	for (curSet = memberSets.begin(); curSet != memberSets.end(); ++curSet)
	{
		double diff = std::abs(curSet->second->GetRepresentativeVal() - val);
		if (diff < currentDifference)
		{
			currentDifference = diff;
			closestSetName = curSet->first;
		}
	}

	return closestSetName;
}

#endif