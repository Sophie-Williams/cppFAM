//
//  main.cpp
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

#include <iostream>
#include <vector>
#include <memory>
#include "triangle.h"
#include "trapezoid.h"
#include "rule_set.h"

using std::cout;
using std::unique_ptr;

using namespace fuzzy;

class HvacBrain {
private:
    // Antecedent sets: air temperature
    unique_ptr<FuzzySet> cold;// { unique_ptr<FuzzySet>(new Trapezoid(40, 40, 40, 50)) };
    unique_ptr<FuzzySet> cool;
    unique_ptr<FuzzySet> ok;
    unique_ptr<FuzzySet> warm;
    unique_ptr<FuzzySet> hot;

    // Consequent sets: fan speed
    unique_ptr<FuzzySet> stop;
    unique_ptr<FuzzySet> slow;
    unique_ptr<FuzzySet> med;
    unique_ptr<FuzzySet> fast;
    unique_ptr<FuzzySet> blast;

    // The rules that will tie the logic together
    unique_ptr<RuleSet> rules;

public:
    double calculate(double t) {
        return rules->calculate( vector<double>{t} );
    }

    HvacBrain() {
        // Configure our antecedent sets
        cold = unique_ptr<FuzzySet>(new Trapezoid(40, 40, 40, 50));
        cool = unique_ptr<FuzzySet>(new Triangle(45, 55, 65));
        ok   = unique_ptr<FuzzySet>(new Triangle(60, 65, 70));
        warm = unique_ptr<FuzzySet>(new Triangle(65, 75, 85));
        hot  = unique_ptr<FuzzySet>(new Trapezoid(80, 90, 90, 90));

        // Configure our consequent sets
        stop  = unique_ptr<FuzzySet>(new Triangle(-30, 0, 30));
        slow  = unique_ptr<FuzzySet>(new Triangle(10, 30, 50));
        med   = unique_ptr<FuzzySet>(new Triangle(40, 50, 60));
        fast  = unique_ptr<FuzzySet>(new Triangle(50, 70, 90));
        blast = unique_ptr<FuzzySet>(new Triangle(70, 100, 130));

        // Set up our rules.
        // If you know another object is going to outlive you and you want to observe it, use a (non-owning) raw pointer.
        // http://herbsutter.com/elements-of-modern-c-style/
        rules = unique_ptr<RuleSet>(new RuleSet("HVAC control", "larsen"));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{cold.get()}, "", stop.get(),  "if room is cold, fan motor stops") ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{cool.get()}, "", slow.get(),  "if room is cool, fan motor is slow") ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{ok.get()},   "", med.get(),   "if room is ok, fan motor is medium") ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{warm.get()}, "", fast.get(),  "if room is warm, fan motor speeds up") ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{hot.get()},  "", blast.get(), "if room is hot, fan motor runs full blast") ));
    }

    // Don't allow copying or assignment
    HvacBrain(const HvacBrain &) = delete;
    HvacBrain& operator=(const HvacBrain &) = delete;
};

#define BENCHMARK

int main(int argc, const char * argv[])
{
    cout << "Starting...\n";

    // OK to put on the stack, it's just 11 pointers (to things on the heap)
    HvacBrain system;

#ifdef BENCHMARK
    for (int i=0; i<50000; ++i) {
        for (double t=40; t<=90; ++t) {
            system.calculate(t);
        }
    }
#else
    double result;
    for (double t=40; t<=90; ++t) {
        result=system.calculate( t );

        cout << "The HVAC system determines: for temperature " << t;
        cout << ", the fan speed is ";
        cout << result << " CFM\n";
    }
#endif

    return 0;
}

