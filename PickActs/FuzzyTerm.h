#pragma once

class FuzzyTerm
{
public:

	// All terms must implement a virtual constructor
	virtual FuzzyTerm* Clone() const = 0;

	// Retrieves the degree of membership of the term
	virtual double GetDOM() const = 0;

	// Clears the degree of membership of the term
	virtual void ClearDOM() = 0;

	// Method for updating the DOM of a consequent when a rule fires
	virtual void ORwithDOM(double val) = 0;
};
