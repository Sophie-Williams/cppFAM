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

class RuleTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    fuzzy::Trapezoid ok{60, 65, 65, 70};
    fuzzy::Trapezoid med{40, 50, 50, 60};
    std::vector<fuzzy::Trapezoid> antecedents {ok};

    fuzzy::Trapezoid close{-150, -25, 25, 150};
    fuzzy::Trapezoid ammo_low{-10, 0, 0, 10};
    fuzzy::Trapezoid undesirable{0, 0, 20, 50};
    std::vector<fuzzy::Trapezoid> antecedents2 {close, ammo_low};

    fuzzy::Rule x {antecedents,
                   fuzzy::Conjunction::AND,
                   med,
                   "if room is ok, fan motor is medium"};

    fuzzy::Rule y {antecedents2,
                   fuzzy::Conjunction::AND,
                   undesirable,
                   "if enemy is close AND ammo is low, rocket is undesirable"};

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
    ASSERT_EQ(0, x.fire(std::vector<const double>{55}));
    ASSERT_EQ(0, x.fire(std::vector<const double>{60}));
    ASSERT_EQ(0.5, x.fire(std::vector<const double>{62.5}));
    ASSERT_EQ(1.0, x.fire(std::vector<const double>{65}));
    ASSERT_EQ(0.5, x.fire(std::vector<const double>{67.5}));
    ASSERT_EQ(0, x.fire(std::vector<const double>{70}));
    ASSERT_EQ(0, x.fire(std::vector<const double>{75}));
}

TEST_F(RuleTest, multiple_antecedent_fire_returns_expected_value) {
    ASSERT_EQ(0, y.fire(std::vector<const double>{200, 15}));
    ASSERT_EQ(1, y.fire(std::vector<const double>{0, 0}));

    // Vary the ammo
    ASSERT_EQ(0.9, y.fire(std::vector<const double>{0, 1}));
    ASSERT_EQ(0.5, y.fire(std::vector<const double>{0, 5}));

    // Vary the distance
    ASSERT_EQ(1, y.fire(std::vector<const double>{25, 0}));
    ASSERT_EQ(0.5, y.fire(std::vector<const double>{87.5, 0}));
}