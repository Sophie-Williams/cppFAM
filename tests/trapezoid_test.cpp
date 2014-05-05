//
//  TrapezoidTest.cpp
//  cecf
//
//  Created by Chris Powell on 5/4/14.
//  Copyright (c) 2014 Prylis Inc. All rights reserved.
//

#include "gtest/gtest.h"

#include "Trapezoid.h"

// The fixture for testing class ActiveSonar.
class TrapezoidTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    fuzzy::Trapezoid x {7, 10, 13, 16};

    // You can remove any or all of the following functions if its body is empty.

    TrapezoidTest() {
        // You can do set-up work for each test here.
    }

    virtual ~TrapezoidTest() {
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

TEST_F(TrapezoidTest, default_constructs_with_zeros) {
    fuzzy::Trapezoid t;
    ASSERT_EQ(0, t.left());
    ASSERT_EQ(0, t.topLeft());
    ASSERT_EQ(0, t.topRight());
    ASSERT_EQ(0, t.right());
}

TEST_F(TrapezoidTest, constructs_as_specified_with_default_height) {
    ASSERT_EQ(7, x.left());
    ASSERT_EQ(10, x.topLeft());
    ASSERT_EQ(13, x.topRight());
    ASSERT_EQ(16, x.right());
    ASSERT_EQ(1.0, x.height());
}

TEST_F(TrapezoidTest, has_centroid_where_expected) {
    ASSERT_EQ(11.5, x.calculateXCentroid());
}

TEST_F(TrapezoidTest, has_DOM_0_outside_left_bound) {
    ASSERT_EQ(0, x.calculateMu(2));
}

TEST_F(TrapezoidTest, has_DOM_0_outside_right_bound) {
    ASSERT_EQ(0, x.calculateMu(17));
}

TEST_F(TrapezoidTest, has_DOM_1_at_peak) {
    ASSERT_EQ(1, x.calculateMu(12));
}

TEST_F(TrapezoidTest, has_DOM_1_at_top_left) {
    ASSERT_EQ(1, x.calculateMu(10));
}

TEST_F(TrapezoidTest, has_DOM_1_at_top_right) {
    ASSERT_EQ(1, x.calculateMu(13));
}

TEST_F(TrapezoidTest, has_DOM_05_at_half_right_offset) {
    ASSERT_EQ(0.5, x.calculateMu(14.5));
}

TEST_F(TrapezoidTest, has_DOM_05_at_half_left_offset) {
    ASSERT_EQ(0.5, x.calculateMu(8.5));
}

TEST_F(TrapezoidTest, has_DOM_0_at_left) {
    ASSERT_EQ(0, x.calculateMu(7));
}

TEST_F(TrapezoidTest, has_DOM_0_at_right) {
    ASSERT_EQ(0, x.calculateMu(16));
}

TEST_F(TrapezoidTest, centroid_calculates_correctly) {
    fuzzy::Trapezoid t1 {0, 20, 50, 50};
    ASSERT_NEAR(29.583, t1.calculateXCentroid(), 0.001);

    fuzzy::Trapezoid t2 {0, 10, 20, 30};
    ASSERT_NEAR(15, t2.calculateXCentroid(), 0.001);

    fuzzy::Trapezoid t3 {50, 80, 100, 100};
    ASSERT_NEAR(81.4286, t3.calculateXCentroid(), 0.0001);
}

TEST_F(TrapezoidTest, has_correct_DOM_when_fully_positive) {
    fuzzy::Trapezoid t1 {20, 30, 40, 50};
    ASSERT_EQ(0.9, t1.calculateMu(41));
}

TEST_F(TrapezoidTest, larsen_implication_takes_the_height_of_scaling_value) {
    ASSERT_EQ(1.0, x.height());
    auto y = x.larsen(0.15);
    ASSERT_EQ(0.15, y.height());
}

TEST_F(TrapezoidTest, larsen_implication_keeps_four_points) {
    auto y = x.larsen(0.15);
    ASSERT_EQ(7, y.left());
    ASSERT_EQ(10, y.topLeft());
    ASSERT_EQ(13, y.topRight());
    ASSERT_EQ(16, y.right());
}

TEST_F(TrapezoidTest, mamdami_implication_takes_the_height_of_clipping_value) {
    ASSERT_EQ(1.0, x.height());
    auto y = x.mamdami(0.15);
    ASSERT_EQ(0.15, y.height());
}

TEST_F(TrapezoidTest, mamdami_implication_keeps_two_points_gets_two_new) {
    auto y = x.mamdami(0.15);
    ASSERT_EQ(7, y.left());
    ASSERT_EQ(7.45, y.topLeft());
    ASSERT_EQ(15.55, y.topRight());
    ASSERT_EQ(16, y.right());
}

TEST_F(TrapezoidTest, triangle_shaped_trapezoid_behaves_like_a_triangle) {
    fuzzy::Trapezoid z {7,10,10,13};

    ASSERT_EQ(10, z.calculateXCentroid());
    ASSERT_EQ(0, z.calculateMu(2));
    ASSERT_EQ(0, z.calculateMu(15));
    ASSERT_EQ(1, z.calculateMu(10));
    ASSERT_EQ(0.5, z.calculateMu(11.5));
    ASSERT_EQ(0.5, z.calculateMu(8.5));
}

