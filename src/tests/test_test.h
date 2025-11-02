#include "willow/test.h"

constexpr auto test_toString([[maybe_unused]] Willow::Test* test) -> int {
    if (Willow::toString(Willow::Status::None) != "None") {
        return 1;
    }
    if (Willow::toString(Willow::Status::Pass) != "Passed") {
        return 2;
    }
    if (Willow::toString(Willow::Status::Fail) != "Failed") {
        return 3;
    }
    if (Willow::toString(Willow::Status::Skip) != "Skipped") {
        return 4;
    }
    return 0;
}

namespace FixtureFuncs {
    constexpr auto op_bracket([[maybe_unused]] Willow::Test* t) -> int {
        return 42;
    }
}  // namespace FixtureFuncs

constexpr auto test_Test_Operator([[maybe_unused]] Willow::Test* test) -> int {
    Willow::Test t = {"t", FixtureFuncs::op_bracket};
    t();

    return !(t.retcode == 42);
}
