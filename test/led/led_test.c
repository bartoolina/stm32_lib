#include "unity.h"
#include "led.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    TEST_FAIL_MESSAGE("wkoncu");
}

void test_function_should_doAlsoDoBlah(void) {
    // TEST_FAIL_MESSAGE("costam");
    // TEST_IGNORE_MESSAGE("IGNORUJE");
    TEST_ASSERT_EQUAL(1, 1);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}