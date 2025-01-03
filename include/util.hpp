#include <iostream>
#include <cstdlib>

#define LOG(msg) do { std::cout << "[" << __FILE__ << ":" << __LINE__ << "] (" << __func__ << ")] " << msg << std::endl; } while (false)

#define unimplemented() do { LOG("unimplemented!"); std::exit(EXIT_FAILURE); } while (false)
