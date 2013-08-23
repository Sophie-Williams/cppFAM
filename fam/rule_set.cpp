//
//  rule_set.cpp
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#include "rule_set.h"

using std::unordered_map;
using std::vector;

RuleSet::RuleSet() :
_name {""},
_implication {""}
{
}

RuleSet::RuleSet(std::string name, std::string implication) :
_name {name},
_implication {implication}
{
}

std::string RuleSet::name() {
    return _name;
}

void RuleSet::addRule(Rule * const r) {
    _rules.push_back(r);
}

double RuleSet::calculate(vector<double> inputValues) {
//    std::cout << "\nFiring all rules..." << std::endl;

    unordered_map<FuzzySet *, double> consequent_mus;
    unordered_map<FuzzySet *, double>::iterator p;

    vector<FuzzySet *> consequents;

    double mu;
    FuzzySet *con;

    for (Rule *rule : _rules) {
        // Fire each rule to determine the µ value (degree of fit).
        // Gather the µ vals by consequent, since each consequent may in fact
        // have been fired more than once and we'll need that knowledge in a
        // moment...
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
            consequent_mus.insert(std::pair<FuzzySet*, double>(con, mu));
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

    //    Defuzzify into a discrete & usable value by adding up the weighted
    //    consequents' contributions to the output. Again there are several ways
    //    of doing it, such as computing the centroid of the combined 'mass', or
    //    the 'mean of maximum' of the tallest set(s). Here we use the "Average
    //    of Maxima" summation mechanism. MaxAv is defined as:
    //    (∑ representative value * height) / (∑ height) for all output sets
    //    where 'representative value' is shape-dependent.
    double numerator=0;
    double denominator=0;

    for (auto cons : consequents) {
//        std::cout << *cons << std::endl;
        numerator += (cons->calculateXCentroid() * cons->getHeight());
        denominator += cons->getHeight();
    }

    return numerator/denominator;
}