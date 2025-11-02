#ifndef WILLOW_H
#define WILLOW_H

#include <vector>

#include "reporters.h"
#include "test.h"

namespace Willow {
    constexpr auto runTests(std::vector<Test> tests, Reporter& reporter) -> int {
        for (auto&& test : tests) {
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

        std::for_each(tests.begin(), tests.end(), [&reporter](Test& t) { reporter.print(t); });
        reporter.cleanup();

        return int32_t(std::count_if(tests.begin(), tests.end(), [](Test& t) {
            return t.status == Status::Fail;
        }));
    }

    constexpr auto alert(Test* test, std::string message) -> void {
        test->msg = message;
    }

}  // namespace Willow

#endif  // WILLOW_H
