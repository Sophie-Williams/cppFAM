//
//  rule_set.h
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

#ifndef __fam__rule_set__
#define __fam__rule_set__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "rule.h"

using std::map;
using std::unique_ptr;

namespace fuzzy {
    enum Implication { MAMDANI, LARSEN };
    
    /**
     A RuleSet is a collection of related rules that govern a particular decision,
     e.g. "fan speed" or "shotgun desirability".
     */
    class RuleSet {
    private:
        std::string _name;
        Implication _implication;
        std::vector<Rule> _rules;

        typedef map<const Trapezoid*, double> mu_map;
        mu_map _consequent_mus;

    public:
        RuleSet();                                          // default constructor
        RuleSet(std::string name, Implication implication); // constructor

        /**
         Retrieve the ruleset's natural-language name
         @return the name in string form
         */
        std::string name() const { return _name; }

        /**
         Add an existing rule to the ruleset.
         @param r an rvalue-reference to a Rule
         */
        void add(Rule &&r) {
            _rules.push_back(std::move(r));
        }

        /**
         Given a collection of inputs, calculate the ruleset's result. This means,
         fire all the rules to calculate each rule's µ ; choosing the highest µ
         for every consequent ; weighting the consequents (implication) by their µ
         values ; finally, adding up the weighted consequents to achieve a final 
         calculation.
         @param values A vector of inputs (each a double)
         @return the result in double form
         */
        double calculate(const std::vector<const double> values) ;
    };
}

#endif /* defined(__fam__rule_set__) */
