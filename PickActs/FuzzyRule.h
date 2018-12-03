#pragma once
#include "FuzzyTerm.h"

class FuzzyRule
{
private:

	// Antecedant (usually a composite of several fuzzy sets and operators)
	const FuzzyTerm* m_pAntecedent;

	// Consequence (usually a single fuzzy set, but can be several ANDed together)
	FuzzyTerm* m_pConsequence;

	// It doesn't make sense to allow clients to copy rules
	FuzzyRule(const FuzzyRule&);
	FuzzyRule& operator=(const FuzzyRule&);

public:

	FuzzyRule(FuzzyTerm& ant, FuzzyTerm& con): m_pAntecedent(ant.Clone()),
											   m_pConsequence(con.Clone())
	{}

	~FuzzyRule()
	{
		delete m_pAntecedent;
		delete m_pConsequence;
	}

	void SetConfidenceOfConsequentToZero()
	{
		m_pConsequence->ClearDOM();
	}

	// This method updates the DOM (the confidence) of the consequent term with
	// the DOM of the antecedant term.
	void Calculate()
	{
		m_pConsequence->ORwithDOM(m_pAntecedent->GetDOM());
	}
};
