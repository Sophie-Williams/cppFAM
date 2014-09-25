//
//  RuleSetTest.cpp
//  cecf
//
//  Created by Chris Powell on 5/7/14.
//  Copyright (c) 2014 Prylis Inc. All rights reserved.
//

#include "gtest/gtest.h"

// https://stackoverflow.com/questions/14186245/unit-testing-c-how-to-test-private-members
#define TEST_FRIENDS \
    friend class RuleSetTest_simple_mu_map_population_works_1_Test; \
 
#include "rule_set.h"
#include <vector>

using namespace fuzzy;

class RuleSetTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body is empty.
    Trapezoid cold_ {40, 40, 40, 50};
    Trapezoid stop_ {-30, 0,  0, 30};

    Trapezoid highly_desirable_ {0,0,15,25};
    Trapezoid quite_desirable_ {10,30,30,50};
    Trapezoid somewhat_desirable_ {30,50,50,70};
    Trapezoid mostly_undesirable_ {50,70,70,90};
    Trapezoid undesirable_ {75,85,100,100};

    Trapezoid no_targets_ {0,0,0,1};
    Trapezoid one_target_ {0,1,1,2};
    Trapezoid many_targets_ {1,2,10,10};

    Trapezoid close_ {0,0,250,500};
    Trapezoid medium_ {250,500,1000,2000};
    Trapezoid far_ {1000,2000, 20000, 20000};

    Trapezoid ammo_low_ {0, 0, 5, 10};
    Trapezoid ammo_ok_ {0, 10, 20, 30};
    Trapezoid ammo_lots_ {10, 30, 40, 40};

    RuleSet acquisition_ {"Acquisition mode desirability", Implication::LARSEN};
    RuleSet interception_ {"Interception mode desirability", Implication::LARSEN};
    RuleSet quarry_ {"Quarry overall desirability", Implication::LARSEN};

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
//
//TEST_F(RuleSetTest, simple_mu_map_population_works_1) {
//    RuleSet rs;
//    rs.add( Rule {std::vector<Trapezoid>{cold_}, Conjunction::AND, stop_,  "if room is cold, fan motor stops"} );
//    rs.populate_mu_map(std::vector<const double> {40.0});
//    ASSERT_EQ(1, rs._consequents_to_mus.size());
//
//    auto iter = rs._consequents_to_mus.find(stop_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(1.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(stop_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(1.0, iter->second);
//}
//
//TEST_F(RuleSetTest, simple_mu_map_population_works_2) {
//    RuleSet rs; // "acquisition mode desirability"
//    rs.add( Rule { std::vector<Trapezoid>{no_targets_},   Conjunction::AND, highly_desirable_ } );
//    rs.add( Rule { std::vector<Trapezoid>{one_target_},   Conjunction::AND, somewhat_desirable_ } );
//    rs.add( Rule { std::vector<Trapezoid>{many_targets_}, Conjunction::AND, undesirable_ } );
//    rs.populate_mu_map(std::vector<const double> {0});
//    ASSERT_EQ(3, rs._consequents_to_mus.size());
//
//    auto iter = rs._consequents_to_mus.find(highly_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(1.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(somewhat_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(undesirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    rs.populate_mu_map(std::vector<const double> {1});
//    ASSERT_EQ(3, rs._consequents_to_mus.size());
//
//    iter = rs._consequents_to_mus.find(highly_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(somewhat_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(1.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(undesirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    rs.populate_mu_map(std::vector<const double> {2});
//    ASSERT_EQ(3, rs._consequents_to_mus.size());
//
//    iter = rs._consequents_to_mus.find(highly_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(somewhat_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(undesirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(1.0, iter->second);
//}
//
//TEST_F(RuleSetTest, compex_mu_map_population_works) {
//    RuleSet rs; // "rocket desirability"
//    rs.add( Rule {std::vector<Trapezoid>{far_, ammo_lots_}, Conjunction::AND, somewhat_desirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{far_, ammo_ok_}, Conjunction::AND, undesirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{far_, ammo_low_}, Conjunction::AND, undesirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{medium_, ammo_lots_}, Conjunction::AND, highly_desirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{medium_, ammo_ok_}, Conjunction::AND, highly_desirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{medium_, ammo_low_}, Conjunction::AND, somewhat_desirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{close_, ammo_lots_}, Conjunction::AND, undesirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{close_, ammo_ok_}, Conjunction::AND, undesirable_} );
//    rs.add( Rule {std::vector<Trapezoid>{close_, ammo_low_}, Conjunction::AND, undesirable_} );
//
//    rs.populate_mu_map(std::vector<const double> {700, 25});
//    ASSERT_EQ(3, rs._consequents_to_mus.size());
//
//    auto iter = rs._consequents_to_mus.find(highly_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.75, iter->second);
//
//    iter = rs._consequents_to_mus.find(somewhat_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    iter = rs._consequents_to_mus.find(undesirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//
//    rs.populate_mu_map(std::vector<const double> {500, 7});
//    ASSERT_EQ(3, rs._consequents_to_mus.size());
//
//    iter = rs._consequents_to_mus.find(highly_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.7, iter->second);
//
//    iter = rs._consequents_to_mus.find(somewhat_desirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.6, iter->second);
//
//    iter = rs._consequents_to_mus.find(undesirable_);
//    ASSERT_NE(end(rs._consequents_to_mus), iter);
//    ASSERT_EQ(0.0, iter->second);
//}

TEST_F(RuleSetTest, scale_and_defuzzify_works_correctly_in_simple_case) {
    RuleSet rs; // "acquisition mode desirability"
    rs.add( Rule { std::vector<Trapezoid>{no_targets_},   Conjunction::AND, highly_desirable_ } );
    rs.add( Rule { std::vector<Trapezoid>{one_target_},   Conjunction::AND, somewhat_desirable_ } );
    rs.add( Rule { std::vector<Trapezoid>{many_targets_}, Conjunction::AND, undesirable_ } );
//
//    for (int tgts = 0; tgts < 5; ++tgts) {
//        std::cout << "Targets " << tgts << ", score " << rs.calculate(static_cast<double>(tgts)) << std::endl;
//    }

}

TEST_F(RuleSetTest, scale_and_defuzzify_works_compares_correctly_to_PGAIBE_book) {
    Trapezoid close {0,0,25,150};
    Trapezoid medium {25,150,150,300};
    Trapezoid far {150,300,400,400};

    Trapezoid ammo_low {0, 0, 0, 10};
    Trapezoid ammo_ok {0, 10, 10, 30};
    Trapezoid ammo_lots {10, 30, 50, 50};

    Trapezoid undes {0,0,25,50};
    Trapezoid des {25,50,50,75};
    Trapezoid vdes {50,75,100,100};

    RuleSet rs("rocket desirability", Implication::MAMDANI);
    rs.add( Rule {std::vector<Trapezoid>{far, ammo_lots}, Conjunction::AND, des, "far + lots is desirable"} );
    rs.add( Rule {std::vector<Trapezoid>{far, ammo_ok}, Conjunction::AND, undes, "far + some is undesirable"} );
    rs.add( Rule {std::vector<Trapezoid>{far, ammo_low}, Conjunction::AND, undes, "far + low is undesirable"} );
    rs.add( Rule {std::vector<Trapezoid>{medium, ammo_lots}, Conjunction::AND, vdes, "med + lots is very des"} );
    rs.add( Rule {std::vector<Trapezoid>{medium, ammo_ok}, Conjunction::AND, vdes, "med + some is very des"} );
    rs.add( Rule {std::vector<Trapezoid>{medium, ammo_low}, Conjunction::AND, des, "med + low is desirable"} );
    rs.add( Rule {std::vector<Trapezoid>{close, ammo_lots}, Conjunction::AND, undes, "close + lots is undes"} );
    rs.add( Rule {std::vector<Trapezoid>{close, ammo_ok}, Conjunction::AND, undes, "close + some is undes"} );
    rs.add( Rule {std::vector<Trapezoid>{close, ammo_low}, Conjunction::AND, undes, "close + low is undes"} );

//    for (int dist = 0; dist<550; dist=dist+50) {
//        for (int ammo = 3; ammo < 50; ammo+=5) {
//            std::cout << "Ammo " << ammo << ", dist " << dist << ", score " << rs.calculate(std::vector<const double>{static_cast<double>(dist), static_cast<double>(ammo)}) << std::endl;
//        }
//        std::cout << "\n";
//    }

    ASSERT_NEAR(55.1289, rs.calculate(std::vector<const double> {static_cast<double>(100), static_cast<double>(8)}), 0.01);
    ASSERT_NEAR(58.54, rs.calculate(std::vector<const double> {static_cast<double>(200), static_cast<double>(8)}), 0.01);
    ASSERT_NEAR(20.4167, rs.calculate(std::vector<const double> {static_cast<double>(300), static_cast<double>(8)}), 0.01);
    ASSERT_NEAR(20.4167, rs.calculate(std::vector<const double> {static_cast<double>(400), static_cast<double>(8)}), 0.01);

    ASSERT_NEAR(56.1547, rs.calculate(std::vector<const double> {static_cast<double>(100), static_cast<double>(33)}), 0.01);
    ASSERT_NEAR(69.2593, rs.calculate(std::vector<const double> {static_cast<double>(200), static_cast<double>(33)}), 0.01);
    ASSERT_NEAR(50, rs.calculate(std::vector<const double> {static_cast<double>(300), static_cast<double>(33)}), 0.01);
    ASSERT_NEAR(50, rs.calculate(std::vector<const double> {static_cast<double>(400), static_cast<double>(33)}), 0.01);
}


























