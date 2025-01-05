#pragma once

#include "tensor.hpp"

namespace ember::alg {

// Scalar operations
void sm(const Tensor& t, float k, Tensor& output);
Tensor sm(const Tensor& t, float k);
void sm_mut(Tensor& t, float k);

// Element-wise operations
void add(const Tensor& lhs, const Tensor& rhs, Tensor& output);
Tensor add(const Tensor& lhs, const Tensor& rhs);

// Higher level operations
void matmul(const Tensor& lhs, const Tensor& rhs, Tensor& output);
Tensor matmul(const Tensor& lhs, const Tensor& rhs);

float inner(const Tensor& lhs, const Tensor& rhs);

// Mutating operations
void softmax(Tensor& t, size_t axis);

// Reducer operations
float sum(const Tensor& t);

} // namespace ember::alg