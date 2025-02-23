#include <vector>

#include "testing.hpp"

#include "algebra.hpp"
#include "index.hpp"
#include "tensor.hpp"


TEST_MAIN()

namespace ember::alg {

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
    auto got = sm(t, 3.0f);
    for (size_t i = 0; i < t.data.size(); ++i) {
        EXPECT_AP_EQ(got.data[i], 3.0f);
    }
}

TEST_CASE(scalar_multiplication_mut_works) {
    Tensor t(std::vector({2ul, 2ul}));
    assign_all(t, 1.0f);
    sm_mut(t, 3.0f);
    for (size_t i = 0; i < t.data.size(); ++i) {
        EXPECT_AP_EQ(t.data[i], 3.0f);
    }
}

TEST_CASE(inner_works) {
    Tensor lhs(std::vector{4ul});
    Tensor rhs(std::vector{4ul});
    assign_all(lhs, 2.0f);
    assign_all(rhs, 2.0f);
    float got = inner(lhs, rhs);
    EXPECT_AP_EQ(got, 16.0f);
}

TEST_CASE(softmax_vector_works) {
    Tensor t(std::vector({5ul}));
    assign_all(t, 1.0f);
    softmax(t, 0);
    float sum = 0.0f;
    for (size_t i = 0; i < t.size(); ++i) {
        sum += t.data[i];
    }

    EXPECT_AP_EQ(sum, 1.0f);
}

TEST_CASE(softmax_matrix_works) {
    Tensor t(std::vector({2ul, 2ul}));
    assign_all(t, 1.0f);
    softmax(t, 0);
    index::MaskedIndexIterator iter(t.shape, 0);
    while (!iter.done()) {
        float sum = 0.0f;
        for (size_t i = 0; i < t.shape[0]; ++i) {
            size_t idx = t.index(iter.current(i));
            sum += t.data[idx];
        }
        EXPECT_AP_EQ(sum, 1.0f);
        iter.next();
    }
}
} // namespace ember