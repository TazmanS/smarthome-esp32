#include <unity.h>

extern "C"
{
#include "nvs_flash.h"
#include "../../src/helpers/nvs/nvs.c"
}

static esp_err_t init_returns[4];
static int init_return_count;
static int init_call_count;

static esp_err_t erase_return;
static int erase_call_count;

static esp_err_t error_check_args[8];
static int error_check_call_count;

static void reset_mocks(void)
{
    for (int i = 0; i < 4; i++)
    {
        init_returns[i] = ESP_OK;
    }

    for (int i = 0; i < 8; i++)
    {
        error_check_args[i] = ESP_OK;
    }

    init_return_count = 0;
    init_call_count = 0;
    erase_return = ESP_OK;
    erase_call_count = 0;
    error_check_call_count = 0;
}

extern "C" esp_err_t nvs_flash_init(void)
{
    int idx = init_call_count++;
    if (idx < init_return_count)
    {
        return init_returns[idx];
    }
    return ESP_OK;
}

extern "C" esp_err_t nvs_flash_erase(void)
{
    erase_call_count++;
    return erase_return;
}

extern "C" void test_esp_error_check(esp_err_t err)
{
    if (error_check_call_count < 8)
    {
        error_check_args[error_check_call_count] = err;
    }
    error_check_call_count++;
}

void setUp(void)
{
    reset_mocks();
}

void tearDown(void)
{
}

void test_nvs_init_success_first_try(void)
{
    init_return_count = 1;
    init_returns[0] = ESP_OK;

    nvs_init();

    TEST_ASSERT_EQUAL_INT(1, init_call_count);
    TEST_ASSERT_EQUAL_INT(0, erase_call_count);
    TEST_ASSERT_EQUAL_INT(1, error_check_call_count);
    TEST_ASSERT_EQUAL_INT(ESP_OK, error_check_args[0]);
}

void test_nvs_init_recover_no_free_pages(void)
{
    init_return_count = 2;
    init_returns[0] = ESP_ERR_NVS_NO_FREE_PAGES;
    init_returns[1] = ESP_OK;
    erase_return = ESP_OK;

    nvs_init();

    TEST_ASSERT_EQUAL_INT(2, init_call_count);
    TEST_ASSERT_EQUAL_INT(1, erase_call_count);
    TEST_ASSERT_EQUAL_INT(2, error_check_call_count);
    TEST_ASSERT_EQUAL_INT(ESP_OK, error_check_args[0]);
    TEST_ASSERT_EQUAL_INT(ESP_OK, error_check_args[1]);
}

void test_nvs_init_recover_new_version(void)
{
    init_return_count = 2;
    init_returns[0] = ESP_ERR_NVS_NEW_VERSION_FOUND;
    init_returns[1] = ESP_OK;
    erase_return = ESP_OK;

    nvs_init();

    TEST_ASSERT_EQUAL_INT(2, init_call_count);
    TEST_ASSERT_EQUAL_INT(1, erase_call_count);
    TEST_ASSERT_EQUAL_INT(2, error_check_call_count);
    TEST_ASSERT_EQUAL_INT(ESP_OK, error_check_args[0]);
    TEST_ASSERT_EQUAL_INT(ESP_OK, error_check_args[1]);
}

void test_nvs_init_reports_failed_reinit(void)
{
    init_return_count = 2;
    init_returns[0] = ESP_ERR_NVS_NO_FREE_PAGES;
    init_returns[1] = 1234;
    erase_return = ESP_OK;

    nvs_init();

    TEST_ASSERT_EQUAL_INT(2, init_call_count);
    TEST_ASSERT_EQUAL_INT(1, erase_call_count);
    TEST_ASSERT_EQUAL_INT(2, error_check_call_count);
    TEST_ASSERT_EQUAL_INT(ESP_OK, error_check_args[0]);
    TEST_ASSERT_EQUAL_INT(1234, error_check_args[1]);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_nvs_init_success_first_try);
    RUN_TEST(test_nvs_init_recover_no_free_pages);
    RUN_TEST(test_nvs_init_recover_new_version);
    RUN_TEST(test_nvs_init_reports_failed_reinit);

    return UNITY_END();
}