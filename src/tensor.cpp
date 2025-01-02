#include "tensor.hpp"

#include <iostream>

namespace ember {
Tensor::Tensor(std::initializer_list<size_t> shape): shape(shape), data(std::vector<float>(size())) {}

Tensor::Tensor(std::initializer_list<size_t> shape, float fill_value): 
    shape(shape), data(size()) {
        std::fill(data.begin(), data.end(), fill_value);
    }

size_t Tensor::size() const {
    size_t total = 1;
    for (size_t dim: shape) {
        total *= dim;
    }
    return total;
}

size_t Tensor::index(std::span<const size_t>& indices) const {
    assert(indices.size() == shape.size());
    size_t flat_index = 0;
    size_t stride = 1;

    for (int i = shape.size() - 1; i >= 0; --i) {
        flat_index += indices[i] * stride;
        stride *= shape[i];
    }

    return flat_index;
}

float& Tensor::operator()(std::span<const size_t>& indices) {
    return data[index(indices)];
}

float Tensor::operator()(std::span<const size_t>& indices) const {
    return data[index(indices)];
}

} // namespace ember
