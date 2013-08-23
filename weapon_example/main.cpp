//
//  main.cpp
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#include <iostream>
#include <vector>
#include "trapezoid.h"
#include "triangle.h"
#include "linguistic_variable.h"
#include "rule_set.h"

using std::cout;

int main(int argc, const char * argv[])
{
    cout << "Starting...\n";

    LinguisticVariable *temperature_in = new LinguisticVariable("room temperature");

    FuzzySet *cold = new Trapezoid(40, 40, 40, 50);
    FuzzySet *cool = new Triangle(45, 55, 65);
    FuzzySet *ok   = new Triangle(60, 65, 70);
    FuzzySet *warm = new Triangle(65, 75, 85);
    FuzzySet *hot  = new Trapezoid(80, 90, 90, 90);

    temperature_in->addSet(cold);
    temperature_in->addSet(cool);
    temperature_in->addSet(ok);
    temperature_in->addSet(warm);
    temperature_in->addSet(hot);

    LinguisticVariable *fan_speed = new LinguisticVariable("fan speed");

    FuzzySet *stop  = new Triangle(-30, 0, 30);
    FuzzySet *slow  = new Triangle(10, 30, 50);
    FuzzySet *med   = new Triangle(40, 50, 60);
    FuzzySet *fast  = new Triangle(50, 70, 90);
    FuzzySet *blast = new Triangle(70, 100, 130);

    fan_speed->addSet(stop);
    fan_speed->addSet(slow);
    fan_speed->addSet(med);
    fan_speed->addSet(fast);
    fan_speed->addSet(blast);

    RuleSet *system = new RuleSet("HVAC control", "larsen");

    Rule *r1 = new Rule(vector<FuzzySet*>{cold}, "", stop,  "if room is cold, fan motor stops");
    Rule *r2 = new Rule(vector<FuzzySet*>{cool}, "", slow,  "if room is cool, fan motor is slow");
    Rule *r3 = new Rule(vector<FuzzySet*>{ok},   "", med,   "if room is ok, fan motor is medium");
    Rule *r4 = new Rule(vector<FuzzySet*>{warm}, "", fast,  "if room is warm, fan motor speeds up");
    Rule *r5 = new Rule(vector<FuzzySet*>{hot},  "", blast, "if room is hot, fan motor runs full blast");

    system->addRule(r1);
    system->addRule(r2);
    system->addRule(r3);
    system->addRule(r4);
    system->addRule(r5);

    double result;
    for (double t=40; t<=90; ++t) {
        vector<double>input{t};
        result = system->calculate(input);

        cout << "The " << system->name() << " determines: for " << temperature_in->name();
        cout << " " << t << ", the " << fan_speed->name() << " is ";
        cout << result << " CFM\n";
    }
    return 0;
}

