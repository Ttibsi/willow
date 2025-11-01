#include "willow.h"

#include <algorithm>

#include "reporters.h"
#include "test.h"

namespace Willow {
    auto run_tests(std::vector<Test> tests, Reporter& reporter) -> int {
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

        return std::count_if(
            tests.begin(), tests.end(), [](Test& t) { return t.status == Status::Fail; });
    }
}  // namespace Willow
