//
//  rule.cpp
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

#include "rule.h"
//#include <assert.h>

using std::cout;
using std::endl;
using std::min_element;
using std::max_element;
using std::begin;
using std::end;

fuzzy::Rule::Rule() {
}

fuzzy::Rule::Rule(vector<FuzzySet *> antecedents, string conjunction, FuzzySet *consequent, string naturalLanguage) :
_antecedents(antecedents),
_conjunction(conjunction),
_consequent(consequent),
_naturalLanguage(naturalLanguage) {
}

fuzzy::FuzzySet* fuzzy::Rule::getConsequent() {
    return _consequent;
}

double fuzzy::Rule::fire(const std::vector<double> values) {
    mus.clear();
    
    for (size_t i = 0; i < _antecedents.size(); i++) {
        mus.push_back(_antecedents[i]->calculateMu(values[i]));
    }

    double mu;
    if (_conjunction == "and")  // AND == intersection == minimum
        mu = *min_element(begin(mus), end(mus));
    else // OR == union == maximum
        mu = *max_element(begin(mus), end(mus));

    //    cout << "Fired rule: µ choices are [";
    //    for (auto mu: mus) {
    //        cout << mu << ", ";
    //    }
    //    cout << "], final µ is " << mu << endl;
    
    return mu;
}
