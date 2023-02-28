#include <unity.h>

void setUp() {}

void tearDown(){}

void test_shouldFail(void){
    TEST_ASSERT_EQUAL(1,2);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_shouldFail);

    return UNITY_END();
}