#include "testing.hpp"
#include "tensor.hpp"

TEST_MAIN()

TEST_CASE(construct_tensor) {
    auto t = ember::Tensor({2, 2}, 4.0f);
}