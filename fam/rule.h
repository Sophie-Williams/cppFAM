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

#include <iostream>
#include <vector>
#include "fuzzy_set.h"

using std::string;
using std::vector;

namespace fuzzy {
    class Rule {
    private:
        std::vector<FuzzySet *> _antecedents;
        std::string _conjunction;
        FuzzySet *_consequent;
        std::string _naturalLanguage;
        std::vector<double> mus;

    public:
        Rule();
        Rule(const vector<FuzzySet *>antecedents, const string conjunction, FuzzySet *const consequent, const string naturalLanguage);

        FuzzySet *getConsequent();

        double fire(const vector<double> values);
    };
}

#endif /* defined(__fam__rule__) */
