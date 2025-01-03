#include <iostream>
#include <cstdlib>

#define LOG(msg) \
    do { \
        std::cout << "[" << __FILE__ << ":" << __LINE__ << "] (" << __func__ << ")] " << \
        msg << \
        std::endl; \
    } while (false)

#define unimplemented() \
    do { \
        LOG("unimplemented."); \
        std::exit(EXIT_FAILURE); \
    } while (false)

#ifndef NDEBUG
#define ASSERT_EQ_DEBUG(lhs, rhs) \
    do { \
        if (lhs != rhs) { \
            LOG("Assertion failed: " #lhs " == " #rhs ", (" << (lhs) << ") != (" << (rhs) << ")"); \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)
#else
#define ASSERT_EQ_DEBUG(lhs, rhs) do {} while (false)
#endif