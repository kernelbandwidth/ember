#pragma once

#include <vector>
#include <span>

#include "util.hpp"

namespace ember {
struct Tensor {
    std::vector<size_t> shape;
    std::vector<float> data;

    Tensor(std::vector<size_t> shape):
        shape(std::move(shape)),
        data(std::vector<float>(compute_size(this->shape))) {}

    Tensor(std::vector<size_t> shape, float fill_value):
        shape(std::move(shape)),
        data(compute_size(this->shape)) {
            std::fill(data.begin(), data.end(), fill_value);
        }

    size_t size() const {
        return data.size();
    }
    
    // Indexing operations
    size_t index(std::span<const size_t> indices) const {
        ASSERT_EQ_DEBUG(indices.size(), shape.size());
        size_t flat_index = 0;
        size_t stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i) {
            flat_index += indices[i] * stride;
            stride *= shape[i];
        }

        return flat_index;
    }

    float& operator()(std::span<const size_t> indices) {
        return data[index(indices)];
    }

    float operator()(std::span<const size_t> indices) const {
        return data[index(indices)];
    }
    
    // Utility, primarily for debugging
    void print() const {
        TODO();
    }

private:
    static size_t compute_size(const std::vector<size_t>& dims) {
        size_t size = 1;
        for (auto dim : dims) {
            size *= dim;
        }
        return size;
    }
};
} // namespace ember
