#pragma once

#include <span>
#include <vector>
#include <numeric>

#include "util.hpp"

class MaskedIndexIterator {
    std::vector<size_t> shape_;
    std::vector<size_t> index_;
    size_t fixed_index_;
    bool done_;

public:
    MaskedIndexIterator(const std::vector<size_t>& shape, size_t fixed_index) :
        shape_(shape), 
        index_(shape.size(), 0), 
        fixed_index_(fixed_index), 
        done_(false) {
            ASSERT_LT_DEBUG(fixed_index_, shape.size());
            index_[fixed_index_] = 0;
            ASSERT_GT_DEBUG(std::accumulate(shape_.begin(), shape_.end(), 0), 0);
    }

    void next() {
        if (done_) return;
        for (size_t i = shape_.size() - 1; i-- > 0;) {
            if (i == fixed_index_) continue;            
            if (++index_[i] < shape_[i]) return;
            index_[i] = 0;
        }
        done_ = true;
    }

    std::span<const size_t> current() { return index_; }

    bool done() { return done_; }
};