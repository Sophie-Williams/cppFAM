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
    Trapezoid cold_;
    Trapezoid cool_;
    Trapezoid ok_;
    Trapezoid warm_;
    Trapezoid hot_;

    // Consequent sets: fan speed
    Trapezoid stop_;
    Trapezoid slow_;
    Trapezoid med_;
    Trapezoid fast_;
    Trapezoid blast_;

    // The rules that will tie the logic together
    RuleSet rule_set_;


public:
    double calculate(double t) {
        return rule_set_.calculate( std::vector<const double>{t} );
    }

    HvacBrain() :
    rule_set_("HVAC control", Implication::MAMDANI)
    {
        // Configure our antecedent sets
        cold_ = Trapezoid(40, 40, 40, 50);
        cool_ = Trapezoid(45, 55, 55, 65);
        ok_   = Trapezoid(60, 65, 65, 70);
        warm_ = Trapezoid(65, 75, 75, 85);
        hot_  = Trapezoid(80, 90, 90, 90);

        // Configure our consequent sets
        stop_  = Trapezoid(-30, 0,  0, 30);
        slow_  = Trapezoid(10, 30, 30, 50);
        med_   = Trapezoid(40, 50, 50, 60);
        fast_  = Trapezoid(50, 70, 70, 90);
        blast_ = Trapezoid(70, 100, 100, 130);

        // Set up our rules.
        // HvacBrain will outlive the RuleSet, so it's OK to pass a non-owning raw pointer to RuleSet.
        // http://herbsutter.com/elements-of-modern-c-style/
        rule_set_.add( Rule{std::vector<Trapezoid>{cold_}, Conjunction::AND, stop_,  "if room is cold, fan motor stops"} );
        rule_set_.add( Rule{std::vector<Trapezoid>{cool_}, Conjunction::AND, slow_,  "if room is cool, fan motor is slow"} );
        rule_set_.add( Rule{std::vector<Trapezoid>{ok_},   Conjunction::AND, med_,   "if room is ok, fan motor is medium"} );
        rule_set_.add( Rule{std::vector<Trapezoid>{warm_}, Conjunction::AND, fast_,  "if room is warm, fan motor speeds up"} );
        rule_set_.add( Rule{std::vector<Trapezoid>{hot_},  Conjunction::AND, blast_, "if room is hot, fan motor runs full blast"} );
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

