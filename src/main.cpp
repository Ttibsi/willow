#include "tests/test_reporters.h"
#include "tests/test_test.h"
#include "tests/test_willow.h"
#include "willow/reporters.h"
#include "willow/willow.h"

auto main(int argc, char* argv[]) -> int {
    Willow::PreCommitReporter reporter = {};

    Willow::registerTests({
        {"test_runTests", test_runTests},
        {"test_toString", test_toString},
        {"test_Test_alert", test_Test_alert},
        {"test_Test_Operator()", test_Test_Operator},
        {"PreCommitReporter::print", TestPreCommitReporter::test_print},
        {"PreCommitReporter::cleanup", TestPreCommitReporter::test_cleanup},
        {"PreCommitReporter::highlight", TestPreCommitReporter::test_highlight},
    });

    if (argc > 1) {
        return Willow::runSingleTest(std::string(argv[1]), reporter);
    }
    return Willow::runTests(reporter);
}
