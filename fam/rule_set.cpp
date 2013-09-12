//
//  rule_set.cpp
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

#include "rule_set.h"

using std::vector;
using std::pair;
using std::string;
using std::shared_ptr;

fuzzy::RuleSet::RuleSet() :
_name(""),
_implication("")
{
    //nop
}

fuzzy::RuleSet::RuleSet(string name, string implication) :
_name(name),
_implication(implication)
{
    //nop
}


double fuzzy::RuleSet::calculate(vector<double> inputValues) {

    // Fire each rule to determine the µ value (degree of fit).
    for (const auto& rule : _rules) {
        double mu = rule->fire(inputValues);

        // Since any given consequent may have been activated more than once, we
        // need to get just a single µ value out -- we only care about the 'best'
        // µ. A popular way of doing so is to OR the values together, i.e. keep the
        // maximum µ value and discard the others.
        _mmi = _consequent_mus.find(rule->getConsequent());
        if (_mmi != _consequent_mus.end() && mu > _mmi->second) {
            _mmi->second = mu; // keep the max mu
        } else {
            // Didn't find
            _consequent_mus.insert(pair<shared_ptr<FuzzySet>, double>(rule->getConsequent(), mu));
        }
    }

    // Using each µ value, alter the consequent fuzzy set's polgyon. This is
    // called implication, and 'weights' the consequents properly. There are
    // several common ways of doing it, such as Larsen (scaling) and Mamdani
    // (clipping).
    //
    // Defuzzify into a discrete & usable value by adding up the weighted
    // consequents' contributions to the output. Again there are several ways
    // of doing it, such as computing the centroid of the combined 'mass', or
    // the 'mean of maximum' of the tallest set(s). Here we use the "Average
    // of Maxima" summation mechanism. MaxAv is defined as:
    // (∑ representative value * height) / (∑ height) for all output sets
    // where 'representative value' is shape-dependent.
    double numerator=0;
    double denominator=0;

        if (_implication == "mamdani") {
            for ( const auto& item : _consequent_mus) {
                shared_ptr<FuzzySet> tmp((item.first)->mamdami(item.second));
                numerator += (tmp->calculateXCentroid() * tmp->getHeight());
                denominator += tmp->getHeight();
            }
        } else {
            for ( const auto& item : _consequent_mus) {
                shared_ptr<FuzzySet> tmp((item.first)->larsen(item.second));
                numerator += (tmp->calculateXCentroid() * tmp->getHeight());
                denominator += tmp->getHeight();
            }
        }

    _consequent_mus.clear();

    return numerator/denominator;
}
