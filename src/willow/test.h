#ifndef WILLOW_TEST_H
#define WILLOW_TEST_H

#include <optional>
#include <string>

namespace Willow {
    // forward declaration for type alias
    struct Test;
    using TestFn = int (*)(Test*);

    enum class Status { None, Pass, Fail, Skip };

    constexpr auto toString(const Status& st) -> std::string {
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
        std::optional<std::string> msg = std::nullopt;
        Status status = Status::None;

        constexpr Test() : name(""), fn(NULL) {}
        constexpr Test(std::string given_name, TestFn f) : name {given_name}, fn {f} {}
        constexpr Test(std::string given_name, TestFn f, Status st)
            : name {given_name}, fn {f}, status {st} {}

        auto operator()() -> void { retcode = fn(this); }

        constexpr auto alert(const std::string& message) -> void { msg = message; }
    };
};  // namespace Willow

#endif  // WILLOW_TEST_H
