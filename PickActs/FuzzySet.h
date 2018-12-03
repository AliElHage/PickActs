#pragma once
#include <cmath>
#include "FuzzyTerm.h"

class FuzzySet
{
protected:

	// This will hold the degree of membership in this set of a given value
	double m_dDOM;

	// This is the maximum of the set's membership function. For instance, if
	// the set is triangular then this will be the peak point of the triangle.
	// If the set has a plateau then this value will be the midpoint of the
	// plateau. This value is set in the constructor to avoid run-time
	// calculation of mid-point values.
	double m_dRepresentativeValue;

public:

	FuzzySet(double RepVal):m_dDOM(0.0), m_dRepresentativeValue(RepVal){}

	// Return the degree of membership in this set of the given value. NOTE:
	// this does not set m_dDOM to the DOM of the value passed as the parameter.
	// This is because the centroid defuzzification method also uses this method
	// to determine the DOMs of the values it uses as its sample points.
	virtual double CalculateDOM(double val) const = 0;

	// If this fuzzy set is part of a consequent FLV and it is fired by a rule,
	// then this method sets the DOM (in this context, the DOM represents a
	// confidence level) to the maximum of the parameter value or the set's
	// existing m_dDOM value
	void ORwithDOM(double val) { m_dDOM = std::fmax(m_dDOM, val); }

	// Accessor methods
	double GetRepresentativeVal() const { return m_dRepresentativeValue; }
	void ClearDOM() { m_dDOM = 0.0; }
	double GetDOM() const { return m_dDOM; }
	void SetDOM(double val) { m_dDOM = val; }
};


#ifndef PROXY_FUZZY_SET
#define PROXY_FUZZY_SET

class FzAND;

class FzSet : public FuzzyTerm
{
private:

	//let the hedge classes be friends 
	friend class FzVery;
	friend class FzFairly;

private:

	//a reference to the fuzzy set this proxy represents
	FuzzySet& m_Set;

public:

	FzSet(FuzzySet& fs): m_Set(fs) {}

	FuzzyTerm* Clone()const { return new FzSet(*this); }
	double GetDOM() const { return m_Set.GetDOM(); }
	void ClearDOM() { m_Set.ClearDOM(); }
	void ORwithDOM(double val) { m_Set.ORwithDOM(val); }
};


#endif
