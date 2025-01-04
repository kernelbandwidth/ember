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
    size_t index(std::span<const size_t>& indices) const {
        ASSERT_EQ_DEBUG(indices.size(), shape.size());
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

    void sm(float scalar, Tensor& output) const {
        size_t sz = size();
        ASSERT_EQ_DEBUG(output.size(), sz);
        for (size_t i = 0; i < sz; ++i) {
            output.data[i] = data[i] * scalar;
        }
    }

    void sm_mut(float scalar) { 
        sm(scalar, *this); 
    }

    void matmul(const Tensor& other, Tensor& output) const {
        UNIMPLEMENTED();
    }

    // Core operations that are mutating
    void softmax(size_t axis) {
        ASSERT_LE_DEBUG(axis, shape.size());
        UNIMPLEMENTED();
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
        sm(scalar, output);
        return output;
    }

    Tensor matmul(const Tensor& other) const {
        std::vector<size_t> shape_clone = shape;
        Tensor output(shape_clone);
        matmul(other, output);
        return output;
    }

    float sum() const {
        float total = 0;
        for (size_t i = 0; i < size(); ++i) {
            total += data[i];
        }
        return total;
    }
    
    // Utility, primarily for debugging
    void print() const {
        UNIMPLEMENTED();
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
