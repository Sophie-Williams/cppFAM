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
#include "trapezoid.h"
#include "triangle.h"
#include "rule_set.h"

using std::cout;
using std::unique_ptr;

using namespace fuzzy;

class RocketFAM {
private:
    // Antecedent sets: enemy distance
    unique_ptr<FuzzySet> close;
    unique_ptr<FuzzySet> medium;
    unique_ptr<FuzzySet> far;

    // Antecedent sets: ammo situation
    unique_ptr<FuzzySet> ammo_low;
    unique_ptr<FuzzySet> ammo_ok;
    unique_ptr<FuzzySet> ammo_lots;

    // Consequent sets: rocket desirability score
    unique_ptr<FuzzySet> undesirable;
    unique_ptr<FuzzySet> desirable;
    unique_ptr<FuzzySet> very_desirable;

    // The rules that will tie the logic together
    unique_ptr<RuleSet> rules;

public:
    double calculate(double dist, double ammo_qty) {
        return rules->calculate( vector<double>{dist, ammo_qty} );
    }

    RocketFAM() {
        // Configure our antecedent sets
        close  = unique_ptr<FuzzySet>(new Trapezoid(-150, -25, 25, 150));
        medium = unique_ptr<FuzzySet>(new Triangle(25, 150, 300));
        far    = unique_ptr<FuzzySet>(new Trapezoid(150, 300, 500, 650));

        ammo_low  = unique_ptr<FuzzySet>(new Triangle(-10, 0, 10));
        ammo_ok   = unique_ptr<FuzzySet>(new Triangle(0, 10, 30));
        ammo_lots = unique_ptr<FuzzySet>(new Trapezoid(10, 30, 40, 40));

        // Configure our consequent sets
        undesirable    = unique_ptr<FuzzySet>(new Trapezoid(0, 0, 20, 50));
        desirable      = unique_ptr<FuzzySet>(new Triangle(30, 50, 70));
        very_desirable = unique_ptr<FuzzySet>(new Trapezoid(50, 80, 100, 100));

        // Set up our rules.
        // If you know another object is going to outlive you and you want to observe it, use a (non-owning) raw pointer.
        // http://herbsutter.com/elements-of-modern-c-style/
        rules = unique_ptr<RuleSet>(new RuleSet("Rocket desirability", "mamdani"));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{far.get(), ammo_lots.get()},    "and", desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{far.get(), ammo_ok.get()},      "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{far.get(), ammo_low.get()},     "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{medium.get(), ammo_lots.get()}, "and", very_desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{medium.get(), ammo_ok.get()},   "and", very_desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{medium.get(), ammo_low.get()},  "and", desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{close.get(), ammo_lots.get()},  "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{close.get(), ammo_ok.get()},    "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{close.get(), ammo_low.get()},   "and", undesirable.get() ) ));
    }

    // Don't allow copying or assignment
    RocketFAM(const RocketFAM &) = delete;
    RocketFAM& operator=(const RocketFAM &) = delete;
};

class ShotgunFam {
private:
    // Antecedent sets: enemy distance
    unique_ptr<FuzzySet> close;
    unique_ptr<FuzzySet> medium;
    unique_ptr<FuzzySet> far;

    // Antecedent sets: ammo situation
    unique_ptr<FuzzySet> ammo_low;
    unique_ptr<FuzzySet> ammo_ok;
    unique_ptr<FuzzySet> ammo_lots;

    // Consequent sets: rocket desirability score
    unique_ptr<FuzzySet> undesirable;
    unique_ptr<FuzzySet> desirable;
    unique_ptr<FuzzySet> very_desirable;

    // The rules that will tie the logic together
    unique_ptr<RuleSet> rules;

public:
    double calculate(double dist, double ammo_qty) {
        return rules->calculate( vector<double>{dist, ammo_qty} );
    }

    ShotgunFam() {
        // Configure our antecedent sets
        close  = unique_ptr<FuzzySet>(new Trapezoid(-150, -25, 25, 150));
        medium = unique_ptr<FuzzySet>(new Triangle(25, 150, 300));
        far    = unique_ptr<FuzzySet>(new Trapezoid(150, 300, 500, 650));

        ammo_low  = unique_ptr<FuzzySet>(new Triangle(-10, 0, 10));
        ammo_ok   = unique_ptr<FuzzySet>(new Triangle(0, 10, 30));
        ammo_lots = unique_ptr<FuzzySet>(new Trapezoid(10, 30, 40, 40));

        // Configure our consequent sets
        undesirable    = unique_ptr<FuzzySet>(new Trapezoid(0, 0, 20, 50));
        desirable      = unique_ptr<FuzzySet>(new Triangle(30, 50, 70));
        very_desirable = unique_ptr<FuzzySet>(new Trapezoid(50, 80, 100, 100));

        // Set up our rules.
        // If you know another object is going to outlive you and you want to observe it, use a (non-owning) raw pointer.
        // http://herbsutter.com/elements-of-modern-c-style/
        rules = unique_ptr<RuleSet>(new RuleSet("Shotgun desirability", "mamdani"));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{far.get(), ammo_lots.get()},    "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{far.get(), ammo_ok.get()},      "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{far.get(), ammo_low.get()},     "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{medium.get(), ammo_lots.get()}, "and", desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{medium.get(), ammo_ok.get()},   "and", desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{medium.get(), ammo_low.get()},  "and", undesirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{close.get(), ammo_lots.get()},  "and", very_desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{close.get(), ammo_ok.get()},    "and", very_desirable.get() ) ));
        rules->add(unique_ptr<Rule>(new Rule(vector<FuzzySet*>{close.get(), ammo_low.get()},   "and", very_desirable.get() ) ));
    }

    // Don't allow copying or assignment
    ShotgunFam(const ShotgunFam &) = delete;
    ShotgunFam& operator=(const ShotgunFam &) = delete;
};

int main()
{
    cout << "Starting...\n";

    // For this demo we set up TWO FAMs, one for each weapon. We supply
    // them both with the inputs of the "current game state" and compare
    // their outputs to pick the more desirable weapon for this state.
    //
    // They are OK to put on the stack, each is just a handful of pointers.
    RocketFAM rocket_system;
    ShotgunFam gun_system;

    double dist = 110.0;
    double rkt_ammo = 8;
    double gun_ammo = 12;

    double rocket_desirability = rocket_system.calculate(dist, rkt_ammo);
    double gun_desirability = gun_system.calculate(dist, gun_ammo);

    cout << "The rocket FAM determines: for distance " << dist;
    cout << " and ammo qty " << rkt_ammo;
    cout << ", the desirability is ";
    cout << rocket_desirability << std::endl;

    cout << "The shotgun FAM determines: for distance " << dist;
    cout << " and ammo qty " << gun_ammo;
    cout << ", the desirability is ";
    cout << gun_desirability << std::endl;

    if (gun_desirability > rocket_desirability)
        cout << "I choose the shotgun" << std::endl;
    else
        cout << "I choose the rocket launcher" << std::endl;

    return 0;
}

