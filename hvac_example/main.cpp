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
#include "linguistic_variable.h"
#include "triangle.h"
#include "trapezoid.h"
#include "rule_set.h"

using std::cout;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

using namespace fuzzy;

int main(int argc, const char * argv[])
{
    cout << "Starting...\n";

    auto temperature_in = make_shared<LinguisticVariable>("room temperature");

//    Trapezoid cold {40, 40, 40, 50};
//    Triangle  cool {45, 55, 65};
//    Triangle  ok   {60, 65, 70};
//    Triangle  warm {65, 75, 85};
//    Trapezoid hot  {80, 90, 90, 90};

//    auto cold = make_shared<Trapezoid>(40, 40, 40, 50);
//    auto cool = make_shared<Triangle>(45, 55, 65);
//    auto ok   = make_shared<Triangle>(60, 65, 70);
//    auto warm = make_shared<Triangle>(65, 75, 85);
//    auto hot  = make_shared<Trapezoid>(80, 90, 90, 90);

    unique_ptr<FuzzySet> cold( new Trapezoid(40,40,40,50));
    unique_ptr<FuzzySet> cool( new Triangle(45, 55, 65));
    unique_ptr<FuzzySet> ok( new Triangle(60, 65, 70));
    unique_ptr<FuzzySet> warm( new Triangle(65, 75, 85));
    unique_ptr<FuzzySet> hot( new Trapezoid(80, 90, 90, 90));

    temperature_in->addSet(std::move(cold));
    temperature_in->addSet(std::move(cool));
    temperature_in->addSet(std::move(ok));
    temperature_in->addSet(std::move(warm));
    temperature_in->addSet(std::move(hot));


    auto fan_speed = make_shared<LinguisticVariable>("fan speed");

    unique_ptr<FuzzySet> stop(new Triangle(-30, 0, 30));
    unique_ptr<FuzzySet> slow(new Triangle(10, 30, 50));
    unique_ptr<FuzzySet> med(new Triangle(40, 50, 60));
    unique_ptr<FuzzySet> fast(new Triangle(50, 70, 90));
    unique_ptr<FuzzySet> blast(new Triangle(70, 100, 130));

//    auto stop  = make_shared<Triangle>(-30, 0, 30);
//    auto slow  = make_shared<Triangle>(10, 30, 50);
//    auto med   = make_shared<Triangle>(40, 50, 60);
//    auto fast  = make_shared<Triangle>(50, 70, 90);
//    auto blast = make_shared<Triangle>(70, 100, 130);

    fan_speed->addSet(std::move(stop));
    fan_speed->addSet(std::move(slow));
    fan_speed->addSet(std::move(med));
    fan_speed->addSet(std::move(fast));
    fan_speed->addSet(std::move(blast));

    auto system = make_shared<RuleSet>("HVAC control", "larsen");

    auto r1 = make_shared<Rule>(vector<FuzzySet*>{cold.get()}, "", stop.get(),  "if room is cold, fan motor stops");
    auto r2 = make_shared<Rule>(vector<FuzzySet*>{cool.get()}, "", slow.get(),  "if room is cool, fan motor is slow");
    auto r3 = make_shared<Rule>(vector<FuzzySet*>{ok.get()},   "", med.get(),   "if room is ok, fan motor is medium");
    auto r4 = make_shared<Rule>(vector<FuzzySet*>{warm.get()}, "", fast.get(),  "if room is warm, fan motor speeds up");
    auto r5 = make_shared<Rule>(vector<FuzzySet*>{hot.get()},  "", blast.get(), "if room is hot, fan motor runs full blast");
//
//    system->addRule(r1);
//    system->addRule(r2);
//    system->addRule(r3);
//    system->addRule(r4);
//    system->addRule(r5);
//
//    //double result;
//    for (int i=0; i<50000; ++i) {
//        for (double t=40; t<=90; ++t) {
//            system->calculate( vector<double>{t} );
//
//            //        cout << "The " << system->name() << " determines: for " << temperature_in->name();
//            //        cout << " " << t << ", the " << fan_speed->name() << " is ";
//            //        cout << result << " CFM\n";
//        }
//    }

    return 0;
}

