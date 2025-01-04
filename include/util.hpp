#include <iostream>
#include <cstdlib>

#define LOG(msg) \
    do { \
        std::cout << "[" << __FILE__ << ":" << __LINE__ << "] (" << __func__ << ")] " << \
        msg << \
        std::endl; \
    } while (false)

#define UNIMPLEMENTED() \
    do { \
        LOG("unimplemented."); \
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

#else

#define ASSERT_EQ_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_LT_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_LE_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_GT_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_GE_DEBUG(lhs, rhs) __ASSERT_NOOP
#define ASSERT_DEBUG(condition) __ASSERT_NOOP

#endif
