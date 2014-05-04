#include "gtest/gtest.h"

// Minimal printer:
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    // Gets hold of the event listener list.
//    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
//    listeners.Append(new MinimalistPrinter);
//    return RUN_ALL_TESTS();
//}

// Stock gtest:
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}