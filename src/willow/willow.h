#ifndef WILLOW_H
#define WILLOW_H

#include <vector>

#include "reporters.h"
#include "test.h"

namespace Willow {
    std::vector<Test> global_tests = {};

    constexpr auto registerTests(std::vector<Test> tests) -> void {
        global_tests = tests;
    }

    constexpr auto runTests(Reporter& reporter) -> int {
        for (auto&& test : global_tests) {
            if (test.status == Status::Skip) {
                continue;
            }

            test();
            if (test.retcode != 0) {
                test.status = Status::Fail;
                continue;
            }

            test.status = Status::Pass;
        }

        std::for_each(global_tests.begin(), global_tests.end(), [&reporter](Test& t) { reporter.print(t); });
        reporter.cleanup();

        return int32_t(std::count_if(global_tests.begin(), global_tests.end(), [](Test& t) {
            return t.status == Status::Fail;
        }));
    }

}  // namespace Willow

#endif  // WILLOW_H
