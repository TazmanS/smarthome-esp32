/**
 * @file test_main.cpp
 * @brief Unit tests for Simple Moving Average (SMA) filter
 */

#include <unity.h>

extern "C"
{
#include "../../src/helpers/sma/sma.h"
#include "../../src/helpers/sma/sma.c"
}

// Test fixtures
static sma_filter_t filter;
static int buffer[5];

void setUp(void)
{
    // Runs before each test
}

void tearDown(void)
{
    // Runs after each test
}

/**
 * @brief Test SMA initialization
 */
void test_sma_init(void)
{
    sma_init(&filter, buffer, 5);

    TEST_ASSERT_EQUAL(5, filter.window_size);
    TEST_ASSERT_EQUAL(0, filter.index);
    TEST_ASSERT_EQUAL(0, filter.count);
    TEST_ASSERT_EQUAL(0, filter.sum);
    TEST_ASSERT_EQUAL_PTR(buffer, filter.buffer);

    // Check buffer is zeroed
    for (int i = 0; i < 5; i++)
    {
        TEST_ASSERT_EQUAL(0, buffer[i]);
    }
}

/**
 * @brief Test adding first sample
 */
void test_sma_first_sample(void)
{
    sma_init(&filter, buffer, 5);

    int result = sma_add_sample(&filter, 10);

    TEST_ASSERT_EQUAL(10, result); // Average of [10] = 10
    TEST_ASSERT_EQUAL(1, filter.count);
    TEST_ASSERT_EQUAL(10, filter.sum);
}

/**
 * @brief Test partial window (not fully filled)
 */
void test_sma_partial_window(void)
{
    sma_init(&filter, buffer, 5);

    sma_add_sample(&filter, 10);
    sma_add_sample(&filter, 20);
    int result = sma_add_sample(&filter, 30);

    // Average of [10, 20, 30] = 60 / 3 = 20
    TEST_ASSERT_EQUAL(20, result);
    TEST_ASSERT_EQUAL(3, filter.count);
    TEST_ASSERT_EQUAL(60, filter.sum);
}

/**
 * @brief Test full window
 */
void test_sma_full_window(void)
{
    sma_init(&filter, buffer, 5);

    sma_add_sample(&filter, 10);
    sma_add_sample(&filter, 20);
    sma_add_sample(&filter, 30);
    sma_add_sample(&filter, 40);
    int result = sma_add_sample(&filter, 50);

    // Average of [10, 20, 30, 40, 50] = 150 / 5 = 30
    TEST_ASSERT_EQUAL(30, result);
    TEST_ASSERT_EQUAL(5, filter.count);
    TEST_ASSERT_EQUAL(150, filter.sum);
}

/**
 * @brief Test circular buffer behavior (overflow)
 */
void test_sma_circular_buffer(void)
{
    sma_init(&filter, buffer, 5);

    // Fill window: [10, 20, 30, 40, 50]
    sma_add_sample(&filter, 10);
    sma_add_sample(&filter, 20);
    sma_add_sample(&filter, 30);
    sma_add_sample(&filter, 40);
    sma_add_sample(&filter, 50);

    // Add 6th sample: should replace first (10)
    // New window: [60, 20, 30, 40, 50]
    int result = sma_add_sample(&filter, 60);

    // Average = (60 + 20 + 30 + 40 + 50) / 5 = 200 / 5 = 40
    TEST_ASSERT_EQUAL(40, result);
    TEST_ASSERT_EQUAL(5, filter.count); // Count stays at 5
    TEST_ASSERT_EQUAL(200, filter.sum);
}

/**
 * @brief Test multiple overflows
 */
void test_sma_multiple_overflows(void)
{
    sma_init(&filter, buffer, 3);

    sma_add_sample(&filter, 10);              // [10] -> avg = 10
    sma_add_sample(&filter, 20);              // [10, 20] -> avg = 15
    sma_add_sample(&filter, 30);              // [10, 20, 30] -> avg = 20
    sma_add_sample(&filter, 40);              // [40, 20, 30] -> avg = 30
    int result = sma_add_sample(&filter, 50); // [40, 50, 30] -> avg = 40

    TEST_ASSERT_EQUAL(40, result);
}

/**
 * @brief Test with negative values
 */
void test_sma_negative_values(void)
{
    sma_init(&filter, buffer, 3);

    sma_add_sample(&filter, -10);
    sma_add_sample(&filter, -20);
    int result = sma_add_sample(&filter, -30);

    // Average of [-10, -20, -30] = -60 / 3 = -20
    TEST_ASSERT_EQUAL(-20, result);
}

/**
 * @brief Test with zero values
 */
void test_sma_zero_values(void)
{
    sma_init(&filter, buffer, 3);

    sma_add_sample(&filter, 0);
    sma_add_sample(&filter, 0);
    int result = sma_add_sample(&filter, 0);

    TEST_ASSERT_EQUAL(0, result);
}

/**
 * @brief Main test runner entry point
 */
int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_sma_init);
    RUN_TEST(test_sma_first_sample);
    RUN_TEST(test_sma_partial_window);
    RUN_TEST(test_sma_full_window);
    RUN_TEST(test_sma_circular_buffer);
    RUN_TEST(test_sma_multiple_overflows);
    RUN_TEST(test_sma_negative_values);
    RUN_TEST(test_sma_zero_values);

    return UNITY_END();
}
