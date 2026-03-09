#ifndef TEST_NVS_FLASH_H
#define TEST_NVS_FLASH_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef int esp_err_t;

#define ESP_OK 0
#define ESP_ERR_NVS_NO_FREE_PAGES 0x1101
#define ESP_ERR_NVS_NEW_VERSION_FOUND 0x1102

  esp_err_t nvs_flash_init(void);
  esp_err_t nvs_flash_erase(void);
  void test_esp_error_check(esp_err_t err);

#define ESP_ERROR_CHECK(x) test_esp_error_check((x))

#ifdef __cplusplus
}
#endif

#endif