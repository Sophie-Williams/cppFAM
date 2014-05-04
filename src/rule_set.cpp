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

fuzzy::RuleSet::RuleSet() :
_name(""),
_implication(Implication::LARSEN)
{
    //nop
}

fuzzy::RuleSet::RuleSet(string name, Implication implication) :
_name(name),
_implication(implication)
{
    //nop
}


double fuzzy::RuleSet::calculate(vector<double> inputValues) {
    // Fire each rule to determine the µ value (degree of fit).
    for (const auto& rule : _rules) {
        double mu = rule.fire(inputValues);

        // Since any given consequent may have been activated more than once, we
        // need to get just a single µ value out -- we only care about the 'best'
        // µ. A popular way of doing so is to OR the values together, i.e. keep the
        // maximum µ value and discard the others.
        //
        // Put another way, keep only the highest µ for any given consequent.
        auto iter = _consequent_mus.find(rule.consequent());
        if (iter == end(_consequent_mus)) {
            // Didn't find
            _consequent_mus.insert(pair<FuzzySet*, double>(rule.consequent(), mu));
        } else if (mu > iter->second) {
            // Did find, and latest µ is better than previous µ
            iter->second = mu; // keep the max mu
        }
    }

    // Using each µ value, alter the consequent fuzzy set's polgyon. This is
    // called implication, and 'weights' the consequents properly. There are
    // several common ways of doing it, such as Larsen (scaling) and Mamdani
    // (clipping).
    //
    // Then defuzzify into a discrete & usable value by adding up the weighted
    // consequents' contributions to the output. Again there are several ways
    // of doing it, such as computing the centroid of the combined 'mass', or
    // the 'mean of maximum' of the tallest set(s). Here we use the "Average
    // of Maxima" summation mechanism. MaxAv is defined as:
    // (∑ representative value * height) / (∑ height) for all output sets
    // where 'representative value' is shape-dependent.
    double numerator=0;
    double denominator=0;

    // This isn't DRY but it's fastest this way.
    if (_implication == Implication::MAMDANI) {
        for ( const auto& item : _consequent_mus) {
            unique_ptr<FuzzySet> tmp = (item.first)->mamdami(item.second);
            numerator += (tmp->calculateXCentroid() * tmp->height());
            denominator += tmp->height();
        }
    } else {
        for ( const auto& item : _consequent_mus) {
            unique_ptr<FuzzySet> tmp((item.first)->larsen(item.second));
            numerator += (tmp->calculateXCentroid() * tmp->height());
            denominator += tmp->height();
        }
    }

    _consequent_mus.clear();

    return numerator/denominator;
}
