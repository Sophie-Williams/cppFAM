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

#include "rule_set.h"
#include "trapezoid.h"

using std::cout;

using namespace fuzzy;

class RocketFAM {
private:
    // Antecedent sets: enemy distance
    const Trapezoid close_;
    const Trapezoid medium_;
    const Trapezoid far_;

    // Antecedent sets: ammo situation
    const Trapezoid ammo_low_;
    const Trapezoid ammo_ok_;
    const Trapezoid ammo_lots_;

    // Consequent sets: rocket desirability score
    const Trapezoid undesirable_;
    const Trapezoid desirable_;
    const Trapezoid very_desirable_;

    // The rules that will tie the logic together
    RuleSet rule_set_;

public:
    double calculate(const double dist, const double ammo_qty) {
        return rule_set_.calculate( std::vector<const double>{dist, ammo_qty} );
    }

    RocketFAM() :
    close_(-150, -25, 25, 150),
    medium_(25, 150, 150, 300),
    far_(150, 300, 500, 650),
    ammo_low_(0, 0, 5, 10),
    ammo_ok_(0, 10, 20, 30),
    ammo_lots_(10, 30, 40, 40),
    undesirable_(0, 0, 20, 50),
    desirable_(30, 50, 70, 90),
    very_desirable_(50, 80, 100, 100),
    rule_set_("Rocket desirability", Implication::MAMDANI)
    {
        // Set up our rules.
        rule_set_.add( Rule{std::vector<Trapezoid>{far_, ammo_lots_}, Conjunction::AND, desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{far_, ammo_ok_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{far_, ammo_low_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{medium_, ammo_lots_}, Conjunction::AND, very_desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{medium_, ammo_ok_}, Conjunction::AND, very_desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{medium_, ammo_low_}, Conjunction::AND, desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{close_, ammo_lots_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{close_, ammo_ok_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{close_, ammo_low_}, Conjunction::AND, undesirable_} );
    }
};

class ShotgunFam {
private:
    // Antecedent sets: enemy distance
    const Trapezoid close_;
    const Trapezoid medium_;
    const Trapezoid far_;

    // Antecedent sets: ammo situation
    const Trapezoid ammo_low_;
    const Trapezoid ammo_ok_;
    const Trapezoid ammo_lots_;

    // Consequent sets: rocket desirability score
    const Trapezoid undesirable_;
    const Trapezoid desirable_;
    const Trapezoid very_desirable_;

    // The rules that will tie the logic together
    RuleSet rule_set_;

public:
    double calculate(const double dist, const double ammo_qty) {
        return rule_set_.calculate( std::vector<const double>{dist, ammo_qty} );
    }

    ShotgunFam() :
    close_(-150, -25, 25, 150),
    medium_(25, 150, 150, 300),
    far_(150, 300, 500, 650),
    ammo_low_(0, 0, 5, 10),
    ammo_ok_(0, 10, 20, 30),
    ammo_lots_(10, 30, 40, 40),
    undesirable_(0, 0, 20, 50),
    desirable_(30, 50, 70, 90),
    very_desirable_(50, 80, 100, 100),
    rule_set_("Shotgun desirability", Implication::MAMDANI)
    {
        // Set up our rules.
        rule_set_.add( Rule{std::vector<Trapezoid>{far_, ammo_lots_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{far_, ammo_ok_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{far_, ammo_low_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{medium_, ammo_lots_}, Conjunction::AND, desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{medium_, ammo_ok_}, Conjunction::AND, desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{medium_, ammo_low_}, Conjunction::AND, undesirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{close_, ammo_lots_}, Conjunction::AND, very_desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{close_, ammo_ok_}, Conjunction::AND, very_desirable_} );
        rule_set_.add( Rule{std::vector<Trapezoid>{close_, ammo_low_}, Conjunction::AND, very_desirable_} );
    }
};

int main()
{
    cout << "Starting...\n";

    // For this demo we set up TWO FAMs, one for each weapon. We supply
    // them both with the inputs of the "current game state" and compare
    // their outputs to pick the more desirable weapon for this state.
    //
    // They are OK to put on the stack, each is just a handful of pointers.
    RocketFAM rocket_brain;
    ShotgunFam gun_brain;

    double dist = 110.0;
    double rkt_ammo = 8;
    double gun_ammo = 12;

    double rocket_desirability = rocket_brain.calculate(dist, rkt_ammo);
    double gun_desirability = gun_brain.calculate(dist, gun_ammo);

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

