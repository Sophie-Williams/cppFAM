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

//#include <iostream>

fuzzy::Rule::Rule() {
    //nop
}

fuzzy::Rule::Rule(const std::vector<FuzzySet*>antecedents, const Conjunction conjunction, FuzzySet *const consequent, const std::string naturalLanguage) :
_antecedents(antecedents),
_conjunction(conjunction),
_consequent(consequent),
_naturalLanguage(naturalLanguage) {
    //nop
}

double fuzzy::Rule::fire(const std::vector<const double> values) const {
    std::vector<double> mus;

    // TODO check that the two sizes are equal
    for (size_t i = 0; i < _antecedents.size(); ++i) {
        mus.push_back(_antecedents[i]->calculateMu(values[i]));
    }

    double mu;

    if (_conjunction == Conjunction::AND)  // AND == intersection == minimum
        mu = *std::min_element(begin(mus), end(mus));
    else // OR == union == maximum
        mu = *std::max_element(begin(mus), end(mus));

//    std::cout << "Fired rule: µ choices are [";
//    for (const auto &mu: mus) {
//        std::cout << mu << ", ";
//    }
//    std::cout << "], final µ is " << mu << std::endl;

    return mu;
}
