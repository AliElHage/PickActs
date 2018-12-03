#pragma once
#include <map>
#include <string>
#include"FuzzySet.h"

class FuzzyVariable
{
private:

	typedef std::map<std::string, FuzzySet*> MemberSets;

	// Disallow copies
	FuzzyVariable(const FuzzyVariable&);
	FuzzyVariable& operator=(const FuzzyVariable&);

	// A map of the fuzzy sets that comprise this variable
	MemberSets m_MemberSets;

	// The minimum and maximum value of the range of this variable
	double m_dMinRange;
	double m_dMaxRange;

	// This method is called with the upper and lower bound of a set each time a 
	// new set is added to adjust the upper and lower range values accordingly
	void AdjustRangeToFit(double min, double max);

	// A client retrieves a reference to a fuzzy variable when an instance is
	// created via FuzzyModule::CreateFLV(). To prevent the client from deleting
	// the instance the FuzzyVariable destructor is made private and the
	// FuzzyModule class made a friend.
	~FuzzyVariable();

	friend class FuzzyModule;

public:
	
	FuzzyVariable():m_dMinRange(0.0), m_dMaxRange(0.0){}

	// The following methods create instances of the sets named in the method
	// name and adds them to the member set map. Each time a set of any type is
	// added the m_dMinRange and m_dMaxRange are adjusted accordingly. All of the
	// methods return a proxy class representing the newly created instance. This
	// proxy set can be used as an operand when creating the rule base.
	FzSet AddLeftShoulderSet(std::string name,
							 double minBound,
							 double peak,
							 double maxBound);

	FzSet AddRightShoulderSet(std::string name,
							 double minBound,
							 double peak,
							 double maxBound);

	FzSet AddTriangularSet(std::string name,
							 double minBound,
							 double peak,
							 double maxBound);

	FzSet AddSingletonSet(std::string name,
							 double minBound,
							 double peak,
							 double maxBound);
	
	// Fuzzify a value by calculating its DOM in each of this variable's subsets
	void Fuzzify(double val);

	// Defuzzify the variable using the MaxAv method
	double Defuzzify() const;

	// Defuzzify the variable using the centroid method
	double DefuzzifyCentroid(int numSamples) const;
};
