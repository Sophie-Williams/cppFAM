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

using std::unordered_map;
using std::vector;
using std::pair;
using std::string;

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

fuzzy::RuleSet::RuleSet(const RuleSet& other) :
_name(other._name),
_implication(other._implication),
_rules(other._rules),
_consequent_mus(other._consequent_mus),
_mmi(other._mmi)
{
    //nop
}

fuzzy::RuleSet& fuzzy::RuleSet::operator=(const fuzzy::RuleSet &rhs) {
    if (this == &rhs) return *this;

    _name = rhs._name;
    _implication = rhs._implication;
    _rules = rhs._rules;
    _consequent_mus = rhs._consequent_mus;
    _mmi = rhs._mmi;
    return *this;
}

string fuzzy::RuleSet::name() {
    return _name;
}

void fuzzy::RuleSet::addRule(std::shared_ptr<Rule> const r) {
    _rules.push_back(r);
}

double fuzzy::RuleSet::calculate(vector<double> inputValues) {
    double mu;
    std::shared_ptr<FuzzySet>con;

    // Fire each rule to determine the µ value (degree of fit).
    for (auto rule : _rules) {
        mu = rule->fire(inputValues);
        con = rule->getConsequent();

        // Since any given consequent may have been activated more than once, we
        // need to get just a single µ value out -- we only care about the 'best'
        // µ. A popular way of doing so is to OR the values together, i.e. keep the
        // maximum µ value and discard the others.
        _mmi = _consequent_mus.find(con);
        if (_mmi != _consequent_mus.end() && mu > _mmi->second) {
            _mmi->second = mu; // keep the max mu
        } else {
            // Didn't find
            _consequent_mus.insert(pair<std::shared_ptr<FuzzySet>, double>(con, mu));
        }
    }

    // Using each µ value, alter the consequent fuzzy set's polgyon. This is
    // called implication, and 'weights' the consequents properly. There are
    // several common ways of doing it, such as Larsen (scaling) and Mamdani
    // (clipping).
    double numerator=0;
    double denominator=0;

    std::shared_ptr<FuzzySet> tmp;
    for ( auto item : _consequent_mus) {
        if (_implication == "mamdani") {
            tmp = (item.first)->mamdami(item.second);
        } else {
            tmp = (item.first)->larsen(item.second);
        }

        // Defuzzify into a discrete & usable value by adding up the weighted
        // consequents' contributions to the output. Again there are several ways
        // of doing it, such as computing the centroid of the combined 'mass', or
        // the 'mean of maximum' of the tallest set(s). Here we use the "Average
        // of Maxima" summation mechanism. MaxAv is defined as:
        // (∑ representative value * height) / (∑ height) for all output sets
        // where 'representative value' is shape-dependent.
        numerator += (tmp->calculateXCentroid() * tmp->getHeight());
        denominator += tmp->getHeight();
    }

    _consequent_mus.clear();

    return numerator/denominator;
}