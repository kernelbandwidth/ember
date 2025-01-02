#pragma once
#include <vector>
#include <span>
#include <cassert>
#include <initializer_list>

namespace ember {
struct Tensor {
    std::vector<size_t> shape;
    std::vector<float> data;

    Tensor(std::initializer_list<size_t> shape);
    Tensor(std::initializer_list<size_t> shape, float fill_value = 0.0f);

    size_t size() const;
    
    // Indexing operations
    size_t index(std::span<const size_t>& indices) const;
    float& operator()(std::span<const size_t>& indices);
    float operator()(std::span<const size_t>& indices) const;

    // Core algebra operations with buffer reuse
    void add(const Tensor& other, Tensor& output) const;
    void scalar_mut(float scalar, Tensor& output) const;
    void matmul(const Tensor& other, Tensor& output) const;

    void softmax(size_t axis);

    // Core algebra operations (allocates return value)
    Tensor operator+(const Tensor& other) const;
    Tensor operator*(float scalar) const;
    Tensor matmul(const Tensor& other) const;

    float sum() const;
    
    // Utility, primarily for debugging
    void print() const;

private:
    void validate_shape(const Tensor& other, const char* operation) const;
    void validate_output(const Tensor& output, const char* operation) const;
};
} // namespace ember
