//
//  RuleTest.cpp
//  cecf
//
//  Created by Chris Powell on 5/4/14.
//  Copyright (c) 2014 Prylis Inc. All rights reserved.
//

#include "gtest/gtest.h"

#include "rule.h"
#include "trapezoid.h"

#include <vector>

using namespace fuzzy;
class RuleTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    fuzzy::Trapezoid ok {60, 65, 65, 70};
    fuzzy::Trapezoid med {40, 50, 50, 60};
    std::vector<fuzzy::Trapezoid> antecedents { std::vector <fuzzy::Trapezoid> {ok} }; // This weird init is a VS2013 issue. See https://stackoverflow.com/questions/21573143/how-to-initialise-a-vector-member-variable-in-the-class-definition-c11

    fuzzy::Trapezoid close { -150, -25, 25, 150};
    fuzzy::Trapezoid ammo_low { -10, 0, 0, 10};
    fuzzy::Trapezoid undesirable {0, 0, 20, 50};
    std::vector<fuzzy::Trapezoid> antecedents2 { std::vector<fuzzy::Trapezoid> { close, ammo_low } }; // This weird init is a VS2013 issue. See https://stackoverflow.com/questions/21573143/how-to-initialise-a-vector-member-variable-in-the-class-definition-c11

    fuzzy::Rule x {antecedents,
                   fuzzy::Conjunction::AND,
                   med,
                   "if room is ok, fan motor is medium"
                  };

    fuzzy::Rule y {antecedents2,
                   fuzzy::Conjunction::AND,
                   undesirable,
                   "if enemy is close AND ammo is low, rocket is undesirable"
                  };

    // You can remove any or all of the following functions if its body is empty.

    RuleTest() {
        // You can do set-up work for each test here.
    }

    virtual ~RuleTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(RuleTest, single_antecedent_fire_returns_expected_value) {
    ASSERT_EQ(0, x.fire(std::vector<double> {55}));
    ASSERT_EQ(0, x.fire(std::vector<double> {60}));
    ASSERT_EQ(0.5, x.fire(std::vector<double> {62.5}));
    ASSERT_EQ(1.0, x.fire(std::vector<double> {65}));
    ASSERT_EQ(0.5, x.fire(std::vector<double> {67.5}));
    ASSERT_EQ(0, x.fire(std::vector<double> {70}));
    ASSERT_EQ(0, x.fire(std::vector<double> {75}));
}

TEST_F(RuleTest, multiple_antecedent_fire_returns_expected_value) {
    ASSERT_EQ(0, y.fire(std::vector<double> {200, 15}));
    ASSERT_EQ(1, y.fire(std::vector<double> {0, 0}));

    // Vary the ammo
    ASSERT_EQ(0.9, y.fire(std::vector<double> {0, 1}));
    ASSERT_EQ(0.5, y.fire(std::vector<double> {0, 5}));

    // Vary the distance
    ASSERT_EQ(1, y.fire(std::vector<double> {25, 0}));
    ASSERT_EQ(0.5, y.fire(std::vector<double> {87.5, 0}));
}

TEST_F(RuleTest, rule_outputs_match_PGAIBE_book_values) {    // Page 431...
    Trapezoid close {0, 0, 25, 150};
    Trapezoid medium {25, 150, 150, 300};
    Trapezoid far {150, 300, 400, 400};

    Trapezoid ammo_low {0, 0, 0, 10};
    Trapezoid ammo_ok {0, 10, 10, 30};
    Trapezoid ammo_lots {10, 30, 50, 50};

    Trapezoid undes {0, 0, 25, 50};
    Trapezoid des {25, 50, 50, 75};
    Trapezoid vdes {50, 75, 100, 100};

    Rule r1 {std::vector<Trapezoid>{far, ammo_lots}, Conjunction::AND, des, "far + lots is desirable"};
    Rule r2 {std::vector<Trapezoid>{far, ammo_ok}, Conjunction::AND, undes, "far + some is undesirable"};
    Rule r3 {std::vector<Trapezoid>{far, ammo_low}, Conjunction::AND, undes, "far + low is undesirable"};
    Rule r4 {std::vector<Trapezoid>{medium, ammo_lots}, Conjunction::AND, vdes, "med + lots is very des"};
    Rule r5 {std::vector<Trapezoid>{medium, ammo_ok}, Conjunction::AND, vdes, "med + some is very des"};
    Rule r6 {std::vector<Trapezoid>{medium, ammo_low}, Conjunction::AND, des, "med + low is desirable"};
    Rule r7 {std::vector<Trapezoid>{close, ammo_lots}, Conjunction::AND, undes, "close + lots is undes"};
    Rule r8 {std::vector<Trapezoid>{close, ammo_ok}, Conjunction::AND, undes, "close + some is undes"};
    Rule r9 {std::vector<Trapezoid>{close, ammo_low}, Conjunction::AND, undes, "close + low is undes"};

    std::vector<double>vals {200, 8};

    ASSERT_NEAR(0, r1.fire(vals), 0.001);
    ASSERT_NEAR(0.3333, r2.fire(vals), 0.001);
    ASSERT_NEAR(0.2, r3.fire(vals), 0.001);
    ASSERT_NEAR(0, r4.fire(vals), 0.001);
    ASSERT_NEAR(0.6666, r5.fire(vals), 0.001);
    ASSERT_NEAR(0.2, r6.fire(vals), 0.001);
    ASSERT_NEAR(0, r7.fire(vals), 0.001);
    ASSERT_NEAR(0, r8.fire(vals), 0.001);
    ASSERT_NEAR(0, r9.fire(vals), 0.001);
}