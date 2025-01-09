#include "testing.hpp"

TEST_MAIN()

TEST_CASE(true_is_true) {
    EXPECT_EQ(true, true);
}

TEST_CASE(approx_eq_is_eq) {
    EXPECT_AP_EQ(1.0f, 1.0f + (EPSILON / 2.0f));
}


