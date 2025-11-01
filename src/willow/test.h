#ifndef WILLOW_TEST_H
#define WILLOW_TEST_H

#include <string>

namespace Willow {
    using TestFn = int (*)();

    enum class Status { None, Pass, Fail, Skip };

    inline auto toString(const Status& st) -> std::string {
        switch (st) {
            case Status::None:
                return "None";
                break;
            case Status::Pass:
                return "Passed";
                break;
            case Status::Fail:
                return "Failed";
                break;
            case Status::Skip:
                return "Skipped";
                break;
        };

        return "";
    }

    struct Test {
        std::string name;
        TestFn fn;
        int retcode = 0;
        Status status = Status::None;

        Test(std::string given_name, TestFn f) : name {given_name}, fn {f} {}
        Test(std::string given_name, TestFn f, Status st)
            : name {given_name}, fn {f}, status {st} {}

        auto operator()() -> void { retcode = fn(); }
    };
};  // namespace Willow

#endif  // WILLOW_TEST_H
