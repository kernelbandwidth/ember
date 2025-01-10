#include <vector>

#include "testing.hpp"
#include "tensor.hpp"
#include "algebra.hpp"

TEST_MAIN()

namespace ember {
TEST_CASE(scalar_multiplication_works) {
    Tensor t(std::vector({size_t(2), size_t(2)}));
    for (size_t i = 0; i < t.data.size(); ++i) {
        t.data[i] = 1;
    }

    auto got = alg::sm(t, 3.0f);
    for (size_t i = 0; i < t.data.size(); ++i) {
        EXPECT_AP_EQ(got.data[i], 3.0f);
    }
}
} // namespace ember