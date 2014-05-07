//
//  RuleSetTest.cpp
//  cecf
//
//  Created by Chris Powell on 5/7/14.
//  Copyright (c) 2014 Prylis Inc. All rights reserved.
//

#include "gtest/gtest.h"

#define private public
#include "rule_set.h"

#include <vector>

using namespace fuzzy;

class RuleSetTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body is empty.
    Trapezoid cold_{40, 40, 40, 50};
    Trapezoid stop_{-30, 0,  0, 30};

    Trapezoid highly_desirable_{0,0,15,25};
    Trapezoid quite_desirable_{10,30,30,50};
    Trapezoid somewhat_desirable_{30,50,50,70};
    Trapezoid mostly_undesirable_{50,70,70,90};
    Trapezoid undesirable_{75,85,100,100};

    Trapezoid no_targets_{0,0,0,1};
    Trapezoid one_target_{0,1,1,2};
    Trapezoid many_targets_{1,2,10,10};

    Trapezoid close_{0,0,250,500};
    Trapezoid medium_{250,500,1000,2000};
    Trapezoid far_{1000,2000, 20000, 20000};

    RuleSet acquisition_{"Acquisition mode desirability", Implication::LARSEN};
    RuleSet interception_{"Interception mode desirability", Implication::LARSEN};
    RuleSet quarry_{"Quarry overall desirability", Implication::LARSEN};

    RuleSetTest() {
        // You can do set-up work for each test here.
    }

    virtual ~RuleSetTest() {
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

TEST_F(RuleSetTest, ruleset_with_no_rules_returns_zero) {
    RuleSet rs;
    ASSERT_EQ(0, rs.calculate(0));
    ASSERT_EQ(0, rs.calculate(0.2));
    ASSERT_EQ(0, rs.calculate(-1));
    ASSERT_EQ(0, rs.calculate(3));
    ASSERT_EQ(0, rs.calculate(35));
    ASSERT_EQ(0, rs.calculate(-3132));
}

TEST_F(RuleSetTest, simple_mu_map_population_works_1) {
    RuleSet rs;
    rs.add( Rule{std::vector<Trapezoid>{cold_}, Conjunction::AND, stop_,  "if room is cold, fan motor stops"} );
    rs.populate_mu_map(std::vector<const double>{40.0});
    ASSERT_EQ(1, rs._consequents_to_mus.size());

    auto iter = rs._consequents_to_mus.find(stop_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);

    iter = rs._consequents_to_mus.find(stop_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);
}

TEST_F(RuleSetTest, simple_mu_map_population_works_2) {
    RuleSet rs; // "acquisition mode desirability"
    rs.add( Rule{ std::vector<Trapezoid>{no_targets_},   Conjunction::AND, highly_desirable_ } );
    rs.add( Rule{ std::vector<Trapezoid>{one_target_},   Conjunction::AND, somewhat_desirable_ } );
    rs.add( Rule{ std::vector<Trapezoid>{many_targets_}, Conjunction::AND, undesirable_ } );
    rs.populate_mu_map(std::vector<const double>{0});
    ASSERT_EQ(3, rs._consequents_to_mus.size());

    auto iter = rs._consequents_to_mus.find(highly_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);

    iter = rs._consequents_to_mus.find(somewhat_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    iter = rs._consequents_to_mus.find(undesirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    rs.populate_mu_map(std::vector<const double>{1});
    ASSERT_EQ(3, rs._consequents_to_mus.size());

    iter = rs._consequents_to_mus.find(highly_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    iter = rs._consequents_to_mus.find(somewhat_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);

    iter = rs._consequents_to_mus.find(undesirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    rs.populate_mu_map(std::vector<const double>{2});
    ASSERT_EQ(3, rs._consequents_to_mus.size());

    iter = rs._consequents_to_mus.find(highly_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    iter = rs._consequents_to_mus.find(somewhat_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    iter = rs._consequents_to_mus.find(undesirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);

}