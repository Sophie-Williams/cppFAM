//
//  TriangleTest.cpp
//  cecf
//
//  Created by Chris Powell on 5/4/14.
//  Copyright (c) 2014 Prylis Inc. All rights reserved.
//

#include "gtest/gtest.h"

#include "triangle.h"

// The fixture for testing class ActiveSonar.
class TriangleTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    fuzzy::Triangle x {7, 10, 13};

    // You can remove any or all of the following functions if its body is empty.

    TriangleTest() {
        // You can do set-up work for each test here.
    }

    virtual ~TriangleTest() {
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

TEST_F(TriangleTest, default_constructs_with_zeros) {
    fuzzy::Triangle t;
    ASSERT_EQ(0, t.left());
    ASSERT_EQ(0, t.center());
    ASSERT_EQ(0, t.right());
}

TEST_F(TriangleTest, constructs_as_specified_with_default_height) {
    fuzzy::Triangle t{-5,1,7};
    ASSERT_EQ(-5, t.left());
    ASSERT_EQ(1, t.center());
    ASSERT_EQ(7, t.right());
    ASSERT_EQ(1.0, t.height());
}

TEST_F(TriangleTest, has_centroid_of_peak_for_isoceles_triangle) {
    ASSERT_EQ(10, x.calculateXCentroid());
}

TEST_F(TriangleTest, has_DOM_0_outside_left_bound) {
    ASSERT_EQ(0, x.calculateMu(2));
}

TEST_F(TriangleTest, has_DOM_0_outside_right_bound) {
    ASSERT_EQ(0, x.calculateMu(15));
}

TEST_F(TriangleTest, has_DOM_1_at_peak) {
    ASSERT_EQ(1, x.calculateMu(10));
}

TEST_F(TriangleTest, has_DOM_05_at_half_right_offset) {
    ASSERT_EQ(0.5, x.calculateMu(11.5));
}

TEST_F(TriangleTest, has_DOM_05_at_half_left_offset) {
    ASSERT_EQ(0.5, x.calculateMu(8.5));
}

TEST_F(TriangleTest, has_correct_DOM_at_threefifths_offset) {
    fuzzy::Triangle y {0,5,10};
    ASSERT_EQ(0.6, y.calculateMu(3.0));
}

TEST_F(TriangleTest, has_correct_DOM_at_seventenths_offset) {
    fuzzy::Triangle y {0,5,10};
    ASSERT_EQ(0.6, y.calculateMu(7.0));
}

TEST_F(TriangleTest, larsen_implication_takes_the_height_of_larsen_value) {
    auto y = x.larsen(0.15);
    ASSERT_EQ(0.15, y->height());
}

//TEST_F(TriangleTest, larsen_implication_keeps_right_left_and_center) {
//    auto y = x.larsen(0.15);
//    ASSERT_EQ(7, static_  y->left());
//}


