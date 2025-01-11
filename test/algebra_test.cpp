#include <vector>

#include "testing.hpp"
#include "tensor.hpp"
#include "algebra.hpp"

TEST_MAIN()

namespace ember {

void assign_all(Tensor& t, float value) {
    for (size_t i = 0; i < t.data.size(); ++i) {
        t.data[i] = value;
    }
}

TEST_CASE(assign_all_works) {
    Tensor t(std::vector({2ul, 2ul}));
    assign_all(t, 3.0f);
    for (size_t i = 0; i < t.data.size(); ++i) {
        EXPECT_EQ(t.data[i], 3.0f);
    }
}

TEST_CASE(scalar_multiplication_works) {
    Tensor t(std::vector({2ul, 2ul}));
    assign_all(t, 1.0f);
    auto got = alg::sm(t, 3.0f);
    for (size_t i = 0; i < t.data.size(); ++i) {
        EXPECT_AP_EQ(got.data[i], 3.0f);
    }
}

TEST_CASE(scalar_multiplication_mut_works) {
    Tensor t(std::vector({2ul, 2ul}));
    assign_all(t, 1.0f);
    alg::sm_mut(t, 3.0f);
    for (size_t i = 0; i < t.data.size(); ++i) {
        EXPECT_AP_EQ(t.data[i], 3.0f);
    }
}
} // namespace ember