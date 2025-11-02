#include "testReporter.h"
#include "willow/willow.h"

namespace FixtureFuncs {
    constexpr auto pass([[maybe_unused]] Willow::Test* t) -> int {
        return 0;
    }
    constexpr auto fail([[maybe_unused]] Willow::Test* t) -> int {
        return 1;
    }
};  // namespace FixtureFuncs

constexpr auto test_runTests([[maybe_unused]] Willow::Test* test) -> int {
    SilentReporter r = {};
    int ret = Willow::runTests(
        {{"pass", FixtureFuncs::pass},
         {"fail", FixtureFuncs::fail},
         {"skip", FixtureFuncs::fail, Willow::Status::Skip}},
        r);

    return !(ret == 1);
}

constexpr auto test_alert([[maybe_unused]] Willow::Test* test) -> int {
    Willow::Test t {};
    Willow::alert(&t, "fail");

    if (t.msg.has_value() && t.msg.value() == "fail") {
        return 0;
    }
    return 1;
}
