#include "willow/reporters.h"
#include "willow/willow.h"

auto test_pass() -> int {
    return 0;
}

auto test_fail() -> int {
    return 1;
}

auto test_skip() -> int {
    return 1;
}

auto main() -> int {
    Willow::PreCommitReporter r = {};
    return Willow::run_tests(
        {
            {"Pass", test_pass},
            {"Fail", test_fail},
            {"Skipped", test_skip, Willow::Status::Skip},
        },
        r);
}
