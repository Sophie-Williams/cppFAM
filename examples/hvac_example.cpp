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

/**
 Handy shortcut for making unique ptrs.
 http://herbsutter.com/gotw/_102/
 */
template<typename T, typename ... Args>
std::unique_ptr<T> make_unique( Args&& ... args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

class HvacBrain {
private:
    // Antecedent sets: air temperature
    unique_ptr<FuzzySet> cold;
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
    RuleSet rules;

public:
    double calculate(double t) {
        return rules.calculate( std::vector<double>{t} );
    }

    HvacBrain() {
        // Configure our antecedent sets
        cold = make_unique<Trapezoid>(40, 40, 40, 50);
        cool = make_unique<Triangle>(45, 55, 65);
        ok   = make_unique<Triangle>(60, 65, 70);
        warm = make_unique<Triangle>(65, 75, 85);
        hot  = make_unique<Trapezoid>(80, 90, 90, 90);

        // Configure our consequent sets
        stop  = make_unique<Triangle>(-30, 0, 30);
        slow  = make_unique<Triangle>(10, 30, 50);
        med   = make_unique<Triangle>(40, 50, 60);
        fast  = make_unique<Triangle>(50, 70, 90);
        blast = make_unique<Triangle>(70, 100, 130);

        // Set up our rules.
        // If you know another object is going to outlive you and you want to observe it, use a (non-owning) raw pointer.
        // http://herbsutter.com/elements-of-modern-c-style/
        RuleSet rules("HVAC control", Implication::MAMDANI);
        rules.add( Rule(std::vector<FuzzySet*>{cold.get()}, Conjunction::INTERSECTION, stop.get(),  "if room is cold, fan motor stops") );
        rules.add( Rule(std::vector<FuzzySet*>{cool.get()}, Conjunction::INTERSECTION, slow.get(),  "if room is cool, fan motor is slow") );
        rules.add( Rule(std::vector<FuzzySet*>{ok.get()},   Conjunction::INTERSECTION, med.get(),   "if room is ok, fan motor is medium") );
        rules.add( Rule(std::vector<FuzzySet*>{warm.get()}, Conjunction::INTERSECTION, fast.get(),  "if room is warm, fan motor speeds up") );
        rules.add( Rule(std::vector<FuzzySet*>{hot.get()},  Conjunction::INTERSECTION, blast.get(), "if room is hot, fan motor runs full blast") );
    }

    // Don't allow copying or assignment
    HvacBrain(const HvacBrain &) = delete;
    HvacBrain& operator=(const HvacBrain &) = delete;
};

int main() {
    cout << "Starting...\n";

    // OK to put on the stack, it's just 11 pointers
    HvacBrain brain;

#ifdef BENCHMARK
    for (int i=0; i<50000; ++i) {
        for (double t=40; t<=90; ++t) {
            brain.calculate(t);
        }
    }
#else
    for (double t=40; t<=90; ++t) {
        double result=brain.calculate( t );

        cout << "The HVAC system determines: for temperature " << t;
        cout << ", the fan speed is ";
        cout << result << " CFM\n";
    }
#endif

    return 0;
}

