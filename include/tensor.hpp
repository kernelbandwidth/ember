#pragma once
#include <vector>
#include <span>
#include <cassert>
#include <initializer_list>

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
        return compute_size(shape);
    }
    
    // Indexing operations
    size_t index(std::span<const size_t>& indices) const {
        assert(indices.size() == shape.size());
        size_t flat_index = 0;
        size_t stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i) {
            flat_index += indices[i] * stride;
            stride *= shape[i];
        }

        return flat_index;
    }

    float& operator()(std::span<const size_t>& indices) {
        return data[index(indices)];
    }

    float operator()(std::span<const size_t>& indices) const {
        return data[index(indices)];
    }

    // Core algebra operations with buffer reuse
    void add(const Tensor& other, Tensor& output) const {
        size_t sz = size();
        for (size_t i = 0; i < sz; ++i) {
            output.data[i] = data[i] + other.data[i];
        }
    }

    void scalar_mul(float scalar, Tensor& output) const {
        size_t sz = size();
        assert(output.size() == sz);
        for (size_t i = 0; i < sz; ++i) {
            output.data[i] = data[i] * scalar;
        }
    }

    void scalar_mul_mut(float scalar) { 
        scalar_mul(scalar, *this); 
    }

    void matmul(const Tensor& other, Tensor& output) const {
        unimplemented();
    }

    // Core operations that are mutating
    void softmax(size_t axis) {
        unimplemented();
    }

    // Core algebra operations (allocates return value)
    Tensor operator+(const Tensor& other) const {
        std::vector<size_t> shape_clone = shape;
        Tensor output(shape_clone);
        add(other, output);
        return output;   
    }

    Tensor operator*(float scalar) const {
        std::vector<size_t> shape_clone = shape;
        Tensor output(shape_clone);
        scalar_mul(scalar, output);
        return output;
    }

    Tensor matmul(const Tensor& other) const {
        unimplemented();
    }

    float sum() const {
        unimplemented();
    }
    
    // Utility, primarily for debugging
    void print() const {
        unimplemented();
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
