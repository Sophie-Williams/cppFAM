//
//  rule.cpp
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#include "rule.h"
//#include <assert.h>

using std::cout;
using std::endl;

Rule::Rule() {
}

Rule::Rule(vector<FuzzySet *> antecedents, string conjunction, FuzzySet *consequent, string naturalLanguage) :
_antecedents(antecedents),
_conjunction(conjunction),
_consequent(consequent),
_naturalLanguage(naturalLanguage) {
}

double Rule::fire(std::vector<double> values) {
    vector<double> mus;

    for (size_t i = 0; i < _antecedents.size(); i++) {
        mus.push_back(_antecedents[i]->calculateMu(values[i]));
    }

    double mu;
    if (_conjunction == "and") {
        // AND == intersection == minimum
        mu = *std::min_element(std::begin(mus), std::end(mus)); // c++11
    } else {
        // OR == union == maximum
        mu = *std::max_element(std::begin(mus), std::end(mus)); // c++11
    }

//    cout << "Fired rule: µ choices are [";
//    for (auto mu: mus) {
//        cout << mu << ", ";
//    }
//    cout << "], final µ is " << mu << endl;

    return mu;
}

FuzzySet* Rule::getConsequent() {
    return _consequent;
}
