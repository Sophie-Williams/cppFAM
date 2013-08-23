//
//  rule_set.cpp
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//
//  This file is part of The C++ Fuzzy Associative Memory
//  http://github.com/cpowell/fuzzy-associative-memory-c++
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the library.
//

#include "rule_set.h"

using std::unordered_map;
using std::vector;
using std::pair;
using std::string;

RuleSet::RuleSet() :
_name {""},
_implication {""}
{
}

RuleSet::RuleSet(string name, string implication) :
_name {name},
_implication {implication}
{
}

string RuleSet::name() {
    return _name;
}

void RuleSet::addRule(Rule * const r) {
    _rules.push_back(r);
}

double RuleSet::calculate(vector<double> inputValues) {
//    std::cout << "\nFiring all rules..." << std::endl;

    typedef unordered_map<FuzzySet *, double> mu_map;
    mu_map consequent_mus;
    mu_map::iterator p;

    vector<FuzzySet *> consequents;

    double mu;
    FuzzySet *con;

    // Fire each rule to determine the µ value (degree of fit).
    for (Rule *rule : _rules) {
        mu = rule->fire(inputValues);
        con = rule->getConsequent();

        // Since any given consequent may have been activated more than once, we
        // need to get just a single µ value out -- we only care about the 'best'
        // µ. A popular way of doing so is to OR the values together, i.e. keep the
        // maximum µ value and discard the others.
        p = consequent_mus.find(con);
        if (p != consequent_mus.end()) {
            // Found it
            if (mu > p->second)
                p->second = mu; // keep the max mu
        } else {
            // Didn't find
            consequent_mus.insert(pair<FuzzySet*, double>(con, mu));
        }
    }

    // Using each µ value, alter the consequent fuzzy set's polgyon. This is
    // called implication, and 'weights' the consequents properly. There are
    // several common ways of doing it, such as Larsen (scaling) and Mamdani
    // (clipping).
    for ( auto item : consequent_mus) {
        if (_implication == "mamdani") {
            consequents.push_back( (item.first)->mamdami(item.second) );
        } else {
            consequents.push_back( (item.first)->larsen(item.second) );
        }
    }

    // Defuzzify into a discrete & usable value by adding up the weighted
    // consequents' contributions to the output. Again there are several ways
    // of doing it, such as computing the centroid of the combined 'mass', or
    // the 'mean of maximum' of the tallest set(s). Here we use the "Average
    // of Maxima" summation mechanism. MaxAv is defined as:
    // (∑ representative value * height) / (∑ height) for all output sets
    // where 'representative value' is shape-dependent.
    double numerator=0;
    double denominator=0;

    for (auto cons : consequents) {
        numerator += (cons->calculateXCentroid() * cons->getHeight());
        denominator += cons->getHeight();
    }

    return numerator/denominator;
}