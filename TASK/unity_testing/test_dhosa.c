#include "unity.h"
#include "dhosa.h" // Include the header for matchDhosas

void setUp(void) {
    // Set up any necessary initialization before each test
}

void tearDown(void) {
    // No teardown required for now
}


void test_MatchDhosas_Case1(void) {
    // Case 1: Match with some orders served in the right sequence
    int stack[] = {0, 1, 1};
    int queue[] = {1, 0, 0};
    int result = matchDhosas(stack, 3, queue);
    TEST_ASSERT_EQUAL(1, result); // Expect 1 unmatched employee
}

void test_MatchDhosas_Case2(void) {
    // Case 2: No matching dhosas, different orders
    int stack[] = {1, 0};
    int queue[] = {0, 1};
    int result = matchDhosas(stack, 2, queue);
    TEST_ASSERT_EQUAL(2, result); // Expect 2 unmatched employees
}
void test_MatchDhosas_Case3(void) {
    // Case 3: Some dhosas match despite different positions
    int stack[] = {0, 0, 1};
    int queue[] = {1, 1, 0};
    int result = matchDhosas(stack, 3, queue);
    TEST_ASSERT_EQUAL(1, result); // Expect 1 unmatched employee
}

void test_MatchDhosas_Case4(void) {
    // Case 4: Same as Case 3 but with 4 elements
    int stack[] = {0, 0, 1, 1};
    int queue[] = {1, 1, 0, 1};
    int result = matchDhosas(stack, 4, queue);
    TEST_ASSERT_EQUAL(2, result); // Expect 2 unmatched employees
}

void test_MatchDhosas_Case5(void) {
    // Case 5: Single element, no match
    int stack[] = {0};
    int queue[] = {1};
    int result = matchDhosas(stack, 1, queue);
    TEST_ASSERT_EQUAL(1, result); // Expect 1 unmatched employee
}

void test_MatchDhosas_Case6(void) {
    // Case 6: Full mismatch between stack and queue
    int stack[] = {0, 0, 1};
    int queue[] = {1, 0, 0};
    int result = matchDhosas(stack, 3, queue);
    TEST_ASSERT_EQUAL(2, result); // Expect 2 unmatched employees
}

void test_MatchDhosas_Case7(void) {
    // Case 7: More elements with partial match
    int stack[] = {0, 0, 1, 1, 0};
    int queue[] = {1, 1, 0, 0, 1};
    int result = matchDhosas(stack, 5, queue);
    TEST_ASSERT_EQUAL(2, result); // Expect 2 unmatched employees
}

// Main function for Unity test runner
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_MatchDhosas_Case1);
    RUN_TEST(test_MatchDhosas_Case2);
    RUN_TEST(test_MatchDhosas_Case3);
    RUN_TEST(test_MatchDhosas_Case4);
    RUN_TEST(test_MatchDhosas_Case5);
    RUN_TEST(test_MatchDhosas_Case6);
    RUN_TEST(test_MatchDhosas_Case7);
    return UNITY_END();
}

