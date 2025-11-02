#ifndef WILLOW_REPORTER_H
#define WILLOW_REPORTER_H

// TODO: Implement JSONReporter

#include <print>

#include "test.h"

namespace Willow {
    class Reporter {
       public:
        virtual constexpr auto print(const Test& test) -> void = 0;
        virtual constexpr auto cleanup() -> void = 0;
        virtual constexpr ~Reporter() = default;
    };

    class DefaultReporter : public Reporter {
       private:
        int test_count = 0;

       public:
        inline constexpr auto print(const Test& test) -> void {
            std::println("[{}] {}\t{}", ++test_count, test.name, toString(test.status));
        }

        inline constexpr auto cleanup() -> void {}
    };

    // A reporter that displays based on the output from pre-commit
    class PreCommitReporter : public Reporter {
       protected:
        struct Results {
            int pass = 0;
            int fail = 0;
            int skip = 0;
        };

        const std::size_t screen_len = 80;
        Results results = {};

       public:
        inline constexpr auto print(const Test& test) -> void {
            const std::size_t name_len = test.name.size();
            const std::size_t status_len = toString(test.status).size();
            const std::string ansi = highlight(test.status);

            std::println(
                "{}{}{}{}\x1b[0m", test.name,
                std::string(screen_len - (name_len + status_len), '.'), ansi,
                toString(test.status));

            if (test.status == Status::Fail) {
                results.fail++;
                std::println("\x1b[31m\tReturn code: {}\x1b[0m", test.retcode);
                if (test.msg.has_value()) {
                    std::println("\x1b[31m\t{}\x1b[0m", test.msg.value());
                }

            } else if (test.status == Status::Skip) {
                results.skip++;
                if (test.msg.has_value()) {
                    std::println("\x1b[33m\t{}\x1b[0m", test.msg.value());
                }
            } else {
                results.pass++;
            }
        }

        inline constexpr auto cleanup() -> void {
            Status final =
                (results.fail ? Status::Fail : (results.skip ? Status::Skip : Status::Pass));

            auto make_bar = [&](std::size_t len) { return std::string((len - 2) / 2, '='); };

            switch (final) {
                case Status::Pass: {
                    std::string msg = "All tests passed!";
                    std::println(
                        "\x1b[32m{} {} {}\x1b[0m", make_bar((screen_len - msg.size()) + 1), msg,
                        make_bar(screen_len - msg.size()));
                    break;
                }

                case Status::Skip: {
                    std::string msg = std::to_string(results.pass) + " tests passed (" +
                                      std::to_string(results.skip) + " skipped)";
                    std::println(
                        "\x1b[33m{} {} {}\x1b[0m", make_bar(screen_len - msg.size()), msg,
                        make_bar(screen_len - msg.size()));
                    break;
                }

                case Status::Fail: {
                    std::string msg = std::to_string(results.fail) + " tests failed, (" +
                                      std::to_string(results.pass) + " passed)";
                    std::println(
                        "\x1b[31m{} {} {}\x1b[0m", make_bar(screen_len - msg.size()), msg,
                        make_bar(screen_len - msg.size()));
                    break;
                }

                case Status::None:
                default:
                    break;
            }
        }

        inline constexpr auto highlight(const Status& st) -> std::string {
            switch (st) {
                case Status::None:
                    return "\x1b[0m";
                    break;
                case Status::Pass:
                    return "\x1b[42m";
                    break;
                case Status::Fail:
                    return "\x1b[41m";
                    break;
                case Status::Skip:
                    return "\x1b[43m";
                    break;
            }

            return "";
        }
    };

}  // namespace Willow

#endif  // WILLOW_REPORTER_H
