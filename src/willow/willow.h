#ifndef WILLOW_H
#define WILLOW_H

#include <vector>

#include "reporters.h"
#include "test.h"

namespace Willow {
    inline std::vector<Test> global_tests = {};

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

        std::for_each(
            global_tests.begin(), global_tests.end(), [&reporter](Test& t) { reporter.print(t); });
        reporter.cleanup();

        return int32_t(std::count_if(global_tests.begin(), global_tests.end(), [](Test& t) {
            return t.status == Status::Fail;
        }));
    }

    constexpr auto runSingleTest(std::string_view test_name, Reporter& reporter) -> int {
        auto it = std::find_if(global_tests.begin(), global_tests.end(), [&test_name](Test& t) {
            return t.name == test_name;
        });
        if (it == global_tests.end()) {
            return 1;
        }

        Test& exec = *it;
        if (exec.status == Status::Skip) {
            return 2;
        }

        exec();
        exec.status = (exec.retcode == 0 ? Status::Pass : Status::Fail);
        reporter.print(exec);

        return exec.retcode;
    }

}  // namespace Willow

#endif  // WILLOW_H
