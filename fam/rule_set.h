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
#include <unordered_map>
#include <memory>
#include "rule.h"

namespace fuzzy {
    class RuleSet {
    private:
        std::string _name;
        std::string _implication;
        std::vector<std::shared_ptr<Rule>> _rules;
        vector<std::shared_ptr<FuzzySet>> consequents;

        typedef std::unordered_map<std::shared_ptr<FuzzySet>, double> mu_map;
        mu_map consequent_mus;
        mu_map::iterator p;

    public:
        RuleSet();
        RuleSet(std::string name, std::string implication);

        std::string name();
        void addRule(std::shared_ptr<Rule> const r);
        double calculate(std::vector<double> values);
    };
}

#endif /* defined(__fam__rule_set__) */
