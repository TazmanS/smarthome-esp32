/**
 * @file wifi.h
 * @brief WiFi connectivity interface
 * @details Declares functions for initializing WiFi connection and station mode
 */

#ifndef WIFI_H
#define WIFI_H

/**
 * @brief Initializes WiFi in station mode
 * @details Connects to WiFi network using provided SSID and password credentials
 * @param[in] ssid WiFi network SSID
 * @param[in] password WiFi network password
 * @return void
 */
void wifi_init_sta(const char *ssid, const char *password);

#endif
