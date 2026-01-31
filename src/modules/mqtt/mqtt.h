/**
 * @file mqtt.h
 * @brief MQTT client interface
 * @details Declares functions for initializing and managing MQTT communication
 */

#ifndef MQTT_H
#define MQTT_H

/**
 * @brief Starts MQTT client application
 * @details Initializes and connects MQTT client to broker for IoT communication
 * @return void
 */
void mqtt_app_start(void);
void mqtt_publish(const char *topic, const char *data);

#endif