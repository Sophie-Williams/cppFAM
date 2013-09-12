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

using std::string;
using std::map;
using std::shared_ptr;
using std::vector;

namespace fuzzy {
    class RuleSet {
    private:
        string _name;
        string _implication;
        vector<shared_ptr<Rule>> _rules;

        typedef map<shared_ptr<FuzzySet>, double> mu_map;
        mu_map _consequent_mus;
        mu_map::iterator _mmi;

    public:
        RuleSet();                                // default constructor
        RuleSet(string name, string implication); // constructor

        /**
         Retrieve the ruleset's natural-language name
         @return the name in string form
         */
        string name() {
            return _name;
        }

        /**
         Add an existing rule to the ruleset.
         @param r A Rule instance
         */
        void addRule(shared_ptr<Rule> const r) {
            _rules.push_back(r);
        }

        /**
         Given a collection of inputs, calculate the ruleset's result.
         @param values A vector of inputs (each a double)
         @return the result in double form
         */
        double calculate(vector<double> values);
    };
}

#endif /* defined(__fam__rule_set__) */
