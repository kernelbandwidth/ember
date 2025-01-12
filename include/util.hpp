#pragma once

#include <iostream>
#include <cstdlib>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
        os << "]";
    }
    return os;
}

#define LOG(msg) \
    do { \
        std::cout << "[" << __FILE__ << ":" << __LINE__ << "] (" << __func__ << ")] " << \
        msg << \
        std::endl; \
    } while (false)

#define TODO() \
    do { \
        LOG("todo"); \
        std::exit(EXIT_FAILURE); \
    } while (false)

#define __ASSERT_OP_DEBUG(lhs, op, rhs, op_str) \
    do { \
        if (!((lhs) op (rhs))) { \
            LOG("Assertion failed: " #lhs " " op_str " " #rhs ", got (" << (lhs) << ") and (" << (rhs) << ")"); \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

#define __ASSERT_NOOP do {} while (false)

#ifndef NDEBUG

#define ASSERT_EQ_DEBUG(lhs, rhs) __ASSERT_OP_DEBUG(lhs, ==, rhs, "==")
#define ASSERT_NE_DEBUG(lhs, rhs) __ASSERT_OP_DEBUG(lhs, !=, rhs, "!=")
#define ASSERT_LT_DEBUG(lhs, rhs) __ASSERT_OP_DEBUG(lhs, <, rhs, "<")
#define ASSERT_LE_DEBUG(lhs, rhs) __ASSERT_OP_DEBUG(lhs, <=, rhs, "<=")
#define ASSERT_GT_DEBUG(lhs, rhs) __ASSERT_OP_DEBUG(lhs, >, rhs, ">")
#define ASSERT_GE_DEBUG(lhs, rhs) __ASSERT_OP_DEBUG(lhs, >=, rhs, ">=")

#define ASSERT_TRUE_DEBUG(condition) \
    do { \
        if (!(condition)) { \
            LOG("Assertion failed: " #condition " expected to be true, was false"); \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

#define ASSERT_FALSE_DEBUG(condition) \
    do { \
        if (condition) { \
            LOG("Assertion failed: " #condition " expected to be false, was true"); \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

#else

#define ASSERT_EQ_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_LT_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_LE_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_GT_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_GE_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_TRUE_DEBUG(condition) __ASSERT_NOOP
#define ASSERT_FALSE_DEBUG(condition) __ASSERT_NOOP
#endif
