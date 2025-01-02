#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <string>

#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"

struct Test {
    std::string name;
    std::function<void()> test_fn;

    Test(const std::string& name, const std::function<void()>& test_fn) :
        name(name),
        test_fn(test_fn) {}
};

inline std::vector<Test>& test_registry() {
    static std::vector<Test> registry;
    return registry;
}

struct TestRegistrar {
    TestRegistrar(const std::string& name, const std::function<void()>& test_fn) {
        test_registry().emplace_back(name, test_fn);
    }
};

#define TEST_CASE(name) \
    void name(); \
    static TestRegistrar _registrar_##name(#name, name); \
    void name()

inline int run_tests() {
    bool all_passed = true;
    for (const auto& test : test_registry()) {
        try {
            test.test_fn();
            std::cout << COLOR_GREEN "[PASS] " COLOR_RESET << test.name << std::endl;
        } catch (const std::exception& e) {
            all_passed = false;
            std::cerr << COLOR_RED "[FAIL] " COLOR_RESET << test.name << " - " << e.what() << std::endl;
        } catch (...) {
            all_passed = false;
            std::cerr << "[FAIL] " << test.name << " - Unknown exception" << std::endl; 
        }
    }
    return all_passed ? 0 : 1;
}

#define TEST_MAIN() \
    int main() { return run_tests(); }

#define EXPECT_EQ(lhs, rhs) \
    do { \
        if (lhs != rhs) { \
            throw std::runtime_error("Expected equality"); \
        } \
    } while (false)
