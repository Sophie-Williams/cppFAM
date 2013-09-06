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
#include "linguistic_variable.h"
#include "rule_set.h"

using std::cout;
using namespace fuzzy;

int main(int argc, const char * argv[])
{
    cout << "Starting...\n";

    auto target_dist = make_shared<LinguisticVariable>("distance to target");

    auto close  = make_shared<Trapezoid>(-150, -25, 25, 150);
    auto medium = make_shared<Triangle>(25, 150, 300);
    auto far    = make_shared<Trapezoid>(150, 300, 500, 650);

    target_dist->addSet(close);
    target_dist->addSet(medium);
    target_dist->addSet(far);

    auto rocket_ammo_status = make_shared<LinguisticVariable>("rocket launcher ammo quantity");

    auto rkt_low   = make_shared<Triangle>(-10, 0, 10);
    auto rkt_okay  = make_shared<Triangle>(0, 10, 30);
    auto rkt_loads = make_shared<Trapezoid>(10, 30, 40, 40);

    rocket_ammo_status->addSet(rkt_low);
    rocket_ammo_status->addSet(rkt_okay);
    rocket_ammo_status->addSet(rkt_loads);

    auto desirability = make_shared<LinguisticVariable>("weapon desirability");

    auto undesirable    = make_shared<Trapezoid>(0, 0, 20, 50);
    auto desirable      = make_shared<Triangle>(30, 50, 70);
    auto very_desirable = make_shared<Trapezoid>(50, 80, 100, 100);

    desirability->addSet(rkt_low);
    desirability->addSet(rkt_okay);
    desirability->addSet(rkt_loads);

    auto rkt_ruleset = make_shared<RuleSet>("Rocket launcher desirability", "larsen");

    auto r1 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{far, rkt_loads},    "and", desirable,      "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r2 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{far, rkt_okay},     "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r3 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{far, rkt_low},      "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r4 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{medium, rkt_loads}, "and", very_desirable, "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r5 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{medium, rkt_okay},  "and", very_desirable, "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r6 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{medium, rkt_low},   "and", desirable,      "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r7 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{close, rkt_loads},  "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r8 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{close, rkt_okay},   "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto r9 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{close, rkt_low},    "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");

    rkt_ruleset->addRule(r1);
    rkt_ruleset->addRule(r2);
    rkt_ruleset->addRule(r3);
    rkt_ruleset->addRule(r4);
    rkt_ruleset->addRule(r5);
    rkt_ruleset->addRule(r6);
    rkt_ruleset->addRule(r7);
    rkt_ruleset->addRule(r8);
    rkt_ruleset->addRule(r9);

    double dist = 110.0;
    double rkt_ammo = 8.0;

    vector<double>input{dist, rkt_ammo};
    double rocket_desirability = rkt_ruleset->calculate(input);

    cout << "The " << rkt_ruleset->name() << " determines: for " << target_dist->name() << " " << dist;
    cout << " and " << rocket_ammo_status->name() << " " << rkt_ammo;
    cout << ", the " << desirability->name() << " is ";
    cout << rocket_desirability << endl;

    // That was ONE FAM. Now we set up a WHOLE NEW FAM based on the shotgun data.
    // We can re-use the 'desirability' consequent since that's static across all
    // weapons. We just need new antecedents and rules.
    //
    // Now for the second input (or antecedent): the amount of ammo left for this
    // particular weapon.

    auto gun_ammo_status = make_shared<LinguisticVariable>("shotgun ammo quantity");

    auto gun_low   = make_shared<Triangle>(-10, 0, 10);
    auto gun_okay  = make_shared<Triangle>(0, 10, 30);
    auto gun_loads = make_shared<Trapezoid>(10, 30, 40, 40);

    gun_ammo_status->addSet(gun_low);
    gun_ammo_status->addSet(gun_okay);
    gun_ammo_status->addSet(gun_loads);

    auto gun_ruleset = make_shared<RuleSet>("Shotgun desirability", "larsen");

    auto sr1 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{far, gun_loads},    "and", undesirable,      "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr2 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{far, gun_okay},     "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr3 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{far, gun_low},      "and", undesirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr4 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{medium, gun_loads}, "and", desirable, "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr5 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{medium, gun_okay},  "and", desirable, "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr6 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{medium, gun_low},   "and", undesirable,      "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr7 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{close, gun_loads},  "and", very_desirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr8 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{close, gun_okay},   "and", very_desirable,    "if target is   and I have   rocket ammo, rocket launcher is ");
    auto sr9 = make_shared<Rule>(vector<shared_ptr<FuzzySet>>{close, gun_low},    "and", very_desirable,    "if target is   and I have   rocket ammo, rocket launcher is ");

    gun_ruleset->addRule(sr1);
    gun_ruleset->addRule(sr2);
    gun_ruleset->addRule(sr3);
    gun_ruleset->addRule(sr4);
    gun_ruleset->addRule(sr5);
    gun_ruleset->addRule(sr6);
    gun_ruleset->addRule(sr7);
    gun_ruleset->addRule(sr8);
    gun_ruleset->addRule(sr9);

    double gun_ammo = 12;

    vector<double>input2{dist, gun_ammo};
    double gun_desirability = gun_ruleset->calculate(input);

    cout << "The " << gun_ruleset->name() << " determines: for " << target_dist->name() << " " << dist;
    cout << " and " << gun_ammo_status->name() << " " << gun_ammo;
    cout << ", the " << desirability->name() << " is ";
    cout << gun_desirability << endl;

    if (gun_desirability > rocket_desirability)
        cout << "I choose the shotgun" << endl;
    else
        cout << "I choose the rocket launcher" << endl;

    return 0;
}

