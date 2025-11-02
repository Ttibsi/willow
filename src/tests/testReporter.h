#ifndef WILLOW_TEST_SILENT_REPORTER_H
#define WILLOW_TEST_SILENT_REPORTER_H

#include "willow/reporters.h"

class SilentReporter : public Willow::Reporter {
   public:
    constexpr SilentReporter() {}
    constexpr inline auto print([[maybe_unused]] const Willow::Test& test) -> void {}
    constexpr inline auto cleanup() -> void {}
};

#endif  // WILLOW_TEST_SILENT_REPORTER_H
