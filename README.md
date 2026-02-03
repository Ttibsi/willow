# Willow

A unit testing library for modern c++23

# How to use
Currently, willow only supports CMake for distribution, although if you know
what you're doing, feel free to clone the repo and build it yourself

```cmake
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)
fetchcontent_declare(
  willow
  GIT_REPOSITORY https://github.com/ttibsi/willow
  GIT_TAG        v0.0.1
)
fetchcontent_makeavailable(willow)
```

# Example
A minimal usage looks like the below code. However, willow dogfoods itself,
meaning that it's tested with itself. To see more usage, see the `src/main.cpp`
file -- anything in the `src/` directory are the tests for this project,
`src/willow` is the source code.

```cpp
#include <willow/reporters.h>
#include <willow/willow.h>

auto add(int x, int y) -> int { return x + y; }

// Any test must follow this signature. It's return code is used to mark if
// it succeeded or not. Alerts print on function failure
auto test_add(Willow::Test* test) -> int {
    if (add(3, 2) != 5) {
        test->alert("3 + 2 does not equal 5");
        return 1;
    }

    return 0;
}

auto main() -> int {
    // Select which reporter to use to display output. A number of reporters
    // are available
    Willow::DefaultReporter reporter = {};

    // Register each function to test
    Willow::registerTests({
        // Each test function is given a name to display as output. you can also
        // mark tests for skipping
        {"addition test", test_add},
        {"skipped test", test_add, Willow::Status::Skip},
    });

    // Your executable will exit with a return code displaying the number of
    // failed tests
    return Willow::runTests(reporter);
}
```
