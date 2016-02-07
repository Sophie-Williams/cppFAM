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
     friend class RuleSetTest_simpleMuMapPopulationWorks_Test;\
     friend class RuleSetTest_simple_mu_map_population_works_2_Test;\
     friend class RuleSetTest_complex_mu_map_population_works_Test; \

#include "rule_set.h"

// Google Test Advanced Guide says: "Pay special attention when your class is defined in a
// namespace, as you should define your test fixtures and tests in the same namespace if
// you want them to be friends of your class."
namespace fuzzy {

class RuleSetTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body is empty.
    fuzzy::Trapezoid cold_ { 40, 40, 40, 50 };
    fuzzy::Trapezoid stop_ { -30, 0, 0, 30 };

    fuzzy::Trapezoid highly_desirable_ { 0, 0, 15, 25 };
    fuzzy::Trapezoid quite_desirable_ { 10, 30, 30, 50 };
    fuzzy::Trapezoid somewhat_desirable_ { 30, 50, 50, 70 };
    fuzzy::Trapezoid mostly_undesirable_ { 50, 70, 70, 90 };
    fuzzy::Trapezoid undesirable_ { 75, 85, 100, 100 };

    fuzzy::Trapezoid no_targets_ { 0, 0, 0, 1 };
    fuzzy::Trapezoid one_target_ { 0, 1, 1, 2 };
    fuzzy::Trapezoid many_targets_ { 1, 2, 10, 10 };

    fuzzy::Trapezoid close_ { 0, 0, 250, 500 };
    fuzzy::Trapezoid medium_ { 250, 500, 1000, 2000 };
    fuzzy::Trapezoid far_ { 1000, 2000, 20000, 20000 };

    fuzzy::Trapezoid ammo_low_ { 0, 0, 5, 10 };
    fuzzy::Trapezoid ammo_ok_ { 0, 10, 20, 30 };
    fuzzy::Trapezoid ammo_lots_ { 10, 30, 40, 40 };

    fuzzy::RuleSet acquisition_ { "Acquisition mode desirability", fuzzy::Implication::LARSEN };
    fuzzy::RuleSet interception_ { "Interception mode desirability", fuzzy::Implication::LARSEN };
    fuzzy::RuleSet quarry_ { "Quarry overall desirability", fuzzy::Implication::LARSEN };

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

TEST_F(RuleSetTest, rs_with_no_rules_returns_zero) {
    fuzzy::RuleSet rs;
    ASSERT_EQ(0, rs.calculate(0));
    ASSERT_EQ(0, rs.calculate(0.2));
    ASSERT_EQ(0, rs.calculate(-1));
    ASSERT_EQ(0, rs.calculate(3));
    ASSERT_EQ(0, rs.calculate(35));
    ASSERT_EQ(0, rs.calculate(-3132));
}

TEST_F(RuleSetTest, simpleMuMapPopulationWorks) {
    fuzzy::RuleSet rs;
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {cold_}, fuzzy::Conjunction::AND, stop_, "if room is cold, fan motor stops" });
    rs.populate_mu_map(std::vector <double> {40.0});
    ASSERT_EQ(1, rs._consequents_to_mus.size());

    auto iter = rs._consequents_to_mus.find(stop_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);

    iter = rs._consequents_to_mus.find(stop_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(1.0, iter->second);
}

TEST_F(RuleSetTest, simple_mu_map_population_works_2) {
    fuzzy::RuleSet rs; // "acquisition mode desirability"
    rs.add(Rule { std::vector<fuzzy::Trapezoid>{no_targets_},   fuzzy::Conjunction::AND, highly_desirable_ });
    rs.add(Rule { std::vector<fuzzy::Trapezoid>{one_target_},   fuzzy::Conjunction::AND, somewhat_desirable_ });
    rs.add(Rule { std::vector<fuzzy::Trapezoid>{many_targets_}, fuzzy::Conjunction::AND, undesirable_ });
    rs.populate_mu_map(std::vector<double> {0});
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

    rs.populate_mu_map(std::vector<double> {1});
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

    rs.populate_mu_map(std::vector<double> {2});
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

TEST_F(RuleSetTest, complex_mu_map_population_works) {
    fuzzy::RuleSet rs; // "rocket desirability"
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{far_, ammo_lots_}, fuzzy::Conjunction::AND, somewhat_desirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{far_, ammo_ok_}, fuzzy::Conjunction::AND, undesirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{far_, ammo_low_}, fuzzy::Conjunction::AND, undesirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{medium_, ammo_lots_}, fuzzy::Conjunction::AND, highly_desirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{medium_, ammo_ok_}, fuzzy::Conjunction::AND, highly_desirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{medium_, ammo_low_}, fuzzy::Conjunction::AND, somewhat_desirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{close_, ammo_lots_}, fuzzy::Conjunction::AND, undesirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{close_, ammo_ok_}, fuzzy::Conjunction::AND, undesirable_});
    rs.add(Rule {std::vector<fuzzy::Trapezoid>{close_, ammo_low_}, fuzzy::Conjunction::AND, undesirable_});

    rs.populate_mu_map(std::vector<double> {700, 25});
    ASSERT_EQ(3, rs._consequents_to_mus.size());

    auto iter = rs._consequents_to_mus.find(highly_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.75, iter->second);

    iter = rs._consequents_to_mus.find(somewhat_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    iter = rs._consequents_to_mus.find(undesirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);

    rs.populate_mu_map(std::vector<double> {500, 7});
    ASSERT_EQ(3, rs._consequents_to_mus.size());

    iter = rs._consequents_to_mus.find(highly_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.7, iter->second);

    iter = rs._consequents_to_mus.find(somewhat_desirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.6, iter->second);

    iter = rs._consequents_to_mus.find(undesirable_);
    ASSERT_NE(end(rs._consequents_to_mus), iter);
    ASSERT_EQ(0.0, iter->second);
}

TEST_F(RuleSetTest, scale_and_defuzzify_works_correctly_in_simple_case) {
    fuzzy::RuleSet rs; // "acquisition mode desirability"
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {no_targets_}, fuzzy::Conjunction::AND, highly_desirable_ });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {one_target_}, fuzzy::Conjunction::AND, somewhat_desirable_ });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {many_targets_}, fuzzy::Conjunction::AND, undesirable_ });
    //
    //    for (int tgts = 0; tgts < 5; ++tgts) {
    //        std::cout << "Targets " << tgts << ", score " << rs.calculate(static_cast<double>(tgts)) << std::endl;
    //    }

}

TEST_F(RuleSetTest, scale_and_defuzzify_works_compares_correctly_to_PGAIBE_book) {
    fuzzy::Trapezoid close { 0, 0, 25, 150 };
    fuzzy::Trapezoid medium { 25, 150, 150, 300 };
    fuzzy::Trapezoid far { 150, 300, 400, 400 };

    fuzzy::Trapezoid ammo_low { 0, 0, 0, 10 };
    fuzzy::Trapezoid ammo_ok { 0, 10, 10, 30 };
    fuzzy::Trapezoid ammo_lots { 10, 30, 50, 50 };

    fuzzy::Trapezoid undes { 0, 0, 25, 50 };
    fuzzy::Trapezoid des { 25, 50, 50, 75 };
    fuzzy::Trapezoid vdes { 50, 75, 100, 100 };

    fuzzy::RuleSet rs("rocket desirability", fuzzy::Implication::MAMDANI);
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {far, ammo_lots}, fuzzy::Conjunction::AND, des, "far + lots is desirable" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {far, ammo_ok}, fuzzy::Conjunction::AND, undes, "far + some is undesirable" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {far, ammo_low}, fuzzy::Conjunction::AND, undes, "far + low is undesirable" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {medium, ammo_lots}, fuzzy::Conjunction::AND, vdes, "med + lots is very des" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {medium, ammo_ok}, fuzzy::Conjunction::AND, vdes, "med + some is very des" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {medium, ammo_low}, fuzzy::Conjunction::AND, des, "med + low is desirable" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {close, ammo_lots}, fuzzy::Conjunction::AND, undes, "close + lots is undes" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {close, ammo_ok}, fuzzy::Conjunction::AND, undes, "close + some is undes" });
    rs.add(fuzzy::Rule { std::vector <fuzzy::Trapezoid> {close, ammo_low}, fuzzy::Conjunction::AND, undes, "close + low is undes" });

    //    for (int dist = 0; dist<550; dist=dist+50) {
    //        for (int ammo = 3; ammo < 50; ammo+=5) {
    //            std::cout << "Ammo " << ammo << ", dist " << dist << ", score " << rs.calculate(std::vector<double>{static_cast<double>(dist), static_cast<double>(ammo)}) << std::endl;
    //        }
    //        std::cout << "\n";
    //    }

    ASSERT_NEAR(55.1289, rs.calculate(std::vector <double> {static_cast<double>(100), static_cast<double>(8)}), 0.01);
    ASSERT_NEAR(58.54, rs.calculate(std::vector <double> {static_cast<double>(200), static_cast<double>(8)}), 0.01);
    ASSERT_NEAR(20.4167, rs.calculate(std::vector <double> {static_cast<double>(300), static_cast<double>(8)}), 0.01);
    ASSERT_NEAR(20.4167, rs.calculate(std::vector <double> {static_cast<double>(400), static_cast<double>(8)}), 0.01);

    ASSERT_NEAR(56.1547, rs.calculate(std::vector <double> {static_cast<double>(100), static_cast<double>(33)}), 0.01);
    ASSERT_NEAR(69.2593, rs.calculate(std::vector <double> {static_cast<double>(200), static_cast<double>(33)}), 0.01);
    ASSERT_NEAR(50, rs.calculate(std::vector <double> {static_cast<double>(300), static_cast<double>(33)}), 0.01);
    ASSERT_NEAR(50, rs.calculate(std::vector <double> {static_cast<double>(400), static_cast<double>(33)}), 0.01);
}

}