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
    Willow::registerTests({
        {"pass", FixtureFuncs::pass},
        {"fail", FixtureFuncs::fail},
        {"skip", FixtureFuncs::fail, Willow::Status::Skip}
    });

    int ret = Willow::runTests(r);
    return !(ret == 1);
}
