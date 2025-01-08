#include <algorithm>
#include <cmath>

#include "algebra.hpp"
#include "index.hpp"
#include "util.hpp"

namespace ember::alg {

// File private helper functions
inline std::vector<size_t> compute_shape(const Tensor& lhs, const Tensor& rhs) {
    TODO();
}

inline std::vector<size_t> compute_shape(const std::vector<size_t>& lhs, const std::vector<size_t>& rhs) {
    TODO();
}

// Implementations

inline void sm(const Tensor& t, float k, Tensor& output) {
    ASSERT_EQ_DEBUG(t.size(), output.size());
    for (size_t i = 0; i < t.size(); ++i) {
        output.data[i] = k * t.data[i];
    }
}

inline Tensor sm(const Tensor& t, float k) {
    std::vector<size_t> shape_clone = t.shape;
    Tensor output(std::move(shape_clone));
    sm(t, k, output);
    return output;
}

inline void sm_mut(Tensor& t, float k) {
    sm(t, k, t);
}

inline void add(const Tensor& lhs, const Tensor& rhs, Tensor& output) {
    ASSERT_EQ_DEBUG(lhs.size(), rhs.size());
    ASSERT_EQ_DEBUG(lhs.size(), output.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        output.data[i] = lhs.data[i] + rhs.data[i];
    }
}

inline Tensor add(const Tensor& lhs, const Tensor& rhs) {
    ASSERT_EQ_DEBUG(lhs.size(), rhs.size());
    std::vector<size_t> shape_clone = lhs.shape;
    Tensor output(shape_clone);
    add(lhs, rhs, output);
    return output;
}

inline void matmul(const Tensor& lhs, const Tensor& rhs, Tensor& output) {
    TODO();
}

inline Tensor matmul(const Tensor& lhs, const Tensor& rhs) {
    Tensor output(compute_shape(lhs, rhs));
    matmul(lhs, rhs, output);
    return output;
}

inline float inner(const Tensor& lhs, const Tensor& rhs) {
    ASSERT_EQ_DEBUG(lhs.shape, rhs.shape);
    ASSERT_EQ_DEBUG(lhs.size(), rhs.size());
    
    float total = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        total += lhs.data[i] * rhs.data[i];
    }
    return total;
}

inline void softmax(Tensor& t, size_t axis) {
    ASSERT_LT_DEBUG(axis, t.shape.size());
    index::MaskedIndexIterator iter(t.shape, axis);

    while (!iter.done()) {
        float max_val = -std::numeric_limits<float>::infinity();
        for (size_t i = 0; i < t.shape[axis]; ++i) {
            max_val = std::max(max_val, t(iter.current(i)));
        }
        float sum_val = 0.0f;
        for (size_t i = 0; i < t.shape[axis]; ++i) {
            size_t raw_index = t.index(iter.current(i));
            t.data[raw_index] = std::exp(t.data[raw_index] - max_val);
            sum_val += t.data[raw_index];
        }
        for (size_t i = 0; i < t.shape[axis]; ++i) {
            t(iter.current(i)) /= sum_val;
        }
    }
}

inline float sum(const Tensor& t) {
    float total = 0;
    for (size_t i = 0; i < t.size(); ++i) {
        total += t.data[i];
    }
    return total;
}

}