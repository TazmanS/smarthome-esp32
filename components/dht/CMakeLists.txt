idf_component_register(
    SRCS "dht.c"
    INCLUDE_DIRS "." "$ENV{IDF_PATH}/components/esp_timer/include"
    REQUIRES driver
)