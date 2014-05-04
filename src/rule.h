//
//  rule.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//
//  This file is part of The C++ Fuzzy Associative Memory
//  http://github.com/cpowell/fuzzy-associative-memory-cplusplus
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the library.
//

#ifndef __fam__rule__
#define __fam__rule__

#include <string>
#include <vector>

#include "fuzzy_set.h"

using std::unique_ptr;

namespace fuzzy {
    enum Conjunction {INTERSECTION, UNION};

    class Rule {
    private:
        // A rule has one or more antecedent FuzzySets
        std::vector<FuzzySet*> _antecedents;

        // The conjunction joins the antecedents together
        Conjunction _conjunction;

        // Holds the calculated mu values for each antecedent upon firing
//        std::vector<double> mus;

        // When a rule fires, it returns the degree-of-fit of this consequent
        FuzzySet* _consequent;

        // This is just a human-readable summary of what this rule does
        std::string _naturalLanguage;

    public:
        Rule();

        /**
         Construct a rule.
         @param antecedents a vector of one or more FuzzySets 
         @param conjunction how the antecedent mu will be chosen at fire-time (intersection or union)
         @param consequent a FuzzySet that is the result of this Rule
         @param naturalLanguage an optional human-readable summary of this rule
         */
        Rule(const std::vector<FuzzySet*>antecedents, const Conjunction conjunction, FuzzySet* const consequent, const std::string naturalLanguage="");

        /**
         Retrieve this rule's consequent.
         */
        FuzzySet *consequent() const { return _consequent; }

        /**
         Fire the rule and determine its degree of fit (µ), given the provided input values.
         This means, it goes through the antecedent fuzzy-sets, calculates the µ value of each,
         and chooses a µ value according to the rule's conjunction.
         The size of 'values' must equal the size of the antecedents vector.
         @param values a vector of input values, one for each antecedent
         @return this rule's degree-of-fit (µ) as a double
         */
        double fire(const std::vector<double> values) const;
    };
}

#endif /* defined(__fam__rule__) */
