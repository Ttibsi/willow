#include "willow/reporters.h"

// PreCommitReporter
class TestPreCommitReporter : public Willow::PreCommitReporter {
   public:
    static constexpr auto test_print([[maybe_unused]] Willow::Test* test) -> int {
        // NOTE: WE can test the logic and what's held in `results`
        return 0;
    }

    static constexpr auto test_cleanup([[maybe_unused]] Willow::Test* test) -> int { return 0; }

    static constexpr auto test_highlight([[maybe_unused]] Willow::Test* test) -> int { return 0; }
};
