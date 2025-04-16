#include "WinSumLoseSum.h"
#include <functional>
using namespace std;

Optional<get<int>> makeTarget(const Set<int>& elems, int target) {
    std::function<Optional<get<int>>(Vector<int>, int, int)> helper;

    helper = [&](vector<int> values, int index, int remaining) -> Optional<get<int>> {

        if (remaining == 0) {
            return {};
        }

        if (index >= values.size()) {
            return Nothing;
        }

        int current = values[index];


        Optional<get<int>> withCurrent = helper(values, index + 1, remaining - current);
        if (withCurrent) {
            withCurrent->add(current);
            return withCurrent;
        }


        return helper(values, index + 1, remaining);
    };

    vector<int> elemsVec = elems.toVector();
    return helper(elemsVec, 0, target);
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

STUDENT_TEST("Works with larger target and mixed elements") {
    Set<int> nums = {2, 4, 6, 10};
    EXPECT_NOT_EQUAL(makeTarget(nums, 16), Nothing); // 6 + 10
    EXPECT_EQUAL(makeTarget(nums, 3), Nothing);
}

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Works for an empty set of numbers.") {
    /* Can make 0, but not others. */
    EXPECT_EQUAL(makeTarget({ },  0), {});
    EXPECT_EQUAL(makeTarget({ },  1), Nothing);
    EXPECT_EQUAL(makeTarget({ }, -1), Nothing);
}

PROVIDED_TEST("Works for a one-element (singleton) set.") {
    /* Can make 0 and 137, but not others. */
    EXPECT_EQUAL(makeTarget({ 137 }, 0),   {});
    EXPECT_EQUAL(makeTarget({ 137 }, 137), {137});
    EXPECT_EQUAL(makeTarget({ 137 }, 1),   Nothing);
    EXPECT_EQUAL(makeTarget({ 137 }, -1),  Nothing);
}

PROVIDED_TEST("Works for a two-element (doubleton) set.") {
    EXPECT_EQUAL(makeTarget({ 1, 2 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 0), {});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 2), {2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 3), {1, 2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 4), Nothing);
}

PROVIDED_TEST("Works for a three-element set.") {

    /* Can make 0, 1, 3, 4, 5, 7, and 8, but not others. */
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  0), {});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  2), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  3), {3});
    EXPECT_NOT_EQUAL(makeTarget({ 1, 3, 4 }, 4), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  5), {1, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  6), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  7), {3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  8), {1, 3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  9), Nothing);
}
